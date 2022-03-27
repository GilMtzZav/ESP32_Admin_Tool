#define RELAY1          27                       
#define RELAY2          26
#define WIFILED         2
#define MQTTLED         13                      
#define HW              "ADMINESP32 v1 00000000"   //Versión de hardware

// ZONA WIFI
bool wifi_status_static_ip;      //Estatus de la IP estática
char wifi_ssid[30];              //Nombre de la red wifi
char wifi_pass[30];              //Contreseña de red wifi
char wifi_ip_static[15];         //IP estático
char wifi_gateway[15];           //Gateway
char wifi_subnet[15];            //Subred
char wifi_primary_dns[15];       //DNS primario
char wifi_secondary_dns[15];     //DNS secundario

// ZONA CONFIGURACIONES GENERALES
char device_id[30];
int device_boot_count;

// ZONA AP
bool ap_status;                  //Estatus del modo AP  
char ap_name[31];                //SSID AP
char ap_pass[63];                //Password AP
char ap_canal;                   //Canal AP
char ap_hidden;                  //Es visible el AP (0 -> Visible, 1 -> Oculto)
char ap_connect;                 //Número de conexiones en el AP


// ZONA OTROS
uint8_t ip[4];                  //Variable función convertir stirng a IP
