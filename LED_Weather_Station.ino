#include <DHT.h>                      //Temperature and humidity support library
#include <DHT_U.h>
#include <Adafruit_Sensor.h>          //Needed by NeoPixels
#include <Adafruit_NeoPixel.h>        //NeoPixels support library

#define DHTPIN 2                      //Set digital pin for sensor
#define DHTTYPE DHT22                 //Sensor type
#define NEOPIN 6                      //Set NeoPixel pin 
#define NUMPIXELS 8                   //Set number of LEDs

DHT_Unified dht(DHTPIN, DHTTYPE);     //Initialises Sensor object

uint32_t delayMS;                     //Temperature sensor read delay

volatile int temp;
volatile int humi;
volatile int ledpos;

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIN, NEO_RGB + NEO_KHZ800);  //Initialises NeoPixel strip

void setup() {
  pixels.begin();
  pixels.setBrightness(25);

  dht.begin();

//Get sensor values
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void loop() {

  delay(delayMS);

  //Transfer sensor values to disposable integer variables and truncate values
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  temp = event.temperature;
  dht.humidity().getEvent(&event);
  humi = event.relative_humidity;

//Gets Neopixel column hight according to humidity value
  if(humi > 10 && humi < 20)
  {
    ledpos = 1;
  }
  else if(humi > 20 && humi < 30)
  {
    ledpos = 2;
  }
  else if(humi > 40 && humi < 50)
  {
    ledpos = 3;
  }
  else if(humi > 50 && humi < 60)
  {
    ledpos = 4;
  }
  else if(humi > 60 && humi < 70)
  {
    ledpos = 5;
  }
  else if(humi > 70 && humi < 80)
  {
    ledpos = 6;
  }
  else if(humi > 80 && humi < 90)
  {
    ledpos = 7;
  }
  else if(humi > 90 && humi < 100)
  {
    ledpos = 8;
  }
  
  pixels.clear();

//Sets Neopixel column hight and colour. Also creates breathing effect.

  if (temp > 0 && temp < 5)
  {
    pixels.fill(pixels.Color(0x00,0x00,0xFF),0,ledpos);  //Blue
    for (int i=10; i<100; i++) { pixels.setBrightness(i); pixels.show(); delay(10); }
    for (int i=100; i>10; i--) { pixels.setBrightness(i); pixels.show(); delay(10); }
  }
  else if(temp > 5 && temp < 10)
  {
    pixels.fill(pixels.Color(0xFF,0x38,0xFF),0,ledpos);  //Cyan
    for (int i=10; i<100; i++) { pixels.setBrightness(i); pixels.show(); delay(10); }
    for (int i=100; i>10; i--) { pixels.setBrightness(i); pixels.show(); delay(10); }
  }
  else if(temp > 10 && temp < 20)
  {
    pixels.fill(pixels.Color(0xFF,0xF7,0x03),0,ledpos);  //Yellow
    for (int i=10; i<100; i++) { pixels.setBrightness(i); pixels.show(); delay(10); }
    for (int i=100; i>10; i--) { pixels.setBrightness(i); pixels.show(); delay(10); }
  }
  else if(temp > 20 && temp < 30)
  {
    pixels.fill(pixels.Color(0x99,0xFF,0x00),0,ledpos);  //Orange
    for (int i=10; i<100; i++) { pixels.setBrightness(i); pixels.show(); delay(10); }
    for (int i=100; i>10; i--) { pixels.setBrightness(i); pixels.show(); delay(10); }
  }
  else if(temp > 30 && temp < 40)
  {
    pixels.fill(pixels.Color(0x00,0xFF,0x00),0,ledpos);  //Red
    for (int i=10; i<100; i++) { pixels.setBrightness(i); pixels.show(); delay(10); }
    for (int i=100; i>10; i--) { pixels.setBrightness(i); pixels.show(); delay(10); }
  }
}
