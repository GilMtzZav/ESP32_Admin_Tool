void settingsResetWifi()
{
    
        //GENERAL
        strlcpy(device_id, "adminesp32", sizeof(device_id));
        device_boot_count = 0;

        //CLIENTE
        wifi_status_static_ip = false;
        strlcpy(wifi_ssid, "Rufo", sizeof(wifi_ssid));
        strlcpy(wifi_pass, "Hunter_189", sizeof(wifi_pass));
        strlcpy(wifi_ip_static, "192.168.0.150", sizeof(wifi_ip_static));
        strlcpy(wifi_gateway, "wifi_gw", sizeof(wifi_gateway));
        strlcpy(wifi_subnet, "wifi_subnet", sizeof(wifi_subnet));
        strlcpy(wifi_primary_dns, "wifi_primaryDNS", sizeof(wifi_primary_dns));
        strlcpy(wifi_secondary_dns, "wifi_secondaryDNS", sizeof(wifi_secondary_dns));

        //AP
        ap_status = true;
        strlcpy(ap_name, deviceID().c_str(), sizeof(ap_name));
        strlcpy(ap_pass, "adminesp32", sizeof(ap_pass));
        ap_canal = 9;
        ap_hidden = false;
        ap_connect = 4;

        log("Info: Lectura configuración wifi correcta");        

    
}