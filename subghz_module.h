// █████████████████████████████████████████████████████████
// 📡 RTX-GHOST - وحدة SubGHz المتقدمة (433MHz/315MHz)
// █████████████████████████████████████████████████████████

#ifndef SUBGHZ_MODULE_H
#define SUBGHZ_MODULE_H

#include <Arduino.h>
#include <SPI.h>
#include "config.h"

// دعم وحدات SubGHz الشائعة
// CC1101 - الأكثر شيوعاً واحترافية
// RFM69 - بديل جيد

// ════════════════════════════════════════════════════════
// 🔧 إعدادات CC1101
// ════════════════════════════════════════════════════════

#define CC1101_CS_PIN    5
#define CC1101_GDO0_PIN  4
#define CC1101_GDO2_PIN  2
#define CC1101_MOSI_PIN  23
#define CC1101_MISO_PIN  19
#define CC1101_SCK_PIN   18

// ترددات شائعة
#define FREQ_315MHZ  315000000
#define FREQ_433MHZ  433920000
#define FREQ_868MHZ  868000000
#define FREQ_915MHZ  915000000

// معدلات البث
#define BAUD_1200    1200
#define BAUD_2400    2400
#define BAUD_4800    4800
#define BAUD_9600    9600
#define BAUD_38400   38400

// ════════════════════════════════════════════════════════
// 📊 بروتوكولات SubGHz المدعومة
// ════════════════════════════════════════════════════════

enum SubGHzProtocol {
    PROTOCOL_PRINCETON,
    PROTOCOL_RCSWITCH,
    PROTOCOL_CAME,
    PROTOCOL_HOLTEC,
    PROTOCOL_NICE,
    PROTOCOL_STARLINE,
    PROTOCOL_KEELOQ,
    PROTOCOL_RAW,
    PROTOCOL_AUTO
};

// ════════════════════════════════════════════════════════
// 🔐 هياكل البيانات
// ════════════════════════════════════════════════════════

struct SubGHzSignal {
    SubGHzProtocol protocol;
    uint32_t frequency;
    uint32_t data;
    uint8_t bitCount;
    uint16_t pulseLength;
    uint8_t repeat;
    String name;
    uint32_t timestamp;
    std::vector<uint16_t> rawData;
};

struct SubGHzDevice {
    String name;
    SubGHzProtocol protocol;
    uint32_t frequency;
    uint32_t code;
    uint8_t bitCount;
};

// ════════════════════════════════════════════════════════
// 📡 CC1101 Registers
// ════════════════════════════════════════════════════════

#define CC1101_IOCFG2       0x00
#define CC1101_IOCFG1       0x01
#define CC1101_IOCFG0       0x02
#define CC1101_FIFOTHR      0x03
#define CC1101_SYNC1        0x04
#define CC1101_SYNC0        0x05
#define CC1101_PKTLEN       0x06
#define CC1101_PKTCTRL1     0x07
#define CC1101_PKTCTRL0     0x08
#define CC1101_ADDR         0x09
#define CC1101_CHANNR       0x0A
#define CC1101_FSCTRL1      0x0B
#define CC1101_FSCTRL0      0x0C
#define CC1101_FREQ2        0x0D
#define CC1101_FREQ1        0x0E
#define CC1101_FREQ0        0x0F
#define CC1101_MDMCFG4      0x10
#define CC1101_MDMCFG3      0x11
#define CC1101_MDMCFG2      0x12
#define CC1101_MDMCFG1      0x13
#define CC1101_MDMCFG0      0x14
#define CC1101_DEVIATN      0x15

// Command Strobes
#define CC1101_SRES         0x30
#define CC1101_SFSTXON      0x31
#define CC1101_SCAL         0x33
#define CC1101_SRX          0x34
#define CC1101_STX          0x35
#define CC1101_SIDLE        0x36

// ════════════════════════════════════════════════════════
// 🎯 Class SubGHz
// ════════════════════════════════════════════════════════

class SubGHz {
private:
    SPIClass* spi;
    std::vector<SubGHzSignal> capturedSignals;
    std::vector<SubGHzDevice> knownDevices;
    
    bool isInitialized = false;
    bool isReceiving = false;
    bool isTransmitting = false;
    bool isJamming = false;
    
    uint32_t currentFrequency = FREQ_433MHZ;
    SubGHzProtocol currentProtocol = PROTOCOL_AUTO;

    // ════════════════════════════════════════════════════════
    // 🔧 CC1101 Low-Level Functions
    // ════════════════════════════════════════════════════════
    
    void writeReg(uint8_t addr, uint8_t value) {
        digitalWrite(CC1101_CS_PIN, LOW);
        spi->transfer(addr);
        spi->transfer(value);
        digitalWrite(CC1101_CS_PIN, HIGH);
    }
    
    uint8_t readReg(uint8_t addr) {
        digitalWrite(CC1101_CS_PIN, LOW);
        spi->transfer(addr | 0x80);
        uint8_t value = spi->transfer(0);
        digitalWrite(CC1101_CS_PIN, HIGH);
        return value;
    }
    
    void writeCommand(uint8_t cmd) {
        digitalWrite(CC1101_CS_PIN, LOW);
        spi->transfer(cmd);
        digitalWrite(CC1101_CS_PIN, HIGH);
    }
    
    void reset() {
        digitalWrite(CC1101_CS_PIN, LOW);
        delayMicroseconds(10);
        digitalWrite(CC1101_CS_PIN, HIGH);
        delayMicroseconds(40);
        writeCommand(CC1101_SRES);
        delay(10);
    }
    
    void setFrequency(uint32_t freq) {
        // حساب قيمة التردد لـ CC1101
        uint32_t freqReg = (freq / 26000000.0) * 65536;
        
        writeReg(CC1101_FREQ2, (freqReg >> 16) & 0xFF);
        writeReg(CC1101_FREQ1, (freqReg >> 8) & 0xFF);
        writeReg(CC1101_FREQ0, freqReg & 0xFF);
        
        currentFrequency = freq;
    }
    
    void setModulation(uint8_t mod) {
        uint8_t mdmcfg2 = readReg(CC1101_MDMCFG2);
        mdmcfg2 = (mdmcfg2 & 0x8F) | (mod << 4);
        writeReg(CC1101_MDMCFG2, mdmcfg2);
    }
    
    void setDataRate(uint32_t baud) {
        // حساب معدل البيانات
        uint16_t drate = (baud * 65536.0) / 26000000.0;
        writeReg(CC1101_MDMCFG4, 0xCA);
        writeReg(CC1101_MDMCFG3, drate & 0xFF);
    }

public:
    SubGHz() {
        spi = new SPIClass(VSPI);
        capturedSignals.reserve(100);
        loadKnownDevices();
    }
    
    // ════════════════════════════════════════════════════════
    // 🚀 التهيئة
    // ════════════════════════════════════════════════════════
    
    bool begin() {
        pinMode(CC1101_CS_PIN, OUTPUT);
        pinMode(CC1101_GDO0_PIN, INPUT);
        pinMode(CC1101_GDO2_PIN, INPUT);
        
        digitalWrite(CC1101_CS_PIN, HIGH);
        
        spi->begin(CC1101_SCK_PIN, CC1101_MISO_PIN, CC1101_MOSI_PIN, CC1101_CS_PIN);
        spi->setFrequency(1000000);
        
        reset();
        delay(100);
        
        // التحقق من الاتصال
        uint8_t partnum = readReg(0xF0);
        uint8_t version = readReg(0xF1);
        
        if (partnum != 0x00) {
            Serial.printf("✅ CC1101 اكتُشف: PartNum=0x%02X, Version=0x%02X\n", partnum, version);
            
            configureCC1101();
            isInitialized = true;
            return true;
        } else {
            Serial.println("❌ فشل اكتشاف CC1101");
            return false;
        }
    }
    
    void configureCC1101() {
        // إعدادات افتراضية محسّنة
        writeReg(CC1101_IOCFG2, 0x0D);    // GDO2 output pin config
        writeReg(CC1101_IOCFG0, 0x06);    // GDO0 output pin config
        writeReg(CC1101_PKTCTRL0, 0x32);  // Packet automation control
        writeReg(CC1101_FSCTRL1, 0x06);   // Frequency synthesizer control
        
        setFrequency(FREQ_433MHZ);
        setModulation(0x00);  // 2-FSK
        setDataRate(BAUD_4800);
        
        writeReg(CC1101_MDMCFG1, 0x22);   // Modem configuration
        writeReg(CC1101_MDMCFG0, 0xF8);   // Modem configuration
        writeReg(CC1101_DEVIATN, 0x47);   // Modem deviation
        
        writeCommand(CC1101_SCAL);        // Calibrate
        delay(10);
    }
    
    // ════════════════════════════════════════════════════════
    // 📻 استقبال الإشارات
    // ════════════════════════════════════════════════════════
    
    void startReceiving(uint32_t freq = 0) {
        if (!isInitialized) return;
        
        if (freq > 0) setFrequency(freq);
        
        writeCommand(CC1101_SRX);
        isReceiving = true;
        
        Serial.printf("📡 بدء الاستقبال على %d MHz\n", currentFrequency / 1000000);
    }
    
    void stopReceiving() {
        writeCommand(CC1101_SIDLE);
        isReceiving = false;
        Serial.println("⏹️ إيقاف الاستقبال");
    }
    
    SubGHzSignal* receiveSignal(uint32_t timeout = 5000) {
        if (!isReceiving) startReceiving();
        
        uint32_t start = millis();
        
        while (millis() - start < timeout) {
            if (digitalRead(CC1101_GDO0_PIN)) {
                SubGHzSignal* signal = new SubGHzSignal();
                signal->frequency = currentFrequency;
                signal->timestamp = millis();
                
                // قراءة البيانات
                signal->protocol = detectProtocol();
                signal->data = readData();
                signal->bitCount = 24; // افتراضي
                
                capturedSignals.push_back(*signal);
                
                Serial.printf("✅ تم استقبال إشارة: Protocol=%d, Data=0x%08X\n", 
                             signal->protocol, signal->data);
                
                return signal;
            }
            delay(10);
        }
        
        return nullptr;
    }
    
    // ════════════════════════════════════════════════════════
    // 📤 إرسال الإشارات
    // ════════════════════════════════════════════════════════
    
    void sendSignal(SubGHzSignal signal) {
        if (!isInitialized) return;
        
        setFrequency(signal.frequency);
        
        writeCommand(CC1101_SIDLE);
        writeCommand(CC1101_STX);
        
        isTransmitting = true;
        
        // إرسال البيانات حسب البروتوكول
        switch (signal.protocol) {
            case PROTOCOL_PRINCETON:
                sendPrinceton(signal);
                break;
            case PROTOCOL_RCSWITCH:
                sendRCSwitch(signal);
                break;
            case PROTOCOL_CAME:
                sendCame(signal);
                break;
            case PROTOCOL_KEELOQ:
                sendKeeloq(signal);
                break;
            default:
                sendRaw(signal);
                break;
        }
        
        writeCommand(CC1101_SIDLE);
        isTransmitting = false;
        
        Serial.printf("📤 تم إرسال إشارة: %s\n", signal.name.c_str());
    }
    
    void replaySignal(int index) {
        if (index >= 0 && index < capturedSignals.size()) {
            sendSignal(capturedSignals[index]);
        }
    }
    
    void replayLastSignal() {
        if (!capturedSignals.empty()) {
            sendSignal(capturedSignals.back());
        }
    }
    
    // ════════════════════════════════════════════════════════
    // 🎯 بروتوكولات محددة
    // ════════════════════════════════════════════════════════
    
    void sendPrinceton(SubGHzSignal signal) {
        uint16_t pulseLength = signal.pulseLength > 0 ? signal.pulseLength : 350;
        
        for (int r = 0; r < signal.repeat; r++) {
            for (int i = signal.bitCount - 1; i >= 0; i--) {
                if (signal.data & (1 << i)) {
                    // Bit 1: high-low-low-high
                    transmitBit(pulseLength * 3, pulseLength);
                } else {
                    // Bit 0: high-low-low-low-low-low
                    transmitBit(pulseLength, pulseLength * 3);
                }
            }
            
            // Sync bit
            transmitBit(pulseLength, pulseLength * 31);
        }
    }
    
    void sendRCSwitch(SubGHzSignal signal) {
        uint16_t pulseLength = signal.pulseLength > 0 ? signal.pulseLength : 350;
        
        for (int r = 0; r < signal.repeat; r++) {
            for (int i = signal.bitCount - 1; i >= 0; i--) {
                if (signal.data & (1 << i)) {
                    transmitBit(pulseLength * 3, pulseLength);
                } else {
                    transmitBit(pulseLength, pulseLength * 3);
                }
            }
            transmitBit(pulseLength, pulseLength * 31);
        }
    }
    
    void sendCame(SubGHzSignal signal) {
        // بروتوكول Came 12-bit
        for (int r = 0; r < signal.repeat; r++) {
            for (int i = 11; i >= 0; i--) {
                if (signal.data & (1 << i)) {
                    transmitBit(320, 640);
                } else {
                    transmitBit(640, 320);
                }
            }
        }
    }
    
    void sendKeeloq(SubGHzSignal signal) {
        // بروتوكول KeeLoq المشفر
        // يحتاج مفتاح تشفير - هنا إرسال بسيط
        uint16_t te = 400;
        
        for (int r = 0; r < signal.repeat; r++) {
            // Preamble
            for (int i = 0; i < 12; i++) {
                transmitBit(te, te);
            }
            
            // Data (66 bits)
            for (int i = 65; i >= 0; i--) {
                if (signal.data & (1ULL << i)) {
                    transmitBit(te * 2, te);
                } else {
                    transmitBit(te, te * 2);
                }
            }
        }
    }
    
    void sendRaw(SubGHzSignal signal) {
        // إرسال البيانات الخام
        for (size_t i = 0; i < signal.rawData.size(); i += 2) {
            if (i + 1 < signal.rawData.size()) {
                transmitBit(signal.rawData[i], signal.rawData[i + 1]);
            }
        }
    }
    
    // ════════════════════════════════════════════════════════
    // 🔊 Jammer (تشويش)
    // ════════════════════════════════════════════════════════
    
    void startJammer(uint32_t freq, uint32_t duration = 0) {
        if (!isInitialized) return;
        
        setFrequency(freq);
        writeCommand(CC1101_STX);
        
        isJamming = true;
        
        Serial.printf("🚨 بدء التشويش على %d MHz\n", freq / 1000000);
        
        if (duration > 0) {
            delay(duration);
            stopJammer();
        }
    }
    
    void stopJammer() {
        writeCommand(CC1101_SIDLE);
        isJamming = false;
        Serial.println("⏹️ إيقاف التشويش");
    }
    
    void jammerSweep(uint32_t startFreq, uint32_t endFreq, uint32_t step = 100000) {
        for (uint32_t freq = startFreq; freq <= endFreq; freq += step) {
            if (!isJamming) break;
            
            setFrequency(freq);
            writeCommand(CC1101_STX);
            delay(10);
        }
    }
    
    // ════════════════════════════════════════════════════════
    // 📊 التحليل
    // ════════════════════════════════════════════════════════
    
    void analyzeFrequency(uint32_t freq, uint32_t duration = 10000) {
        setFrequency(freq);
        startReceiving();
        
        uint32_t start = millis();
        int signalCount = 0;
        
        Serial.printf("🔍 تحليل %d MHz لمدة %d ثانية...\n", freq / 1000000, duration / 1000);
        
        while (millis() - start < duration) {
            if (receiveSignal(100)) {
                signalCount++;
            }
        }
        
        stopReceiving();
        
        Serial.printf("📊 تم اكتشاف %d إشارة\n", signalCount);
    }
    
    void scanFrequencies(uint32_t startFreq, uint32_t endFreq, uint32_t step = 100000) {
        Serial.printf("🔍 مسح من %d إلى %d MHz\n", 
                     startFreq / 1000000, endFreq / 1000000);
        
        for (uint32_t freq = startFreq; freq <= endFreq; freq += step) {
            setFrequency(freq);
            startReceiving();
            
            if (receiveSignal(500)) {
                Serial.printf("✅ نشاط على %d MHz\n", freq / 1000000);
            }
            
            stopReceiving();
        }
    }
    
    // ════════════════════════════════════════════════════════
    // 🛠️ دوال مساعدة
    // ════════════════════════════════════════════════════════
    
    void transmitBit(uint16_t high, uint16_t low) {
        digitalWrite(CC1101_GDO0_PIN, HIGH);
        delayMicroseconds(high);
        digitalWrite(CC1101_GDO0_PIN, LOW);
        delayMicroseconds(low);
    }
    
    SubGHzProtocol detectProtocol() {
        // كشف البروتوكول تلقائياً بناء على النمط
        // هنا تنفيذ بسيط - يمكن تحسينه
        return PROTOCOL_AUTO;
    }
    
    uint32_t readData() {
        // قراءة البيانات من CC1101 FIFO
        uint32_t data = 0;
        // تنفيذ القراءة الفعلية
        return data;
    }
    
    void loadKnownDevices() {
        // قاعدة بيانات أجهزة معروفة
        knownDevices.push_back({"Garage Door 1", PROTOCOL_PRINCETON, FREQ_433MHZ, 0x123456, 24});
        knownDevices.push_back({"Car Key 1", PROTOCOL_KEELOQ, FREQ_433MHZ, 0xABCDEF, 66});
        knownDevices.push_back({"Remote 1", PROTOCOL_RCSWITCH, FREQ_433MHZ, 0x789ABC, 24});
    }
    
    // ════════════════════════════════════════════════════════
    // 📋 Getters
    // ════════════════════════════════════════════════════════
    
    std::vector<SubGHzSignal>& getSignals() { return capturedSignals; }
    std::vector<SubGHzDevice>& getKnownDevices() { return knownDevices; }
    
    bool isReady() { return isInitialized; }
    bool receiving() { return isReceiving; }
    bool transmitting() { return isTransmitting; }
    bool jamming() { return isJamming; }
    
    int getSignalCount() { return capturedSignals.size(); }
    
    String protocolToString(SubGHzProtocol protocol) {
        switch (protocol) {
            case PROTOCOL_PRINCETON: return "Princeton";
            case PROTOCOL_RCSWITCH: return "RCSwitch";
            case PROTOCOL_CAME: return "Came";
            case PROTOCOL_HOLTEC: return "Holtec";
            case PROTOCOL_NICE: return "Nice";
            case PROTOCOL_STARLINE: return "StarLine";
            case PROTOCOL_KEELOQ: return "KeeLoq";
            case PROTOCOL_RAW: return "Raw";
            default: return "Auto";
        }
    }
};

#endif // SUBGHZ_MODULE_H
