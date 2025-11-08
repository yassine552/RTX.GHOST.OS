import os
import sys
import time
import requests
import subprocess
from stem import Signal
from stem.control import Controller

class TorManager:
    """إدارة اتصال Tor"""
    
    def __init__(self):
        self.tor_process = None
        self.controller = None
        self.tor_port = 9050
        self.control_port = 9051
        self.is_running = False
        
    def start(self):
        """تشغيل Tor"""
        try:
            # التحقق من وجود Tor
            if not self._check_tor_installed():
                print("⚠️ Tor غير مثبت. جاري التثبيت...")
                self._install_tor()
            
            # تشغيل عملية Tor
            print("🔄 تشغيل Tor...")
            self.tor_process = subprocess.Popen(
                ['tor', '--SocksPort', str(self.tor_port), '--ControlPort', str(self.control_port)],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE
            )
            
            # الانتظار حتى يكون Tor جاهزاً
            time.sleep(5)
            
            # الاتصال بوحدة التحكم
            self.controller = Controller.from_port(port=self.control_port)
            self.controller.authenticate()
            
            self.is_running = True
            print("✅ تم تشغيل Tor بنجاح")
            return True
            
        except Exception as e:
            print(f"❌ خطأ في تشغيل Tor: {e}")
            return False
    
    def stop(self):
        """إيقاف Tor"""
        try:
            if self.controller:
                self.controller.close()
            
            if self.tor_process:
                self.tor_process.terminate()
                self.tor_process.wait()
            
            self.is_running = False
            print("✅ تم إيقاف Tor")
            return True
            
        except Exception as e:
            print(f"❌ خطأ في إيقاف Tor: {e}")
            return False
    
    def renew_ip(self):
        """تجديد عنوان IP"""
        try:
            if not self.is_running or not self.controller:
                return False
            
            self.controller.signal(Signal.NEWNYM)
            time.sleep(5)  # الانتظار حتى يتم تغيير IP
            print("✅ تم تجديد IP")
            return True
            
        except Exception as e:
            print(f"❌ خطأ في تجديد IP: {e}")
            return False
    
    def get_current_ip(self):
        """الحصول على IP الحالي"""
        try:
            proxies = {
                'http': f'socks5h://127.0.0.1:{self.tor_port}',
                'https': f'socks5h://127.0.0.1:{self.tor_port}'
            }
            
            response = requests.get('https://api.ipify.org?format=json', proxies=proxies, timeout=10)
            return response.json()['ip']
            
        except Exception as e:
            print(f"❌ خطأ في الحصول على IP: {e}")
            return None
    
    def get_status(self):
        """الحصول على حالة Tor"""
        if self.is_running:
            ip = self.get_current_ip()
            return {
                'status': 'running',
                'ip': ip
            }
        else:
            return {
                'status': 'stopped'
            }
    
    def _check_tor_installed(self):
        """التحقق من تثبيت Tor"""
        try:
            subprocess.run(['tor', '--version'], capture_output=True, check=True)
            return True
        except:
            return False
    
    def _install_tor(self):
        """تثبيت Tor"""
        system = sys.platform
        
        try:
            if system == 'linux':
                # Linux
                subprocess.run(['sudo', 'apt-get', 'update'], check=True)
                subprocess.run(['sudo', 'apt-get', 'install', '-y', 'tor'], check=True)
            elif system == 'darwin':
                # macOS
                subprocess.run(['brew', 'install', 'tor'], check=True)
            elif system == 'win32':
                # Windows
                print("⚠️ يرجى تثبيت Tor Expert Bundle يدوياً من:")
                print("https://www.torproject.org/download/tor/")
                return False
            
            print("✅ تم تثبيت Tor بنجاح")
            return True
            
        except Exception as e:
            print(f"❌ خطأ في تثبيت Tor: {e}")
            return False
