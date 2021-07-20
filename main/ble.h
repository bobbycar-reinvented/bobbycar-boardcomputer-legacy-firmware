#pragma once

// 3rdparty lib includes
#include <ArduinoJson.h>
#ifdef FEATURE_BLE
#include <NimBLEDevice.h>
#endif

// local includes
#include "globals.h"
#include "futurecpp.h"

namespace {
#ifdef FEATURE_BLE
BLEServer *pServer{};
BLEService *pService{};
BLECharacteristic *livestatsCharacteristic{};
BLECharacteristic *remotecontrolCharacteristic{};

void initBle()
{
    BLEDevice::init(deviceName);

    const auto serviceUuid{"0335e46c-f355-4ce6-8076-017de08cee98"};

    pServer = BLEDevice::createServer();

    pService = pServer->createService(serviceUuid);

    livestatsCharacteristic = pService->createCharacteristic("a48321ea-329f-4eab-a401-30e247211524", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    remotecontrolCharacteristic = pService->createCharacteristic("4201def0-a264-43e6-946b-6b2d9612dfed", NIMBLE_PROPERTY::WRITE);

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(serviceUuid);
    pAdvertising->setScanResponse(true);
    BLEDevice::startAdvertising();
}

void handleBle()
{
    if (livestatsCharacteristic->getSubscribedCount())
    {
        StaticJsonDocument<1024> doc;
        {
            auto arr = doc.createNestedArray("v");
            if (controllers.front.feedbackValid)
                arr.add(fixBatVoltage(controllers.front.feedback.batVoltage));
            else
                arr.add(nullptr);
            if (controllers.back.feedbackValid)
                arr.add(fixBatVoltage(controllers.back.feedback.batVoltage));
            else
                arr.add(nullptr);
        }

        {
            auto arr = doc.createNestedArray("t");
            if (controllers.front.feedbackValid)
                arr.add(fixBoardTemp(controllers.front.feedback.boardTemp));
            else
                arr.add(nullptr);
            if (controllers.back.feedbackValid)
                arr.add(fixBoardTemp(controllers.back.feedback.boardTemp));
            else
                arr.add(nullptr);
        }

        {
            auto arr = doc.createNestedArray("e");
            if (controllers.front.feedbackValid)
            {
                arr.add(controllers.front.feedback.left.error);
                arr.add(controllers.front.feedback.right.error);
            }
            else
            {
                arr.add(nullptr);
                arr.add(nullptr);
            }
            if (controllers.back.feedbackValid)
            {
                arr.add(controllers.back.feedback.left.error);
                arr.add(controllers.back.feedback.right.error);
            }
            else
            {
                arr.add(nullptr);
                arr.add(nullptr);
            }
        }

        {
            auto arr = doc.createNestedArray("s");
            if (controllers.front.feedbackValid)
            {
                arr.add(convertToKmh(controllers.front.feedback.left.speed * (settings.controllerHardware.invertFrontLeft ? -1 : 1)));
                arr.add(convertToKmh(controllers.front.feedback.right.speed * (settings.controllerHardware.invertFrontRight ? -1 : 1)));
            }
            else
            {
                arr.add(nullptr);
                arr.add(nullptr);
            }
            if (controllers.back.feedbackValid)
            {
                arr.add(convertToKmh(controllers.back.feedback.left.speed * (settings.controllerHardware.invertBackLeft ? -1 : 1)));
                arr.add(convertToKmh(controllers.back.feedback.right.speed * (settings.controllerHardware.invertBackRight ? -1 : 1)));
            }
            else
            {
                arr.add(nullptr);
                arr.add(nullptr);
            }
        }

        {
            auto arr = doc.createNestedArray("a");
            if (controllers.front.feedbackValid)
            {
                arr.add(fixCurrent(controllers.front.feedback.left.dcLink));
                arr.add(fixCurrent(controllers.front.feedback.right.dcLink));
            }
            else
            {
                arr.add(nullptr);
                arr.add(nullptr);
            }
            if (controllers.back.feedbackValid)
            {
                arr.add(fixCurrent(controllers.back.feedback.left.dcLink));
                arr.add(fixCurrent(controllers.back.feedback.right.dcLink));
            }
            else
            {
                arr.add(nullptr);
                arr.add(nullptr);
            }
        }

        std::string json;
        serializeJson(doc, json);

        livestatsCharacteristic->setValue(json);
        livestatsCharacteristic->notify();
    }
}
#endif
}
