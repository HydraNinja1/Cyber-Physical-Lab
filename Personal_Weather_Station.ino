#include "arduino_secrets.h"

#include "thingProperties.h"
#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;
 
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
 
  // Defined in thingProperties.h
  initProperties();
 
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  //Get Cloud Info/errors , 0 (only errors) up to 4
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
 
  //Wait to get cloud connection to init the carrier
  while (ArduinoCloud.connected() != 1) {
    ArduinoCloud.update();
    delay(500);
  }
  delay(500);
  CARRIER_CASE = false;
  carrier.begin();
  carrier.display.setRotation(0);
}
 
void loop() {
  ArduinoCloud.update();
  carrier.leds.setPixelColor(0,  0 , 20 , 20);
  carrier.leds.setPixelColor(1,  0 ,  0 , 20);
  carrier.leds.setPixelColor(2, 20 , 20 , 20);
  carrier.leds.setPixelColor(3,  0 , 20 , 0 );
  carrier.leds.setPixelColor(4, 20 ,  0 , 0 );
  carrier.leds.show();
  carrier.Buttons.update();
 
  while(!carrier.Light.colorAvailable()) {
    delay(5);
  }
  int none;
  carrier.Light.readColor(none, none, none, light);
  
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
  pressure = carrier.Pressure.readPressure();
 
  if (carrier.Buttons.onTouchDown(TOUCH0)) {
    carrier.display.fillScreen(ST77XX_BLACK);
    carrier.display.setTextColor(ST77XX_CYAN);
    carrier.display.setTextSize(2);
    
    carrier.display.setCursor(30, 60);
    carrier.display.print("Temp: ");
    carrier.display.print(temperature);
    carrier.display.print(" C");
  }
 
  if (carrier.Buttons.onTouchDown(TOUCH1)) {
    carrier.display.fillScreen(ST77XX_BLACK);
    carrier.display.setTextColor(ST77XX_BLUE);
    carrier.display.setTextSize(2);
    
    carrier.display.setCursor(30, 60);
    carrier.display.print("Humi: ");
    carrier.display.print(humidity);
    carrier.display.print(" %");
  }
 
  if (carrier.Buttons.onTouchDown(TOUCH2)) {
    carrier.display.fillScreen(ST77XX_BLACK);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);
    
    carrier.display.setCursor(30, 60);
    carrier.display.print("Light: ");
    carrier.display.print(light);
  }
 
  if (carrier.Buttons.onTouchDown(TOUCH3)) {
    carrier.display.fillScreen(ST77XX_BLACK);
    carrier.display.setTextColor(ST77XX_GREEN);
    carrier.display.setTextSize(2);
    
    carrier.display.setCursor(30, 60);
    carrier.display.print("Pressure: ");
    carrier.display.print(pressure);
    
  }
  if (carrier.Buttons.onTouchDown(TOUCH4)) {
    carrier.display.fillScreen(ST77XX_BLACK);
    carrier.display.setTextColor(ST77XX_GREEN);
    carrier.display.setTextSize(2);
    
    carrier.display.setCursor(40, 60);
    carrier.display.print(weather_report);
    
  }
 
  if (humidity >= 60 && temperature >= 15) {
    weather_report = "It is very humid outside";
    
  }else if (temperature >= 15 && light >= 700) {
    weather_report = "Warm and sunny outside";
    
  }else if (temperature <= 16 && light >= 700) {
    weather_report = "A little cold, but sunny outside";
  }
  
  else{
   weather_report = "Weather is normal"; 
  }
 
}