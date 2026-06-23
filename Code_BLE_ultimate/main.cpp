//code real
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// UART 
#define UART_RX 16      // ESP32 RX <- Bluepill TX
#define UART_TX 17      // ESP32 TX -> Bluepill RX

// BLE UUID 
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcdefab-1234-5678-1234-abcdefabcdef"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// Callback khi iPhone kết nối/ngắt kết nối
class MyServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        deviceConnected = true;
        Serial.println("BLE Connected");
    }
    void onDisconnect(BLEServer *pServer)
    {
        deviceConnected = false;
        Serial.println("BLE Disconnected");
        BLEDevice::startAdvertising();
    }
};
// Callback khi iPhone ghi dữ liệu
class MyCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        String rx = pCharacteristic->getValue().c_str();

        if (rx.length() > 0)
        {
            Serial.print("BLE Receive: ");
            Serial.println(rx);
            // Gửi sang Bluepill
            Serial1.println(rx);
           /* // Echo lại iPhone
            pCharacteristic->setValue(("Send: " + rx).c_str());
            pCharacteristic->notify();*/
        }
    }
};

void setup()
{
    // USB Debug
    Serial.begin(9600);

    // UART với Bluepill
    Serial1.begin(9600, SERIAL_8N1, UART_RX, UART_TX);

    Serial.println("Starting BLE...");

    BLEDevice::init("ESP32_BLE");

    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY);

    pCharacteristic->setCallbacks(new MyCallbacks());

    pCharacteristic->addDescriptor(new BLE2902());

    pCharacteristic->setValue("ESP32 Ready");

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();

    Serial.println("BLE Advertising...");
}

void loop()
{
    // Bluepill -> iPhone
    while (Serial1.available())
    {
        char c = Serial1.read();

        Serial.write(c);

        if (deviceConnected)
        {
            char buf[2];
            buf[0] = c;
            buf[1] = '\0';

            pCharacteristic->setValue(buf);
            pCharacteristic->notify();
        }
    }

    delay(5);
}
//debug code
/*

#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// UART ===
#define UART_RX 16      // ESP32 RX <- Bluepill TX
#define UART_TX 17      // ESP32 TX -> Bluepill RX

// BLE UUID ===============
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcdefab-1234-5678-1234-abcdefabcdef"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

void setup()
{
    Serial.begin(9600);

    Serial1.begin(9600, SERIAL_8N1, 16, 17);

    Serial.println("ESP32 Start");
}

void loop()
{
    while (Serial.available())
    {
        char c = Serial.read();

        Serial.print("USB Receive: ");
        Serial.println(c);

        Serial1.write(c);
    }
}
    */