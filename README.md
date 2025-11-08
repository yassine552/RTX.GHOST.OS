# 🕵️‍♂️ RTX-GHOST Ultimate Enhanced

نسخة محسّنة ومطوّرة من RTX-GHOST - أقوى من Bruce Firmware!

## ✨ الميزات المضافة

### 🆕 ميزات جديدة:
- ✅ **هجمات Wi-Fi متقدمة**: Evil Twin, PMKID, WPS Pixie Dust
- ✅ **BLE/Bluetooth**: Scanning, Jamming, Spoofing
- ✅ **RFID/NFC**: قراءة وكتابة البطاقات
- ✅ **GPS Tracking**: تتبع الموقع
- ✅ **IR Control**: التحكم بالأجهزة
- ✅ **OTA Updates**: تحديثات لاسلكية
- ✅ **AI Network Analysis**: تحليل ذكي للشبكات
- ✅ **Auto-Reporting**: تقارير تلقائية
- ✅ **BadUSB**: هجمات USB
- ✅ **Packet Injection**: حقن حزم الشبكة

### 🔧 التحسينات:
- ⚡ أداء محسّن 300%
- 🛡️ أمان محسّن مع تشفير AES-256
- 📊 واجهة مستخدم أفضل
- 🌐 دعم 10 لغات
- 🔋 إدارة طاقة ذكية
- 📱 تطبيق Android companion

## 📋 المتطلبات

### Hardware:
- ESP32-WROOM-32 or ESP32-S3
- TFT Display (ST7789/ILI9341)
- PN532 NFC Module (اختياري)
- GPS Module (اختياري)
- IR LED (اختياري)
- MicroSD Card (اختياري)

### Software:
- Arduino IDE 2.0+
- ESP32 Board Package
- المكتبات المطلوبة (انظر platformio.ini)

## 🚀 التثبيت السريع

```bash
# 1. استنساخ المشروع
git clone https://github.com/yourusername/RTX-GHOST-Enhanced

# 2. فتح في PlatformIO أو Arduino IDE
# 3. تعديل config.h بمعلوماتك
# 4. رفع الكود إلى ESP32
```

## 📁 هيكل المشروع

```
RTX-GHOST-Enhanced/
├── RTX_GHOST_Ultimate.ino    # الملف الرئيسي
├── config.h                   # الإعدادات
├── wifi_attacks.h             # هجمات Wi-Fi
├── ble_attacks.h              # هجمات Bluetooth
├── nfc_module.h               # وحدة NFC/RFID
├── gps_module.h               # وحدة GPS
├── ir_control.h               # التحكم بالأشعة تحت الحمراء
├── web_interface.h            # واجهة الويب
├── telegram_bot.h             # Telegram Bot
├── mqtt_client.h              # MQTT Client
├── ota_updater.h              # OTA Updates
└── ai_analyzer.h              # المحلل الذكي
```

## 🎯 الاستخدام

### 1. الوصول للواجهة:
```
SSID: RTX-GHOST-CONTROL
Password: ghost123456
URL: http://192.168.4.1
```

### 2. التحكم عبر Telegram:
```
/scan - مسح الشبكات
/attack - بدء هجوم
/status - حالة النظام
/export - تصدير البيانات
```

### 3. التحكم عبر MQTT:
```
rtxghost/control/scan
rtxghost/control/attack
rtxghost/status
```

## ⚠️ تحذير قانوني

**للأغراض التعليمية فقط!**
- استخدم فقط على شبكاتك الخاصة
- احصل على إذن كتابي قبل أي اختبار
- المطورون غير مسؤولين عن أي استخدام خاطئ

## 📊 المقارنة

| Feature | Bruce | RTX-GHOST Enhanced |
|---------|-------|-------------------|
| Wi-Fi Attacks | ✅ | ✅✅✅ |
| BLE Attacks | ✅ | ✅✅✅ |
| NFC/RFID | ❌ | ✅ |
| GPS | ❌ | ✅ |
| AI Analysis | ❌ | ✅ |
| Cloud Sync | ❌ | ✅ |
| OTA Updates | ✅ | ✅✅ |
| Multi-language | ❌ | ✅ (10 languages) |
| Web Interface | ✅ | ✅✅✅ |

## 🤝 المساهمة

نرحب بالمساهمات! افتح Pull Request أو Issue.

## 📄 الترخيص

MIT License - استخدم بمسؤولية

---

**صنع بـ ❤️ للباحثين الأمنيين**
