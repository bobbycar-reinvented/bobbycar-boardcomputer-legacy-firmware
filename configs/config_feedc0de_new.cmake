set(BOBBY_APP_NAME bobbyquad_feedc0de)
set(BOBBY_DEFAULT_USERNAME feedc0de)

set(BOBBYCAR_BUILDFLAGS
# Pins
#    -DFEATURE_JOYSTICK
#    -DPINS_RX1=4
#    -DPINS_TX1=5
#    -DPINS_RX2=22
#    -DPINS_TX2=23
    -DPINS_MOSFET0=4
    -DPINS_MOSFET1=5
    -DPINS_MOSFET2=25
#    -DPINS_GAMETRAKX=34
#    -DPINS_GAMETRAKY=39
#    -DPINS_GAMETRAKDIST=36
    -DPINS_LEDBACKLIGHT=23
    -DPINS_LEDSTRIP=26

# Config flags
    -DFEATURE_ADC_IN
    -DFEATURE_CAN
#    -DFEATURE_SERIAL
#    -DFEATURE_MOSFETS
#    -DFEATURE_BLUETOOTH
#    -DFEATURE_BMS
#    -DFEATURE_GAMETRAK
#    -DFEATURE_POWERSUPPLY
    -DFEATURE_LEDBACKLIGHT

#    -DLEDBACKLIGHT_INVERTED
#    -DLEDSTRIP_WRONG_DIRECTION
#    -DHEAP_LRGST_CRASH_TEXT_FIX

# Default values
    -DDEFAULT_SWAPSCREENBYTES=false
    -DDEFAULT_INVERTFRONTLEFT=false
    -DDEFAULT_INVERTFRONTRIGHT=true
    -DDEFAULT_INVERTBACKLEFT=false
    -DDEFAULT_INVERTBACKRIGHT=true
    -DDEFAULT_WHEELDIAMETER=255
    -DDEFAULT_IMOTMAX=40
    -DDEFAULT_IDCMAX=42
    -DDEFAULT_NMOTMAX=2000
    -DDEFAULT_FIELDWEAKMAX=17
    -DDEFAULT_FIELDADVMAX=40

# DPAD
    -DDPAD_BOARDCOMPUTER_V2
    -DPINS_DPAD_BOARDCOMPUTER_V2_OUT1=19
    -DPINS_DPAD_BOARDCOMPUTER_V2_OUT2=5
    -DPINS_DPAD_BOARDCOMPUTER_V2_IN1=4
    -DPINS_DPAD_BOARDCOMPUTER_V2_IN2=18
    -DPINS_DPAD_BOARDCOMPUTER_V2_IN3=27
    -DPINS_DPAD_BOARDCOMPUTER_V2_IN4=16
)
