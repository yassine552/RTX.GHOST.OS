# 📥 دليل التثبيت الكامل - RTX-GHOST Enhanced

## المتطلبات الأساسية

### 🔧 Hardware
- **ESP32** (ESP32-WROOM-32 or ESP32-S3)
- **TFT Display** 240x320 (ILI9341 or ST7789)
- **MicroSD Card** (اختياري)
- **PN532 NFC Module** (اختياري)
- **GPS Module** (NEO-6M أو أفضل) (اختياري)
- **IR LED + Receiver** (اختياري)
- **بطارية Li-Ion** 3.7V (موصى به)

### 💻 Software
- Arduino IDE 2.0+ أو PlatformIO
- Python 3.8+ (لأدوات مساعدة)
- ESP32 Board Package

---

## خطوة 1: تثبيت Arduino IDE

### Windows:
```powershell
# تحميل من الموقع الرسمي
https://www.arduino.cc/en/software

# أو عبر Winget
winget install ArduinoSA.IDE.stable
```

### Linux:
```bash
wget https://downloads.arduino.cc/arduino-ide/arduino-ide_2.2.1_Linux_64bit.AppImage
chmod +x arduino-ide_2.2.1_Linux_64bit.AppImage
./arduino-ide_2.2.1_Linux_64bit.AppImage
```

---

## خطوة 2: إضافة ESP32 Board

1. فتح Arduino IDE
2. File → Preferences
3. في "Additional Board Manager URLs" أضف:
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
4. Tools → Board → Boards Manager
5. ابحث عن "esp32"
6. Install "esp32 by Espressif Systems"

---

## خطوة 3: تثبيت المكتبات المطلوبة

### طريقة 1: عبر Arduino IDE
Tools → Manage Libraries → ابحث عن وثبّت:

- ✅ **TFT_eSPI** by Bodmer
- ✅ **ArduinoJson** by Benoit Blanchon
- ✅ **UniversalTelegramBot** by Brian Lough
- ✅ **PubSubClient** by Nick O'Leary
- ✅ **QRCode** by Richard Moore
- ✅ **Button2** by Lennart Hennigs
- ✅ **TinyGPSPlus** by Mikal Hart
- ✅ **Adafruit PN532** by Adafruit
- ✅ **IRremoteESP8266** by crankyoldgit
- ✅ **NeoPixelBus** by Makuna

### طريقة 2: عبر PlatformIO (موصى به)
```bash
# استنساخ المشروع
git clone https://github.com/yourusername/RTX-GHOST-Enhanced
cd RTX-GHOST-Enhanced

# PlatformIO سيثبت كل شيء تلقائياً
pio run
```

---

## خطوة 4: إعداد TFT_eSPI

1. انتقل إلى مجلد المكتبة:
```
C:\Users\[USERNAME]\Documents\Arduino\libraries\TFT_eSPI
```

2. افتح `User_Setup.h`

3. اختر نوع الشاشة (مثال ILI9341):
```cpp
#define ILI9341_DRIVER

#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST   4

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8

#define SPI_FREQUENCY  40000000
```

---

## خطوة 5: إعداد المشروع

1. افتح `config.h`
2. عدّل الإعدادات:

```cpp
// Telegram Bot
#define BOT_TOKEN "1234567890:ABCdefGHIjklMNOpqrsTUVwxyz"
#define CHAT_ID "123456789"

// MQTT
#define MQTT_SERVER "your-broker.com"
#define MQTT_USER "username"
#define MQTT_PASSWORD "password"

// Cloud Storage
#define GOOGLE_DRIVE_TOKEN "your_token"
#define DROPBOX_TOKEN "your_token"
```

---

## خطوة 6: التوصيلات

### TFT Display (ILI9341):
```
ESP32    →    TFT
-----------------
3.3V     →    VCC
GND      →    GND
GPIO 23  →    MOSI/SDA
GPIO 18  →    SCK/SCL
GPIO 15  →    CS
GPIO 2   →    DC
GPIO 4   →    RST
GPIO 19  →    MISO
```

### PN532 NFC (I2C):
```
ESP32    →    PN532
-------------------
3.3V     →    VCC
GND      →    GND
GPIO 21  →    SDA
GPIO 22  →    SCL
```

### GPS Module:
```
ESP32    →    GPS
-----------------
5V       →    VCC
GND      →    GND
GPIO 16  →    TX
GPIO 17  →    RX
```

### IR LED:
```
ESP32    →    IR LED
--------------------
GPIO 25  →    Anode (+)
GND      →    Cathode (-) + 220Ω resistor
```

### Battery:
```
ESP32    →    Battery
---------------------
GPIO 34  →    VBAT (voltage divider)
GND      →    GND
```

---

## خطوة 7: رفع الكود

1. افتح `RTX_GHOST_Ultimate.ino`
2. Tools → Board → ESP32 Dev Module
3. Tools → Port → اختر المنفذ الصحيح
4. Tools → Upload Speed → 921600
5. اضغط Upload ✅

---

## خطوة 8: التحقق من التثبيت

1. افتح Serial Monitor (115200 baud)
2. يجب أن ترى:
```
🚀 RTX-GHOST Enhanced Starting...
✅ SPIFFS Initialized
✅ TFT Display Ready
✅ WiFi Ready
✅ BLE Ready
✅ System Ready
```

---

## خطوة 9: الوصول للنظام

### عبر Wi-Fi:
```
SSID: RTX-GHOST-ENHANCED
Password: ghost123456
URL: http://192.168.4.1
```

### عبر Telegram:
أرسل `/start` للبوت

### عبر MQTT:
```
Topic: rtxghost/control/scan
Payload: {"action": "start"}
```

---

## 🐛 حل المشاكل الشائعة

### المشكلة 1: خطأ في الترجمة (Compilation Error)
```
الحل: تأكد من تثبيت جميع المكتبات
```

### المشكلة 2: لا تظهر الشاشة
```
الحل: 
1. تحقق من التوصيلات
2. راجع إعدادات TFT_eSPI
3. جرب شاشة اختبار
```

### المشكلة 3: لا يمكن الاتصال بالـ WiFi
```
الحل:
1. تحقق من اسم الشبكة وكلمة المرور
2. أعد تشغيل ESP32
3. تحقق من قوة الإشارة
```

### المشكلة 4: Telegram Bot لا يعمل
```
الحل:
1. تحقق من صحة BOT_TOKEN و CHAT_ID
2. تأكد من اتصال الإنترنت
3. تحقق من عدم حظر IP
```

---

## 📊 اختبارات ما بعد التثبيت

### Test 1: Wi-Fi Scan
```cpp
/scan
```

### Test 2: Telegram
```cpp
/status
```

### Test 3: MQTT
```bash
mosquitto_pub -h broker.hivemq.com -t rtxghost/control/scan -m "start"
```

### Test 4: Web Interface
```
افتح: http://192.168.4.1
```

---

## 🔄 التحديثات (OTA)

### عبر Web Interface:
1. Settings → OTA Update
2. اختر ملف .bin
3. Upload

### عبر Arduino IDE:
1. Tools → Port → Network Port
2. اختر RTX-GHOST
3. Upload

---

## 📱 تطبيق Android Companion (قريباً)

```
سيتم إصدار تطبيق Android للتحكم الكامل
```

---

## 🎓 الخطوات التالية

1. ✅ اقرأ `README.md` للمميزات الكاملة
2. ✅ راجع `QUICKSTART.md` للاستخدام السريع
3. ✅ استكشف الواجهة و API
4. ✅ انضم للمجتمع على GitHub
5. ✅ ساهم في التطوير

---

**تم التثبيت بنجاح! 🎉**

استمتع باستخدام RTX-GHOST Enhanced! 🕵️‍♂️
