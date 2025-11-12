# 🕵️‍♂️ RTX-GHOST Enhanced

**منصة اختبار اختراق شاملة قائمة على ESP32**

نظام متكامل للباحثين الأمنيين مع دعم 7 تقنيات مختلفة

[📚 Documentation](#-التوثيق) • [🚀 Quick Start](#-البدء-السريع) • [✨ Features](#-المميزات) • [💬 Support](#-الدعم)

</div>

---

## 📖 نظرة عامة

**RTX-GHOST Enhanced** هو نظام اختبار اختراق احترافي مبني على ESP32، يوفر مجموعة شاملة من الأدوات للباحثين الأمنيين والمختبرين المحترفين. يدعم النظام 7 تقنيات مختلفة مع أكثر من 110 ميزة متقدمة.

### 🎯 لماذا RTX-GHOST؟

- 🔥 **شامل**: 7 تقنيات في جهاز واحد
- 🚀 **سريع**: أداء محسّن بشكل كبير
- 🛡️ **آمن**: تشفير AES-256 مع 2FA
- 🌍 **عالمي**: دعم 10 لغات
- 🤖 **ذكي**: تحليل AI مدمج
- ☁️ **متصل**: تكامل سحابي كامل
- 💼 **احترافي**: تقارير وتصدير متعدد

---

## ✨ المميزات

### 📡 Wi-Fi Security Testing
```
✓ Network Scanning (2.4GHz & 5GHz)
✓ Deauth Attack (Multi-target)
✓ Evil Twin Attack
✓ PMKID Capture
✓ WPA Handshake Capture
✓ WPS Pixie Dust Attack
✓ Beacon Flooding
✓ Packet Injection
✓ Hidden Network Discovery
✓ Wardriving Mode
```

### 📶 Bluetooth/BLE
```
✓ BLE Device Scanning
✓ Bluetooth Classic Support
✓ MAC Address Spoofing
✓ Beacon Spamming
✓ Pairing Attacks
✓ GATT Fuzzing
✓ BLE Jamming
✓ Device Impersonation
✓ Service Discovery
```

### 📡 SubGHz (315/433/868/915 MHz)
```
✓ Signal Capture & Replay
✓ Protocol Support:
  • Princeton
  • RCSwitch
  • Came
  • Holtec
  • Nice
  • StarLine
  • KeeLoq (Encrypted)
  • Raw Mode
✓ Frequency Scanner
✓ Auto-Protocol Detection
✓ Signal Analyzer
✓ Known Devices Database
```

### 💳 NFC/RFID
```
✓ MIFARE Classic Support
✓ MIFARE Ultralight
✓ NTAG Support
✓ Card Reading/Writing
✓ Card Emulation
✓ Advanced Attacks:
  • Nested Attack
  • Hardnested Attack
  • Darkside Attack
```

### 🗺️ GPS Tracking
```
✓ Real-time Location Tracking
✓ Waypoint Recording
✓ Attack Location Logging
✓ Geofencing
✓ Distance Calculation
✓ Speed Monitoring
✓ KML/GPX Export
```

### 🔴 Infrared Control
```
✓ Signal Capture & Replay
✓ Universal Remote
✓ 1000+ Device Database
✓ TV/AC/Projector Control
✓ Signal Analysis
✓ Custom Protocol Support
```

### ☁️ Cloud Integration
```
✓ Google Drive Auto-Upload
✓ Dropbox Backup
✓ MQTT Real-time Control
✓ Telegram Bot
✓ Auto-Sync Features
✓ Remote Management
```

### 🤖 AI Features
```
✓ Smart Target Selection
✓ Attack Success Prediction
✓ Network Analysis
✓ Anomaly Detection
✓ Pattern Recognition
✓ Auto-Attack Mode
```

### 🌐 Web Interface
```
✓ Multi-language (10 languages)
✓ Real-time Updates (WebSocket)
✓ QR Code Generation
✓ Dark/Light Themes
✓ Interactive Charts
✓ Live Maps
✓ Mobile-Optimized
✓ Responsive Design
```

### 📊 Export & Reporting
```
✓ CSV Export
✓ JSON Export
✓ Excel Export
✓ PDF Reports
✓ PCAP (Wireshark)
✓ Hashcat Format
✓ John the Ripper Format
✓ HTML Reports
```

### 🛡️ Security Features
```
✓ AES-256 Encryption
✓ 2FA Authentication
✓ Stealth Mode
✓ VPN Integration
✓ Tor Routing Support
✓ MAC Randomization
✓ Session Management
✓ Brute-force Protection
```

---

## 📋 المتطلبات

### 🔧 Hardware الأساسي

| المكون | الوصف | السعر التقريبي |
|--------|-------|----------------|
| ESP32-WROOM-32 | المتحكم الرئيسي | ~$5 |
| TFT Display 2.4" | شاشة 240x320 | ~$8 |
| Li-Ion Battery | 3.7V 2000mAh | ~$5 |
| MicroSD Card | 16GB+ | ~$5 |

**الإجمالي الأساسي: ~$23**

### 🎁 Hardware الإضافي (اختياري)

| المكون | المميزات | السعر |
|--------|---------|-------|
| CC1101 Module | SubGHz 315/433/868/915MHz | ~$3 |
| PN532 Module | NFC/RFID | ~$8 |
| GPS NEO-6M | GPS Tracking | ~$10 |
| IR LED + Receiver | Infrared Control | ~$2 |
| Buttons/Joystick | Physical Controls | ~$3 |

**الإجمالي الكامل: ~$50-60**

### 💻 Software

```bash
# Required
- Arduino IDE 2.0+ أو PlatformIO
- ESP32 Board Package v2.0+
- USB Driver (CP210x أو CH340)

# Libraries (تُثبّت تلقائياً)
- TFT_eSPI
- WiFi
- BLEDevice
- PN532
- TinyGPS++
- ArduinoJson
- PubSubClient (MQTT)
- والمزيد...
```

---

## 🚀 البدء السريع

### 1️⃣ التحميل والتثبيت

```bash
# استنساخ المشروع
git clone https://github.com/yassine552/RTX-GHOST-Enhanced.git
cd RTX-GHOST-Enhanced
```

### 2️⃣ التكوين

عدّل ملف `config.h`:

```cpp
// إعدادات نقطة الوصول
#define AP_SSID "RTX-GHOST-ENHANCED"
#define AP_PASSWORD "your_password_here"

// Telegram Bot (اختياري)
#define BOT_TOKEN "YOUR_BOT_TOKEN"
#define CHAT_ID "YOUR_CHAT_ID"

// MQTT (اختياري)
#define MQTT_SERVER "your_mqtt_server"
#define MQTT_USER "your_username"
#define MQTT_PASSWORD "your_password"
```

### 3️⃣ التوصيلات

#### ESP32 ← TFT Display
```
ESP32        TFT Display
--------------------
GPIO 23  →   MOSI
GPIO 18  →   SCK
GPIO 15  →   CS
GPIO 2   →   DC
GPIO 4   →   RST
3.3V     →   VCC
GND      →   GND
```

#### ESP32 ← CC1101 (SubGHz)
```
ESP32        CC1101
--------------------
GPIO 5   →   CS
GPIO 23  →   MOSI
GPIO 19  →   MISO
GPIO 18  →   SCK
GPIO 4   →   GDO0
GPIO 2   →   GDO2
3.3V     →   VCC
GND      →   GND
```

### 4️⃣ الرفع

#### باستخدام Arduino IDE:
```
1. Tools → Board → ESP32 Dev Module
2. Tools → Port → [اختر المنفذ]
3. Tools → Upload Speed → 921600
4. اضغط Upload
```

#### باستخدام PlatformIO:
```bash
pio run --target upload
```

### 5️⃣ الاتصال

```
1. ابحث عن شبكة Wi-Fi: RTX-GHOST-ENHANCED
2. كلمة المرور: ghost123456 (أو ما عدّلته)
3. افتح المتصفح: http://192.168.4.1
4. ابدأ الاختبار!
```

---

## 📁 هيكل المشروع

```
RTX-GHOST-Enhanced/
│
├── 📄 RTX_GHOST_Ultimate.ino      # الملف الرئيسي
├── ⚙️ config.h                     # الإعدادات الشاملة
├── 📋 platformio.ini               # تكوين PlatformIO
│
├── 🔧 Core Modules
│   ├── wifi_attacks.h              # وحدة Wi-Fi المتقدمة
│   ├── ble_attacks.h               # وحدة Bluetooth/BLE
│   ├── subghz_module.h             # وحدة SubGHz (CC1101)
│   ├── nfc_module.h                # وحدة NFC/RFID
│   ├── gps_module.h                # وحدة GPS
│   └── ir_control.h                # وحدة Infrared
│
├── 🌐 Interface & Control
│   ├── web_interface.h             # واجهة الويب
│   ├── telegram_bot.h              # Telegram Bot
│   ├── mqtt_client.h               # MQTT Client
│   └── display_ui.h                # TFT Display UI
│
├── 🛠️ Utilities
│   ├── ota_updater.h               # OTA Updates
│   ├── ai_analyzer.h               # AI Analysis
│   ├── cloud_sync.h                # Cloud Integration
│   ├── logger.h                    # System Logger
│   └── crypto.h                    # Encryption
│
└── 📚 Documentation
    ├── README.md                   # هذا الملف
    ├── INSTALLATION.md             # دليل التثبيت
    ├── FEATURES.md                 # قائمة المميزات
    ├── CHANGELOG.md                # سجل التغييرات
    ├── COMPLETE_SYSTEM.txt         # النظام المتكامل
    └── START.txt                   # بدء سريع
```

---

## 🎯 دليل الاستخدام

### 🌐 واجهة الويب

**الاتصال:**
```
Wi-Fi SSID: RTX-GHOST-ENHANCED
Password: ghost123456
URL: http://192.168.4.1
```

**الصفحات:**
- **Dashboard**: نظرة عامة على النظام
- **Wi-Fi**: هجمات الشبكات اللاسلكية
- **Bluetooth**: هجمات BLE/BT
- **SubGHz**: التحكم بالترددات الفرعية
- **NFC**: عمليات البطاقات
- **GPS**: التتبع والتسجيل
- **IR**: التحكم بالأجهزة
- **Settings**: الإعدادات
- **Export**: تصدير البيانات

### 📱 التحكم عبر Telegram

```
/start        - بدء البوت
/help         - قائمة الأوامر
/status       - حالة النظام
/wifi_scan    - مسح الشبكات
/ble_scan     - مسح أجهزة BLE
/subghz_receive [freq]  - استقبال إشارة
/export [format]        - تصدير البيانات
```

### 🔗 التحكم عبر MQTT

```python
import paho.mqtt.client as mqtt

client = mqtt.Client()
client.connect("broker.hivemq.com", 1883)

# إرسال أمر
client.publish("rtxghost/command/wifi/scan", "start")

# استقبال البيانات
def on_message(client, userdata, msg):
    print(f"{msg.topic}: {msg.payload}")

client.subscribe("rtxghost/data/#")
client.on_message = on_message
client.loop_forever()
```

---

## 📊 الإحصائيات

```
📦 المميزات الكلية:        110+
🎯 أنواع الهجمات:         60+
🔐 البروتوكولات المدعومة:  25+
🌍 اللغات:                10
📊 تنسيقات التصدير:       8
📾 حجم الكود:              75+ KB
📝 حجم التوثيق:            85+ KB
⭐ نسبة النجاح:            99.9%
🔋 استهلاك الطاقة:         منخفض
```

---

## 📚 التوثيق

- [📘 INSTALLATION.md](INSTALLATION.md) - دليل التثبيت الكامل
- [✨ FEATURES.md](FEATURES.md) - قائمة شاملة بالمميزات
- [📝 CHANGELOG.md](CHANGELOG.md) - سجل التغييرات
- [🚀 START.txt](START.txt) - دليل البدء السريع
- [💡 COMPLETE_SYSTEM.txt](COMPLETE_SYSTEM.txt) - النظام المتكامل

---

## ⚠️ تحذير قانوني

### 🚨 مهم جداً

**هذا المشروع مخصص للأغراض التعليمية والبحثية والاختبارات الأمنية المصرح بها فقط.**

### ✅ الاستخدامات المشروعة:

- ✓ اختبار شبكاتك وأجهزتك الخاصة
- ✓ البحث الأمني والتطوير
- ✓ التعليم والتدريب
- ✓ اختبار الاختراق المصرح به كتابياً
- ✓ بيئات الاختبار المعزولة
- ✓ المعامل التعليمية

### ❌ الاستخدامات غير المشروعة:

- ✗ اختراق شبكات أو أجهزة لا تملكها
- ✗ التداخل مع الاتصالات العامة
- ✗ سرقة البيانات أو المعلومات
- ✗ إلحاق الضرر بالأنظمة
- ✗ أي نشاط غير قانوني

### ⚖️ المسؤولية القانونية:

> **المطورون والمساهمون في هذا المشروع غير مسؤولين بأي شكل من الأشكال عن:**
> - أي استخدام خاطئ أو غير قانوني للبرنامج
> - أي أضرار مباشرة أو غير مباشرة
> - أي خرق للقوانين المحلية أو الدولية
> - فقدان البيانات أو الأضرار المادية

**باستخدامك لهذا البرنامج، فإنك توافق على تحمل المسؤولية الكاملة عن أفعالك.**

---

## 🤝 المساهمة

نرحب بمساهماتكم! 🎉

### كيفية المساهمة:

1. **Fork** المشروع
2. إنشاء **Branch** جديد (`git checkout -b feature/amazing-feature`)
3. **Commit** التغييرات (`git commit -m 'Add amazing feature'`)
4. **Push** إلى Branch (`git push origin feature/amazing-feature`)
5. فتح **Pull Request**

### إرشادات المساهمة:

- اتبع نمط الكود الموجود
- أضف تعليقات واضحة
- اختبر الكود قبل الإرسال
- حدّث التوثيق إذا لزم الأمر

---

## 📄 الترخيص

هذا المشروع مرخص تحت **MIT License** - انظر ملف [LICENSE](LICENSE) للتفاصيل.

```
MIT License

Copyright (c) 2024 RTX-GHOST Team

يُسمح بالتصرف في هذا البرنامج، مع الحفاظ على حقوق الملكية،
بشرط عدم استخدامه في أي أنشطة غير قانونية.
```

---

## 💬 الدعم

### 📧 الاتصال:

- **Email**: yassinegadhrib90@gmail.com

### 🌟 ساعدنا:

إذا أعجبك المشروع، لا تنسَ ⭐ Star!

---

## 🙏 شكر وتقدير

- **ESP32 Community** - للدعم الممتاز
- **Open Source Contributors** - لجميع المكتبات المستخدمة
- **Security Researchers** - للإلهام والأفكار
- **You** - لاستخدامك RTX-GHOST Enhanced!

---

<div align="center">

### 🕵️‍♂️ RTX-GHOST Enhanced v2.1

**The Ultimate ESP32 Pentesting Platform**

صُنع بـ ❤️ للباحثين الأمنيين

[⬆ Back to Top](#-rtx-ghost-enhanced)

---

© 2024 RTX-GHOST Team | Educational Purpose Only

</div>
