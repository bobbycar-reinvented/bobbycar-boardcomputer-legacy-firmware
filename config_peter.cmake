set(BOBBY_APP_NAME bobbyquad_peter)

add_definitions(
    -DUSER_SETUP_LOADED=1
    -DLOAD_GLCD=1
    -DLOAD_FONT2=1
    -DLOAD_FONT4=1
    -DLOAD_FONT7=1
    -DILI9341_DRIVER=1
    -DTFT_MOSI=13
    -DTFT_SCLK=15
    -DTFT_CS=14
    -DTFT_DC=12
    -DTFT_RST=2
    -DSPI_FREQUENCY=40000000
)

set(BOBBYCAR_BUILDFLAGS
    -DFEATURE_ADC_IN
    -DPINS_GAS=34
    -DPINS_BREMS=35
    -DDEFAULT_SWAPSCREENBYTES=false
    -DFEATURE_CAN
    #  -DFEATURE_SERIAL
    #  -DPINS_RX1=4
    #  -DPINS_TX1=5
    #  -DPINS_RX2=22
    #  -DPINS_TX2=23
    -DDEFAULT_INVERTFRONTLEFT=false
    -DDEFAULT_INVERTFRONTRIGHT=true
    -DDEFAULT_INVERTBACKLEFT=false
    -DDEFAULT_INVERTBACKRIGHT=true
    -DDEFAULT_WHEELDIAMETER=200
    #  -DFEATURE_MOSFETS
    #  -DPINS_MOSFET0=18
    #  -DPINS_MOSFET1=19
    #  -DPINS_MOSFET2=21
    -DDEFAULT_IMOTMAX=28
    -DDEFAULT_IDCMAX=30
    -DDEFAULT_NMOTMAX=2000
    -DDEFAULT_FIELDWEAKMAX=7
    -DDEFAULT_FIELDADVMAX=40
    -DDEVICE_PREFIX=peter_bobbyquad
    -DAP_PASSWORD=Passwort_123
    -DFEATURE_WEBSERVER
    -DFEATURE_OTA
    -DOTA_USERNAME="peter"
    -DFEATURE_DPAD_5WIRESW_2OUT
    -DPINS_DPAD_5WIRESW_OUT1=18
    -DPINS_DPAD_5WIRESW_OUT2=19
    -DPINS_DPAD_5WIRESW_IN1=4
    -DPINS_DPAD_5WIRESW_IN2=5
    -DPINS_DPAD_5WIRESW_IN3=27
    -DDPAD_5WIRESW_UP=4
    -DDPAD_5WIRESW_DOWN=7
    -DDPAD_5WIRESW_CONFIRM=1
    -DDPAD_5WIRESW_BACK=10
    -DDPAD_5WIRESW_PROFILE0=11
    -DDPAD_5WIRESW_PROFILE1=8
    -DDPAD_5WIRESW_PROFILE2=5
    -DDPAD_5WIRESW_PROFILE3=2
    -DDPAD_5WIRESW_BLINK_LEFT=9
    -DDPAD_5WIRESW_BLINK_RIGHT=0
    -DDPAD_5WIRESW_QUICKACTION_DOWN=3
    -DDPAD_5WIRESW_QUICKACTION_UP=6
    # -DDPAD_5WIRESW_DEBUG
    -DDEFAULT_GASMIN=842
    -DDEFAULT_GASMAX=2480
    -DDEFAULT_BREMSMIN=826
    -DDEFAULT_BREMSMAX=2502
    -DFEATURE_BLE
    #  -DFEATURE_BLUETOOTH
    #  -DFEATURE_BMS
    #  -DFEATURE_GAMETRAK
    #  -DPINS_GAMETRAKX=34
    #  -DPINS_GAMETRAKY=39
    #  -DPINS_GAMETRAKDIST=36
    #  -DDEFAULT_GAMETRAKXMIN=0
    #  -DDEFAULT_GAMETRAKXMAX=4095
    #  -DDEFAULT_GAMETRAKYMIN=0
    #  -DDEFAULT_GAMETRAKYMAX=4095
    #  -DDEFAULT_GAMETRAKDISTMIN=0
    #  -DDEFAULT_GAMETRAKDISTMAX=4095
    #  -DFEATURE_POWERSUPPLY
    -DFEATURE_CLOUD
    -DFEATURE_LEDBACKLIGHT
    -DPINS_LEDBACKLIGHT=23
    -DLEDBACKLIGHT_INVERTED
    -DFEATURE_GARAGE
    -DFEATURE_NTP
    -DFEATURE_WIRELESS_CONFIG
    -DFEATURE_LEDSTRIP
    -DPINS_LEDSTRIP=33
    -DLEDSTRIP_LENGTH=288
    #  -DLEDSTRIP_WRONG_DIRECTION
    -DLEDSTRIP_ANIMATION_DEFAULT=2
    -DLEDS_PER_METER=144
    -DOLD_NVS
    -DFEATURE_DNS_NS
)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ignore/lockscreen_plugin.cmake")
    include("${CMAKE_CURRENT_SOURCE_DIR}/ignore/lockscreen_plugin.cmake")
    message(WARNING "Including lockscreen_plugin")
endif()
