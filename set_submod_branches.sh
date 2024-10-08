#!/bin/bash

( pushd esp-idf ; git checkout fixes ; git pull ) &
( pushd esp-protocols ; git checkout fixes ; git pull ) &
( pushd components/arduino-esp32 ; git checkout remove-lowquality-parts ; git pull ) &
( pushd components/ArduinoJson ; git checkout esp-idf-refactoring ; git pull ) &
( pushd components/bobbycar-protocol ; git checkout master ; git pull ) &
( pushd components/cpputils ; git checkout main ; git pull ) &
( pushd components/cxx-ring-buffer ; git checkout esp-idf ; git pull ) &
( pushd components/date ; git checkout esp-idf-refactoring ; git pull ) &
( pushd components/esp-gui-lib ; git checkout main ; git pull ) &
( pushd components/esp-nimble-cpp ; git checkout remove-arduino-bullshit ; git pull ) &
( pushd components/espasynchttpreq ; git checkout master ; git pull ) &
( pushd components/espasyncota ; git checkout main ; git pull ) &
( pushd components/espchrono ; git checkout main ; git pull ) &
( pushd components/espconfiglib ; git checkout main ; git pull ) &
( pushd components/espcpputils ; git checkout main ; git pull ) &
( pushd components/esphttpdutils ; git checkout main ; git pull ) &
( pushd components/espwifistack ; git checkout main ; git pull ) &
( pushd components/expected ; git checkout esp-idf-fixes ; git pull ) &
( pushd components/FastLED-idf ; git checkout fixes ; git pull ) &
( pushd components/fmt ; git checkout esp-idf-rewrite ; git pull ) &
( pushd components/QRCode-esp32 ; git checkout fixes ; git pull ) &
( pushd components/sunset ; git checkout fixes ; git pull ) &
( pushd components/TFT_eSPI ; git checkout esp-idf-fixes ; git pull ) &
wait
