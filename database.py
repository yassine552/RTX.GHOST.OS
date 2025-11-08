import json
import os
from datetime import datetime

class Database:
    """إدارة قاعدة البيانات"""
    
    def __init__(self):
        self.data_dir = os.path.join(os.path.dirname(__file__), '..', 'data')
        self.ensure_data_dir()
        
    def ensure_data_dir(self):
        """التأكد من وجود مجلد البيانات"""
        if not os.path.exists(self.data_dir):
            os.makedirs(self.data_dir)
    
    def save_json(self, filename, data):
        """حفظ بيانات JSON"""
        try:
            filepath = os.path.join(self.data_dir, filename)
            with open(filepath, 'w', encoding='utf-8') as f:
                json.dump(data, f, ensure_ascii=False, indent=2)
            return True
        except Exception as e:
            print(f"خطأ في حفظ البيانات: {e}")
            return False
    
    def load_json(self, filename):
        """تحميل بيانات JSON"""
        try:
            filepath = os.path.join(self.data_dir, filename)
            if os.path.exists(filepath):
                with open(filepath, 'r', encoding='utf-8') as f:
                    return json.load(f)
            return None
        except Exception as e:
            print(f"خطأ في تحميل البيانات: {e}")
            return None
    
    def log_activity(self, activity_type, details):
        """تسجيل النشاطات"""
        try:
            log_file = os.path.join(self.data_dir, 'activity_log.json')
            
            # تحميل السجل الحالي
            log = []
            if os.path.exists(log_file):
                with open(log_file, 'r', encoding='utf-8') as f:
                    log = json.load(f)
            
            # إضافة النشاط الجديد
            log.append({
                'timestamp': datetime.now().isoformat(),
                'type': activity_type,
                'details': details
            })
            
            # حفظ السجل
            with open(log_file, 'w', encoding='utf-8') as f:
                json.dump(log, f, ensure_ascii=False, indent=2)
            
            return True
            
        except Exception as e:
            print(f"خطأ في تسجيل النشاط: {e}")
            return False
    
    def get_activity_log(self, limit=100):
        """الحصول على سجل النشاطات"""
        try:
            log_file = os.path.join(self.data_dir, 'activity_log.json')
            
            if os.path.exists(log_file):
                with open(log_file, 'r', encoding='utf-8') as f:
                    log = json.load(f)
                    return log[-limit:]  # آخر N نشاط
            return []
            
        except Exception as e:
            print(f"خطأ في قراءة السجل: {e}")
            return []
import json
import os
from datetime import datetime

class Database:
    """إدارة قاعدة البيانات"""
    
    def __init__(self):
        self.data_dir = os.path.join(os.path.dirname(__file__), '..', 'data')
        self.ensure_data_dir()
        
    def ensure_data_dir(self):
        """التأكد من وجود مجلد البيانات"""
        if not os.path.exists(self.data_dir):
            os.makedirs(self.data_dir)
    
    def save_json(self, filename, data):
        """حفظ بيانات JSON"""
        try:
            filepath = os.path.join(self.data_dir, filename)
            with open(filepath, 'w', encoding='utf-8') as f:
                json.dump(data, f, ensure_ascii=False, indent=2)
            return True
        except Exception as e:
            print(f"خطأ في حفظ البيانات: {e}")
            return False
    
    def load_json(self, filename):
        """تحميل بيانات JSON"""
        try:
            filepath = os.path.join(self.data_dir, filename)
            if os.path.exists(filepath):
                with open(filepath, 'r', encoding='utf-8') as f:
                    return json.load(f)
            return None
        except Exception as e:
            print(f"خطأ في تحميل البيانات: {e}")
            return None
    
    def log_activity(self, activity_type, details):
        """تسجيل النشاطات"""
        try:
            log_file = os.path.join(self.data_dir, 'activity_log.json')
            
            # تحميل السجل الحالي
            log = []
            if os.path.exists(log_file):
                with open(log_file, 'r', encoding='utf-8') as f:
                    log = json.load(f)
            
            # إضافة النشاط الجديد
            log.append({
                'timestamp': datetime.now().isoformat(),
                'type': activity_type,
                'details': details
            })
            
            # حفظ السجل
            with open(log_file, 'w', encoding='utf-8') as f:
                json.dump(log, f, ensure_ascii=False, indent=2)
            
            return True
            
        except Exception as e:
            print(f"خطأ في تسجيل النشاط: {e}")
            return False
    
    def get_activity_log(self, limit=100):
        """الحصول على سجل النشاطات"""
        try:
            log_file = os.path.join(self.data_dir, 'activity_log.json')
            
            if os.path.exists(log_file):
                with open(log_file, 'r', encoding='utf-8') as f:
                    log = json.load(f)
                    return log[-limit:]  # آخر N نشاط
            return []
            
        except Exception as e:
            print(f"خطأ في قراءة السجل: {e}")
            return []
