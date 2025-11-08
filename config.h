// █████████████████████████████████████████████████████████
// ⚙️ RTX-GHOST Ultimate Enhanced - ملف الإعدادات
// █████████████████████████████████████████████████████████

#ifndef CONFIG_H
#define CONFIG_H

// 🌐 إعدادات نقطة الوصول
#define AP_SSID "RTX-GHOST-ENHANCED"
#define AP_PASSWORD "ghost123456"
#define AP_CHANNEL 6
#define AP_HIDDEN false
#define AP_MAX_CONNECTIONS 8

// 🔐 إعدادات الأمان
#define ADMIN_PASSWORD "rtxghost2024"
#define ENABLE_2FA true
#define SESSION_TIMEOUT 3600000  // 1 ساعة
#define MAX_LOGIN_ATTEMPTS 5
#define LOCKOUT_TIME 300000  // 5 دقائق

// 📱 Telegram Bot
#define TELEGRAM_ENABLED true
#define BOT_TOKEN "YOUR_BOT_TOKEN_HERE"
#define CHAT_ID "YOUR_CHAT_ID_HERE"
#define TELEGRAM_UPDATE_INTERVAL 1000

// 🔗 MQTT Broker
#define MQTT_ENABLED true
#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_USER "rtxghost"
#define MQTT_PASSWORD "mqtt_password"
#define MQTT_CLIENT_ID "RTXGhost_"
#define MQTT_TOPIC_PREFIX "rtxghost/"

// ☁️ Cloud Storage
#define GOOGLE_DRIVE_ENABLED false
#define GOOGLE_DRIVE_TOKEN "your_token_here"
#define DROPBOX_ENABLED false
#define DROPBOX_TOKEN "your_token_here"
#define AUTO_CLOUD_BACKUP true
#define CLOUD_BACKUP_INTERVAL 3600000  // كل ساعة

// 🖥️ شاشة TFT
#define TFT_ENABLED true
#define TFT_WIDTH 240
#define TFT_HEIGHT 320
#define TFT_BRIGHTNESS 200
#define TFT_ROTATION 0
#define SCREEN_TIMEOUT 30000  // 30 ثانية

// 🔋 إدارة الطاقة
#define BATTERY_PIN 34
#define LOW_BATTERY_THRESHOLD 15.0
#define CRITICAL_BATTERY_THRESHOLD 5.0
#define AUTO_SLEEP_ENABLED true
#define SLEEP_TIMEOUT 300000  // 5 دقائق

// 📡 إعدادات Wi-Fi
#define MAX_NETWORKS_SCAN 100
#define SCAN_INTERVAL 5000
#define CHANNEL_HOP_INTERVAL 100
#define DEAUTH_INTERVAL 100
#define BEACON_INTERVAL 102400

// 🎯 إعدادات الهجمات
#define MAX_DEAUTH_CLIENTS 50
#define HANDSHAKE_TIMEOUT 60000
#define PMKID_TIMEOUT 30000
#define EVIL_TWIN_CHANNEL 6
#define WPS_PIXIE_DUST_ENABLED true

// 📶 Bluetooth/BLE
#define BLE_SCAN_TIME 30
#define BLE_SCAN_INTERVAL 100
#define BLE_SCAN_WINDOW 99
#define BT_CLASSIC_ENABLED true

// 💾 التخزين
#define USE_SPIFFS true
#define USE_SD_CARD false
#define SD_CARD_CS 5
#define MAX_LOG_SIZE 1000000  // 1MB
#define AUTO_ROTATE_LOGS true

// 🌐 إعدادات اللغة
#define DEFAULT_LANGUAGE "ar"
#define SUPPORTED_LANGUAGES {"ar", "en", "fr", "es", "de", "ru", "zh", "ja", "ko", "pt"}

// 🚨 إعدادات التنبيهات
#define ALERT_ON_NEW_NETWORK true
#define ALERT_ON_HANDSHAKE true
#define ALERT_ON_LOW_BATTERY true
#define ALERT_SOUND_ENABLED false

// 🤖 AI/ML
#define AI_ANALYSIS_ENABLED true
#define AI_AUTO_ATTACK false
#define AI_RECOMMEND_TARGETS true

// 🔄 OTA Updates
#define OTA_ENABLED true
#define OTA_PASSWORD "rtxghost_ota"
#define OTA_PORT 3232
#define AUTO_CHECK_UPDATES true
#define UPDATE_CHECK_INTERVAL 86400000  // 24 ساعة
#define UPDATE_SERVER_URL "https://your-server.com/updates"

// 📍 GPS
#define GPS_ENABLED false
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD 9600
#define GPS_UPDATE_INTERVAL 1000

// 📡 NFC/RFID
#define NFC_ENABLED false
#define NFC_SS_PIN 21
#define NFC_RST_PIN 22

// 🔴 IR Control
#define IR_ENABLED false
#define IR_SEND_PIN 25
#define IR_RECV_PIN 26

// 🎮 أزرار التحكم
#define BTN_UP_PIN 32
#define BTN_DOWN_PIN 33
#define BTN_LEFT_PIN 35
#define BTN_RIGHT_PIN 36
#define BTN_SELECT_PIN 39
#define BTN_BACK_PIN 27

// 🔊 Buzzer
#define BUZZER_ENABLED false
#define BUZZER_PIN 23

// 💡 LED
#define LED_STATUS_PIN 2
#define LED_ACTIVITY_PIN 4

// 🌈 RGB LED (Neopixel)
#define NEOPIXEL_ENABLED false
#define NEOPIXEL_PIN 13
#define NEOPIXEL_COUNT 1

// ⚡ الأداء
#define TASK_STACK_SIZE 8192
#define TASK_PRIORITY 1
#define CORE_WIFI 0
#define CORE_BLE 1
#define WATCHDOG_TIMEOUT 30

// 🐛 التصحيح
#define DEBUG_MODE false
#define SERIAL_BAUD 115200
#define LOG_LEVEL 2  // 0=NONE, 1=ERROR, 2=WARN, 3=INFO, 4=DEBUG

// 🎨 الألوان (RGB565)
#define COLOR_PRIMARY 0x07E0    // أخضر
#define COLOR_SECONDARY 0x001F  // أزرق
#define COLOR_SUCCESS 0x07E0    // أخضر
#define COLOR_DANGER 0xF800     // أحمر
#define COLOR_WARNING 0xFFE0    // أصفر
#define COLOR_INFO 0x07FF       // سماوي
#define COLOR_BACKGROUND 0x0000 // أسود
#define COLOR_TEXT 0xFFFF       // أبيض

// 📊 حدود النظام
#define MAX_SAVED_NETWORKS 1000
#define MAX_HANDSHAKES 100
#define MAX_CLIENTS 500
#define MAX_LOG_ENTRIES 1000

// 🔒 أوضاع التشغيل
#define MODE_NORMAL 0
#define MODE_STEALTH 1
#define MODE_AGGRESSIVE 2
#define MODE_PASSIVE 3

#define DEFAULT_MODE MODE_NORMAL

// ⏱️ الفواصل الزمنية
#define UI_UPDATE_INTERVAL 100
#define METRICS_UPDATE_INTERVAL 5000
#define HEARTBEAT_INTERVAL 10000

// 🎯 استراتيجيات الهجوم
#define STRATEGY_TARGETED 0
#define STRATEGY_BROADCAST 1
#define STRATEGY_SMART 2

#define DEFAULT_STRATEGY STRATEGY_SMART

#endif // CONFIG_H
