
bool settingsReadWifi()
{
    StaticJsonDocument<500> jsonConfig;
    File file = SPIFFS.open("/SettingWifi.json", "r");
    if(deserializeJson(jsonConfig, file))
    {
        // Si fallla la lectura inicia valores por defecto
        settingsResetWifi();
        log("Error: Falló  la lectura de la configuración wifi, tomando valores por defecto");
        return false;
    }
    else    
    {
        //GENERAL
        strlcpy(device_id, jsonConfig["deviceID"], sizeof(device_id));
        device_boot_count = jsonConfig["deviceBootCount"];

        //CLIENTE
        wifi_status_static_ip = jsonConfig["wifi_status_ip"];
        strlcpy(wifi_ssid, jsonConfig["wifi_ssid"], sizeof(wifi_ssid));
        strlcpy(wifi_pass, jsonConfig["wifi_pass"], sizeof(wifi_pass));
        strlcpy(wifi_ip_static, jsonConfig["wifi_ip_static"], sizeof(wifi_ip_static));
        strlcpy(wifi_gateway, jsonConfig["wifi_gw"], sizeof(wifi_gateway));
        strlcpy(wifi_subnet, jsonConfig["wifi_subnet"], sizeof(wifi_subnet));
        strlcpy(wifi_primary_dns, jsonConfig["wifi_primaryDNS"], sizeof(wifi_primary_dns));
        strlcpy(wifi_secondary_dns, jsonConfig["wifi_secondaryDNS"], sizeof(wifi_secondary_dns));

        //AP
        ap_status = jsonConfig["ap_status"];
        strlcpy(ap_name, jsonConfig["ap_name"], sizeof(ap_name));
        strlcpy(ap_pass, jsonConfig["ap_pass"], sizeof(ap_pass));
        ap_canal = jsonConfig["ap_canal"];
        ap_hidden = jsonConfig["ap_hidden"];
        ap_connect = jsonConfig["ap_connect"];

        file.close();
        log("Info: Lectura configuración wifi correcta");        

        return true;
    }
}