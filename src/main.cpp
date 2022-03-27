#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "settings.hpp"
#include "functions.hpp"
#include "ledBlink.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"


void setup() 
{
  Serial.begin(115200);
  setCpuFrequencyMhz(240);
  log("Info: Iniciando setup");

  settingsPines();

  if(!SPIFFS.begin(true))
  {
    log(F("Error: Falló la inicialización del SPIFFS"));
    while(true);
  }

  settingsReadWifi();
  WiFi.disconnect(true);
  delay(1000);
  wifi_setup();

}

void loop() 
{
  yield();

  if (wifi_mode ==  WIFI_STA)
  {
    wifiLoop();
  }
  if (wifi_mode == WIFI_AP)
  {
    wifiAPLoop();
  }
  

} 