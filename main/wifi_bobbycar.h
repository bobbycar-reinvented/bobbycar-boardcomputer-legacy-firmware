#pragma once

// 3rdparty lib includes
#include <espwifistack.h>

// local includes
#include "globals.h"

namespace {
wifi_stack::config wifi_create_config()
{
    static wifi_stack::config config {
        .wifiEnabled = true,
        .hostname = deviceName,
        .sta = {
            .wifis = std::array<wifi_stack::wifi_entry, 10> {
                wifi_stack::wifi_entry { .ssid = "realraum",            .key = "r3alraum" },
                wifi_stack::wifi_entry { .ssid = "McDonalds Free WiFi", .key = "Passwort_123" },
                wifi_stack::wifi_entry { .ssid = {},                    .key = {} },
                wifi_stack::wifi_entry { .ssid = {},                    .key = {} },
                wifi_stack::wifi_entry { .ssid = {},                    .key = {} },
                wifi_stack::wifi_entry { .ssid = {},                    .key = {} },
                wifi_stack::wifi_entry { .ssid = {},                    .key = {} },
                wifi_stack::wifi_entry { .ssid = {},                    .key = {} },
                wifi_stack::wifi_entry { .ssid = {},                    .key = {} },
                wifi_stack::wifi_entry { .ssid = {},                    .key = {} }
            },
            .min_rssi = -90
        },
        .ap = {
            .ssid = deviceName,
            .key = STRING(AP_PASSWORD),
            .static_ip = {
                .ip = {10, 0, 0, 1},
                .subnet = {255, 255, 255, 0},
                .gateway = {10, 0, 0, 1},
            },
            .channel = 1,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .ssid_hidden = false,
            .max_connection = 4,
            .beacon_interval = 100
        }
    };

    return config;
}

void wifi_begin()
{
    wifi_stack::init(wifi_create_config());
    //bootLabel.redraw("setHostname");
    //if (!WiFi.setHostname(deviceName))
    //{
        //Serial.println("Could not setHostname");
    //}
    //printMemoryStats("setHostname()");

    //bootLabel.redraw("softAPsetHostname");
    //if (!WiFi.softAPsetHostname(deviceName))
    //{
        //Serial.println("Could not softAPsetHostname");
    //}
    //printMemoryStats("softAPsetHostname()");

    //bootLabel.redraw("WiFi mode");
    //if (!WiFi.mode(settings.wifiSettings.autoWifiMode))
    //{
        //Serial.println("Could not set mode to WIFI_AP_STA");
    //}
    //printMemoryStats("WiFi.mode()");

    //if (settings.wifiSettings.autoEnableAp)
    //{
        //bootLabel.redraw("WiFi softAp");
        //WifiSoftApAction{}.triggered();
        //printMemoryStats("WifiSoftApAction()");
    //}

    //bootLabel.redraw("WiFi begin");
    //if (!WiFi.begin("realraum", "r3alraum"))
    //{
        //Serial.println("Could not begin WiFi");
    //}
    //printMemoryStats("WiFi.begin()");
}

void wifi_update()
{
    wifi_stack::update(wifi_create_config());
}
} // namespace
