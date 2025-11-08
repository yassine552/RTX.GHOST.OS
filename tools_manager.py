import json
import os
import subprocess
import uuid
import threading
from datetime import datetime

class ToolsManager:
    """إدارة الأدوات"""
    
    def __init__(self):
        self.tools_file = os.path.join(os.path.dirname(__file__), '..', 'data', 'tools.json')
        self.categories_file = os.path.join(os.path.dirname(__file__), '..', 'data', 'categories.json')
        self.tools = self._load_tools()
        self.categories = self._load_categories()
        self.running_jobs = {}
        
    def _load_tools(self):
        """تحميل الأدوات من ملف JSON"""
        try:
            if os.path.exists(self.tools_file):
                with open(self.tools_file, 'r', encoding='utf-8') as f:
                    return json.load(f)
            return []
        except Exception as e:
            print(f"خطأ في تحميل الأدوات: {e}")
            return []
    
    def _load_categories(self):
        """تحميل الفئات من ملف JSON"""
        try:
            if os.path.exists(self.categories_file):
                with open(self.categories_file, 'r', encoding='utf-8') as f:
                    return json.load(f)
            return []
        except Exception as e:
            print(f"خطأ في تحميل الفئات: {e}")
            return []
    
    def get_categories(self):
        """الحصول على جميع الفئات"""
        return self.categories
    
    def get_all_tools(self):
        """الحصول على جميع الأدوات"""
        return self.tools
    
    def get_tools(self, category=None, search=None):
        """الحصول على الأدوات مع التصفية"""
        filtered_tools = self.tools
        
        # تصفية حسب الفئة
        if category:
            filtered_tools = [t for t in filtered_tools if t.get('category') == category]
        
        # تصفية حسب البحث
        if search:
            search = search.lower()
            filtered_tools = [
                t for t in filtered_tools 
                if search in t.get('name', '').lower() or 
                   search in t.get('name_ar', '').lower() or
                   search in t.get('description', '').lower() or
                   search in t.get('description_ar', '').lower()
            ]
        
        return filtered_tools
    
    def get_tool(self, tool_id):
        """الحصول على أداة معينة"""
        for tool in self.tools:
            if tool.get('id') == tool_id:
                return tool
        return None
    
    def get_installed_tools(self):
        """الحصول على الأدوات المثبتة"""
        installed = []
        for tool in self.tools:
            if self._check_tool_installed(tool):
                installed.append(tool)
        return installed
    
    def _check_tool_installed(self, tool):
        """التحقق من تثبيت أداة"""
        try:
            # محاولة تشغيل الأمر --version أو --help
            command = tool.get('command', '')
            if command:
                subprocess.run(
                    [command, '--version'], 
                    capture_output=True, 
                    timeout=2
                )
                return True
        except:
            pass
        return False
    
    def install_tool(self, tool_id):
        """تثبيت أداة"""
        tool = self.get_tool(tool_id)
        if not tool:
            return {'success': False, 'message': 'الأداة غير موجودة'}
        
        try:
            install_cmd = tool.get('install_command', '')
            if not install_cmd:
                return {'success': False, 'message': 'لا يوجد أمر تثبيت لهذه الأداة'}
            
            # تنفيذ أمر التثبيت
            process = subprocess.Popen(
                install_cmd,
                shell=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE
            )
            
            stdout, stderr = process.communicate()
            
            if process.returncode == 0:
                return {
                    'success': True,
                    'message': 'تم تثبيت الأداة بنجاح',
                    'output': stdout.decode('utf-8', errors='ignore')
                }
            else:
                return {
                    'success': False,
                    'message': 'فشل تثبيت الأداة',
                    'error': stderr.decode('utf-8', errors='ignore')
                }
                
        except Exception as e:
            return {'success': False, 'message': f'خطأ: {str(e)}'}
    
    def run_tool(self, tool_id, params, use_tor=False):
        """تشغيل أداة"""
        tool = self.get_tool(tool_id)
        if not tool:
            return {'success': False, 'message': 'الأداة غير موجودة'}
        
        try:
            # بناء الأمر
            command = self._build_command(tool, params, use_tor)
            
            # إنشاء معرف للعملية
            job_id = str(uuid.uuid4())
            
            # تشغيل الأمر في thread منفصل
            def run_command():
                try:
                    process = subprocess.Popen(
                        command,
                        shell=True,
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE
                    )
                    
                    self.running_jobs[job_id]['process'] = process
                    stdout, stderr = process.communicate()
                    
                    self.running_jobs[job_id].update({
                        'status': 'completed',
                        'output': stdout.decode('utf-8', errors='ignore'),
                        'error': stderr.decode('utf-8', errors='ignore'),
                        'return_code': process.returncode,
                        'end_time': datetime.now().isoformat()
                    })
                    
                except Exception as e:
                    self.running_jobs[job_id].update({
                        'status': 'failed',
                        'error': str(e),
                        'end_time': datetime.now().isoformat()
                    })
            
            # حفظ معلومات العملية
            self.running_jobs[job_id] = {
                'tool_id': tool_id,
                'tool_name': tool.get('name'),
                'command': command,
                'status': 'running',
                'start_time': datetime.now().isoformat(),
                'process': None
            }
            
            # بدء الـ thread
            thread = threading.Thread(target=run_command)
            thread.start()
            
            return {
                'success': True,
                'message': 'تم بدء تشغيل الأداة',
                'job_id': job_id,
                'start_time': self.running_jobs[job_id]['start_time']
            }
            
        except Exception as e:
            return {'success': False, 'message': f'خطأ: {str(e)}'}
    
    def _build_command(self, tool, params, use_tor):
        """بناء أمر التشغيل"""
        command = tool.get('command', '')
        
        # إضافة المعاملات
        for param_name, param_value in params.items():
            command += f" {param_name} {param_value}"
        
        # إضافة Tor proxy إذا كان مفعلاً
        if use_tor:
            # إضافة proxychains أو torsocks
            command = f"proxychains {command}"
        
        return command
    
    def get_job_status(self, job_id):
        """الحصول على حالة عملية"""
        if job_id not in self.running_jobs:
            return {'success': False, 'message': 'العملية غير موجودة'}
        
        job = self.running_jobs[job_id]
        return {
            'success': True,
            'job': {
                'id': job_id,
                'tool_id': job.get('tool_id'),
                'tool_name': job.get('tool_name'),
                'status': job.get('status'),
                'start_time': job.get('start_time'),
                'end_time': job.get('end_time'),
                'output': job.get('output', ''),
                'error': job.get('error', ''),
                'return_code': job.get('return_code')
            }
        }
    
    def stop_job(self, job_id):
        """إيقاف عملية"""
        if job_id not in self.running_jobs:
            return {'success': False, 'message': 'العملية غير موجودة'}
        
        try:
            job = self.running_jobs[job_id]
            process = job.get('process')
            
            if process and job['status'] == 'running':
                process.terminate()
                process.wait(timeout=5)
                
                job.update({
                    'status': 'stopped',
                    'end_time': datetime.now().isoformat()
                })
                
                return {'success': True, 'message': 'تم إيقاف العملية'}
            else:
                return {'success': False, 'message': 'العملية غير قيد التشغيل'}
                
        except Exception as e:
            return {'success': False, 'message': f'خطأ: {str(e)}'}
