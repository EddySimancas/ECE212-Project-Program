#ifndef _Global_H
#define _Global_H

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include <Adafruit_STMPE610.h>

#ifdef ESP8266
   #define STMPE_CS 16
   #define TFT_CS   0
   #define TFT_DC   15
   #define SD_CS    2
#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
   #define STMPE_CS 32
   #define TFT_CS   15
   #define TFT_DC   33
   #define SD_CS    14
#elif defined(TEENSYDUINO)
   #define TFT_DC   10
   #define TFT_CS   4
   #define STMPE_CS 3
   #define SD_CS    8
#elif defined(ARDUINO_STM32_FEATHER)
   #define TFT_DC   PB4
   #define TFT_CS   PA15
   #define STMPE_CS PC7
   #define SD_CS    PC5
#elif defined(ARDUINO_NRF52832_FEATHER)  /* BSP 0.6.5 and higher! */
   #define TFT_DC   11
   #define TFT_CS   31
   #define STMPE_CS 30
   #define SD_CS    27
#elif defined(ARDUINO_MAX32620FTHR) || defined(ARDUINO_MAX32630FTHR)
   #define TFT_DC   P5_4
   #define TFT_CS   P5_3
   #define STMPE_CS P3_3
   #define SD_CS    P3_2
#else
    // Anything else, defaults!
   #define STMPE_CS 6
   #define TFT_CS   9
   #define TFT_DC   10
   #define SD_CS    5
#endif


#define TFT_RST -1

// Use hardware SPI and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750

// Color definitions ------------------------
#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN   0xBFF7
#define LTCYAN    0xC7FF
#define LTRED     0xFD34
#define LTMAGENTA 0xFD5F
#define LTYELLOW  0xFFF8
#define LTORANGE  0xFE73
#define LTPINK    0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY    0xE71C

#define BLUE      0x001F
#define TEAL      0x0438
#define GREEN     0x07E0
#define CYAN      0x07FF
#define RED       0xF800
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define ORANGE    0xFC00
#define PINK      0xF81F
#define PURPLE    0x8010
#define GREY      0xC618
#define WHITE     0xFFFF
#define BLACK     0x0000

#define DKBLUE    0x000D
#define DKTEAL    0x020C
#define DKGREEN   0x03E0
#define DKCYAN    0x03EF
#define DKRED     0x6000
#define DKMAGENTA 0x8008
#define DKYELLOW  0x8400
#define DKORANGE  0x8200
#define DKPINK    0x9009
#define DKPURPLE  0x4010
#define DKGREY    0x4A49

// graph stuff
double a1, b1, c1, d1, r1, r2;

// this is the only external variable used by the graph
// it's a flat to draw the coordinate system only on the first pass
boolean display1 = true;

double ox , oy ; // old x, old y
double nx, ny; // new x, new y

// code for data collection
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;

// interval at which data will be stored into the arrays
const long interval = 1000;

// data array
int CO2Data[24]   = {0}; // initialize with zeros
int TVOCData[24]  = {0}; // initialize with zeros
int tempData[26]  = {0}; // initialize with zeros
int humidData[26] = {0}; // initialize with zeros

// keep track of index
int currentIndex = 0;

// SGP30 stuff -----------------------------------------------------------------------------
#include "Adafruit_SGP30.h" //  Library for the the sensor

Adafruit_SGP30 sgp; //  Create an Object from the sensor library

// DHT stuff ------------------------
#include "DHT.h"
//here we use pin 12 of ESP32 to read data
#define DHTPIN A0
//our sensor is DHT11 type
#define DHTTYPE DHT11
//create an instance of DHT sensor
DHT dht(DHTPIN, DHTTYPE);


// Wi-Fi stuff
// Import required libraries for wifi communication
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// initialize the fan speed
int fan_speed = 0;

String fanSpeed(){
  return String(fan_speed);
}

// global variables
// LED pins
int ledR = 21;
int ledG = 17;
int ledB = 16;

// buzzer pin
#define buzzerPin 19

// touchscreen position variables
int y;
int x;

// touchscreen button boundaries
int XMIN_HOME;
int XMAX_HOME;
int YMIN_HOME;
int YMAX_HOME;

int XMIN_SET;
int XMAX_SET;
int YMIN_SET;
int YMAX_SET;

int XMIN_eCO2;
int XMAX_eCO2;
int YMIN_eCO2;
int YMAX_eCO2;

int XMIN_TVOC;
int XMAX_TVOC;
int YMIN_TVOC;
int YMAX_TVOC;

int XMIN_TEMP;
int XMAX_TEMP;
int YMIN_TEMP;
int YMAX_TEMP;

int XMIN_HUMID;
int XMAX_HUMID;
int YMIN_HUMID;
int YMAX_HUMID;

int XMIN_B1;
int XMAX_B1;
int YMIN_B1;
int YMAX_B1;

int XMIN_B2;
int XMAX_B2;
int YMIN_B2;
int YMAX_B2;

int XMIN_B3;
int XMAX_B3;
int YMIN_B3;
int YMAX_B3;

int XMIN_B4;
int XMAX_B4;
int YMIN_B4;
int YMAX_B4;

// sensor boundaries 
int CO2minLower = 0;
int CO2minUpper = 1000;

int CO2midLower = 1000;
int CO2midUpper = 2000;

int CO2maxLower = 2000;
int CO2maxUpper = 5000;

int TVOCminLower = 0;
int TVOCminUpper = 100;

int TVOCmidLower = 100;
int TVOCmidUpper = 220;

int TVOCmaxLower = 220;
int TVOCmaxUpper = 2200;

// screen orientation
int rotation = 0; // 0 & 2 set screen vertically, 1 & 3 set screen horizontally

#endif
