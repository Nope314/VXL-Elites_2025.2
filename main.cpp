/*
//Bluetooth
#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>

#define ESP32_ADDR 0x55 //7 bit address, no bit read/write bit
#define LED_PIN 2

BluetoothSerial SerialBT; //class BluetoothSerial, SerialBT is an object of class BluetoothSerial(object dùng để giao tiếp Bluetooth)

char txBuf[64];
uint8_t txLen = 0;
uint8_t currentCmd = 0;

void onReceive(int len)
{
    if(len <= 0)
        return;

    currentCmd = Wire.read();

    // Chỉ nhận CMD, chuẩn bị đọc 
    if(len == 1)
    {
        return;
    }

    txLen = 0;

    while(Wire.available() && txLen < sizeof(txBuf)-1)
    {
        txBuf[txLen++] = Wire.read();
    }   

    txBuf[txLen] = '\0';

    // Chỉ in khi thực sự có dữ liệu
    if(txLen > 0)
    {
        Serial.print("Receive: ");
        Serial.println(txBuf);
    }
}

void onRequest()
{
    Wire.write((uint8_t *)txBuf, txLen);

    Serial.print("Master Read: ");
    Serial.println(txBuf);
    Serial.println(txLen);
}

void setup()
{
   pinMode(LED_PIN, OUTPUT);
digitalWrite(LED_PIN, LOW);

Serial.begin(9600);

SerialBT.begin("ESP32_BLUETOOTH"); // Bluetooth device name

Wire.begin(ESP32_ADDR);

Wire.onReceive(onReceive);

Wire.onRequest(onRequest);

Serial.println("ESP32 Slave Ready");
Serial.println("Bluetooth Ready");

}

void loop()
{
    if (SerialBT.available())
    {
        String cmd = SerialBT.readStringUntil('\n');

        cmd.trim();

        Serial.print("Bluetooth: ");
        Serial.println(cmd);

        if(cmd == "bat led cho toi")
        {
            digitalWrite(LED_PIN, HIGH);

            SerialBT.println("Da bat LED");

            Serial.println("LED ON");
        }
        else if(cmd == "tat led")
        {
            digitalWrite(LED_PIN, LOW);

            SerialBT.println("Da tat LED");

            Serial.println("LED OFF");
        }
        else
        {
            SerialBT.println("Khong hieu lenh");
        }
    }
}
*/
//BLE(Bluetooth Low Energy)
#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LED_PIN 2

// UUID (có thể tự đặt)
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcdefab-1234-5678-1234-abcdefabcdef"

BLECharacteristic *pCharacteristic;

class MyCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        String value = pCharacteristic->getValue().c_str(); 

        if (value.length() > 0)
        {
            Serial.print("Received: ");
            Serial.println(value);

            if (value == "1")
            {
                digitalWrite(LED_PIN, HIGH);
                Serial.println("LED ON");
            }
            else if (value == "0")
            {
                digitalWrite(LED_PIN, LOW);
                Serial.println("LED OFF");
            }
        }
    }
};

void setup()
{
    Serial.begin(9600);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    BLEDevice::init("ESP32_BLE");

    BLEServer *pServer = BLEDevice::createServer();

    BLEService *pService = pServer->createService(SERVICE_UUID);

    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY);

    pCharacteristic->setCallbacks(new MyCallbacks());

    pCharacteristic->setValue("Hello");

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

    pAdvertising->addServiceUUID(SERVICE_UUID);

    pAdvertising->start();

    Serial.println("BLE Started");
}

void loop()
{
}