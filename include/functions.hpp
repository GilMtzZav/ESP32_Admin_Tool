#include <Arduino.h>


void log(String data)
{
    Serial.println(data);
}

String platform()
{
    #ifndef ARDUINO_ESP32_DEV
    return "ESP32";
    #endif
    return "esp32";
}

IPAddress CharToIP(const char* str)
{
    sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
    return IPAddress(ip[0], ip[1], ip[2], ip[3]);
}



// Retorna IPAddress en formato "n.n.n.n" de IP a String
String ipStr(const IPAddress &ip)
{
    String sFn = "";
    for(byte bFn = 0; bFn < 3; bFn++)
    {
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8 * 3)) & 0xFF);
    return sFn;
}

// De hex a string
String hexStr(const unsigned long &h, const  byte &l = 8)
{
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}

// Crea un ID unico desde la dirección MAC

String idUnique()
{
    char id_unique[15];
    uint64_t chip_id = ESP.getEfuseMac();
    uint16_t chip = (uint16_t) (chip_id >> 32);
    snprintf(id_unique, 15, "%04X", chip);
    return id_unique;
}

String deviceID()
{
    return String(platform()) + hexStr(ESP.getEfuseMac()) + String(idUnique());
}

void settingsPines()
{
    pinMode(WIFILED, OUTPUT);
    pinMode(MQTTLED, OUTPUT);
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);

    digitalWrite(WIFILED, LOW);
    digitalWrite(MQTTLED, LOW);
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
}