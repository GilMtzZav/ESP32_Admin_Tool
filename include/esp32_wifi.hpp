#pragma once
#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h>


const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;
IPAddress apIP(192, 168, 4, 1);
IPAddress netMask(255, 255, 255, 0);
int wifi_mode = WIFI_STA;

unsigned long interval_wifi = 30000;
unsigned long previous_millis_wifi = 0;

// Hostname for ESPmDNS. Should work at least on windows. Try http://adminesp32.local
const char* esp_hostname = device_id;

void startAP()
{
    log("Info: Iniciando modo AP");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.softAPConfig(apIP, apIP, netMask);
    WiFi.setHostname(deviceID().c_str());
    WiFi.softAP(ap_name, ap_pass, ap_canal, ap_hidden, ap_connect);
    log("Info: Wifi AP " + deviceID() + " - IP " + ipStr(WiFi.softAPIP()));
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", apIP);
    wifi_mode = WIFI_AP;
}

void startClient()
{
    if (wifi_status_static_ip) 
    {
        if(!WiFi.config(CharToIP(wifi_ip_static), CharToIP(wifi_gateway), CharToIP(wifi_subnet), CharToIP(wifi_primary_dns), CharToIP(wifi_secondary_dns)))
        {
            log("Error: Falló al conectar el modo estación");
        }
    }

    WiFi.hostname(deviceID());
    WiFi.begin(wifi_ssid, wifi_pass);
    log("Info: Conectando wifi " + String(wifi_ssid));
    delay(50);
    byte b = 0;
    while (WiFi.status() != WL_CONNECTED && b < 60)
    {
        b++;
        log("Warning: Intentando conexión wifi...");
        delay(500);
        // Para parpadear led wifi cuando este conectandose al wifi no bloqueante
        // Parpadeo simple del led cada 100 ms
        blinkSingle(100, WIFILED);
    }

    if ((WiFi.status() == WL_CONNECTED))
    {
        //Wifi station conectado
        log("Info: wifi conectado (" + String(WiFi.RSSI()) + ") IP " + ipStr(WiFi.localIP()));
        // Parpadeo random del led
        blinkRandomSingle(10, 100, WIFILED);
        delay(100);
    }
    else
    {
        //Wifi station NO conectado
        log(F("Error: wifi no conectado"));
        // Parpadeo random del led
        blinkRandomSingle(10, 100, WIFILED);
        delay(100);
    } 
    
}


// WiFi.mode(WIFI_STA)	station mode: the ESP32 connects to an access point
// WiFi.mode(WIFI_AP)	access point mode: stations can connect to the ESP32
// WiFi.mode(WIFI_STA_AP)	access point and a station connected to another access point

void wifi_setup()
{
    WiFi.disconnect();
    // 1.- Si esta activo el modo AP
    if(ap_status)
    {
        startAP();
        log("Info: Wifi modo AP");
    }
    // 2.- Caso contrario en modo cliente (estacionario)
    else
    {
        WiFi.mode(WIFI_STA);
        wifi_mode = WIFI_STA;
        startClient();
        log("Info: Wifi en modo estación");
    }

    // Iniciar hostname broadcast en modo AP o STA
    if(wifi_mode == WIFI_STA || wifi_mode == WIFI_AP)
    {
        if(MDNS.begin(esp_hostname))
        {
            MDNS.addService("http", "tcp", 80);
        }
    }
}

// Loop modo cliente o modo estación
void wifiLoop()
{
    unsigned long current_millis = millis();

    if (WiFi.status() != WL_CONNECTED && (current_millis - previous_millis_wifi >= interval_wifi))
    {
        blinkSingle(100, WIFILED);
        WiFi.disconnect();
        WiFi.reconnect();
        previous_millis_wifi = millis();
    }
    else
    {
        blinkSingleAsy(10, 500, WIFILED);
    }
}

// Modo AP
void wifiAPLoop()
{
    blinkRandomSingle(50, 100, WIFILED);
    dnsServer.processNextRequest();
}