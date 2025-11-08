from flask import Flask, jsonify, request, send_from_directory
from flask_cors import CORS
import json
import os
import subprocess
import threading
from tor_manager import TorManager
from tools_manager import ToolsManager
from database import Database

app = Flask(__name__, static_folder='../frontend/build', static_url_path='')
CORS(app)

# تهيئة المكونات
tor_manager = TorManager()
tools_manager = ToolsManager()
db = Database()

# متغيرات عامة
tor_enabled = False
running_tools = {}

@app.route('/')
def serve():
    """تقديم الواجهة الرئيسية"""
    return send_from_directory(app.static_folder, 'index.html')

@app.route('/api/status')
def status():
    """حالة النظام"""
    return jsonify({
        'status': 'online',
        'tor_enabled': tor_enabled,
        'tor_status': tor_manager.get_status() if tor_enabled else 'disabled',
        'tools_count': len(tools_manager.get_all_tools()),
        'running_tools': len(running_tools)
    })

@app.route('/api/tor/enable', methods=['POST'])
def enable_tor():
    """تفعيل Tor"""
    global tor_enabled
    try:
        if tor_manager.start():
            tor_enabled = True
            return jsonify({
                'success': True,
                'message': 'تم تفعيل Tor بنجاح',
                'ip': tor_manager.get_current_ip()
            })
        else:
            return jsonify({
                'success': False,
                'message': 'فشل تفعيل Tor'
            }), 500
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/tor/disable', methods=['POST'])
def disable_tor():
    """تعطيل Tor"""
    global tor_enabled
    try:
        tor_manager.stop()
        tor_enabled = False
        return jsonify({
            'success': True,
            'message': 'تم تعطيل Tor'
        })
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/tor/newip', methods=['POST'])
def new_tor_ip():
    """الحصول على IP جديد من Tor"""
    try:
        if tor_manager.renew_ip():
            return jsonify({
                'success': True,
                'message': 'تم تغيير IP بنجاح',
                'ip': tor_manager.get_current_ip()
            })
        else:
            return jsonify({
                'success': False,
                'message': 'فشل تغيير IP'
            }), 500
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/categories')
def get_categories():
    """الحصول على جميع الفئات"""
    try:
        categories = tools_manager.get_categories()
        return jsonify({
            'success': True,
            'categories': categories
        })
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/tools')
def get_tools():
    """الحصول على جميع الأدوات أو حسب الفئة"""
    try:
        category = request.args.get('category', None)
        search = request.args.get('search', None)
        
        tools = tools_manager.get_tools(category=category, search=search)
        return jsonify({
            'success': True,
            'tools': tools,
            'count': len(tools)
        })
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/tools/<tool_id>')
def get_tool(tool_id):
    """الحصول على تفاصيل أداة معينة"""
    try:
        tool = tools_manager.get_tool(tool_id)
        if tool:
            return jsonify({
                'success': True,
                'tool': tool
            })
        else:
            return jsonify({
                'success': False,
                'message': 'الأداة غير موجودة'
            }), 404
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/tools/<tool_id>/install', methods=['POST'])
def install_tool(tool_id):
    """تثبيت أداة"""
    try:
        result = tools_manager.install_tool(tool_id)
        return jsonify(result)
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/tools/<tool_id>/run', methods=['POST'])
def run_tool(tool_id):
    """تشغيل أداة"""
    try:
        params = request.json.get('params', {})
        use_tor = request.json.get('use_tor', False)
        
        result = tools_manager.run_tool(
            tool_id, 
            params, 
            use_tor=use_tor and tor_enabled
        )
        
        if result['success']:
            running_tools[result['job_id']] = {
                'tool_id': tool_id,
                'start_time': result['start_time']
            }
        
        return jsonify(result)
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/jobs/<job_id>')
def get_job_status(job_id):
    """الحصول على حالة عملية"""
    try:
        result = tools_manager.get_job_status(job_id)
        return jsonify(result)
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/jobs/<job_id>/stop', methods=['POST'])
def stop_job(job_id):
    """إيقاف عملية"""
    try:
        result = tools_manager.stop_job(job_id)
        if job_id in running_tools:
            del running_tools[job_id]
        return jsonify(result)
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

@app.route('/api/stats')
def get_stats():
    """إحصائيات النظام"""
    try:
        stats = {
            'total_tools': len(tools_manager.get_all_tools()),
            'installed_tools': len(tools_manager.get_installed_tools()),
            'categories': len(tools_manager.get_categories()),
            'running_jobs': len(running_tools),
            'tor_enabled': tor_enabled
        }
        return jsonify({
            'success': True,
            'stats': stats
        })
    except Exception as e:
        return jsonify({
            'success': False,
            'message': f'خطأ: {str(e)}'
        }), 500

if __name__ == '__main__':
    print("🚀 تشغيل PentestOS...")
    print("=" * 50)
    print("📡 الواجهة: http://localhost:5000")
    print("=" * 50)
    app.run(host='0.0.0.0', port=5000, debug=True)
