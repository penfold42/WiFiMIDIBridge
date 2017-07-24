/*
* ESPixelStick.h
*
* Project: ESPixelStick - An ESP8266 and E1.31 based pixel driver
* Copyright (c) 2016 Shelby Merrick
* http://www.forkineye.com
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*/

#ifndef ESPIXELSTICK_H_
#define ESPIXELSTICK_H_


/* Name and version */
const char VERSION[] = "0.1 (20170718)";

#define FROM_INVALID 0
#define FROM_WIFI 1
#define FROM_DIN 2


#define HTTP_PORT       80      /* Default web server port */
#define MQTT_PORT       1883    /* Default MQTT port */
#define DATA_PIN        2       /* Pixel output - GPIO2 */
#define EEPROM_BASE     0       /* EEPROM configuration base address */
#define UNIVERSE_LIMIT  512     /* Universe boundary - 512 Channels */
#define PIXEL_LIMIT     1360    /* Total pixel limit - 40.85ms for 8 universes */
#define CONNECT_TIMEOUT 15000   /* 15 seconds */
#define REBOOT_DELAY    100     /* Delay for rebooting once reboot flag is set */
#define DBG_PORT        Serial  /* Serial port for console logging */


/* Configuration file params */
const char CONFIG_FILE[] = "/config.json";
#define CONFIG_MAX_SIZE 2048    /* Sanity limit for config file */


typedef struct {
    uint8_t r,g,b;              //hold requested color
    uint16_t step;               //step in testing routine
    uint32_t last;              //last update
} testing_t;

/* Pixel Types */
enum class PixelType : uint8_t {
    WS2811,
    GECE
};

/* Color Order */
enum class PixelColor : uint8_t {
    RGB,
    GRB,
    BRG,
    RBG,
    GBR,
    BGR
};

/* Configuration structure */
typedef struct {
    /* Device */
    String      id;             /* Device ID */
//    DevMode     devmode;        /* Device Mode - used for reporting mode, can't be set */
//    TestMode    testmode;       /* Testing mode */

    /* Network */
    String      ssid;
    String      passphrase;
    String      hostname;
    uint8_t     ip[4];
    uint8_t     netmask[4];
    uint8_t     gateway[4];
    bool        dhcp;           /* Use DHCP? */
    bool        ap_fallback;    /* Fallback to AP if fail to associate? */

    /* MQTT */
    bool        mqtt;           /* Use MQTT? */
    String      mqtt_ip;
    uint16_t    mqtt_port;
    String      mqtt_user;
    String      mqtt_password;
    String      mqtt_topic;

    /* E131 */
    uint16_t    universe;       /* Universe to listen for */
    uint16_t    channel_start;  /* Channel to start listening at - 1 based */
    uint16_t    channel_count;  /* Number of channels */
    bool        multicast;      /* Enable multicast listener */

    /* Pixels */
    PixelType   pixel_type;     /* Pixel type */
    PixelColor  pixel_color;    /* Pixel color order */
    bool        gamma;          /* Use gamma map? */

} config_t;

/* Globals */
//E131Async       e131(10);       /* E131Async with X buffers */
//testing_t       testing;
config_t        config;
uint32_t        *seqError;      /* Sequence error tracking for each universe */
uint16_t        uniLast = 1;    /* Last Universe to listen for */
bool            reboot = false; /* Reboot flag */
AsyncWebServer  web(HTTP_PORT); /* Web Server */
AsyncWebSocket  ws("/ws");      /* Web Socket Plugin */


/* Forward Declarations */
void serializeConfig(String &jsonString, bool pretty = false, bool creds = false);
void dsNetworkConfig(JsonObject &json);
void dsDeviceConfig(JsonObject &json);
void saveConfig();

/* Plain text friendly MAC */
String getMacAddress() {
    uint8_t mac[6];
    char macStr[18] = {0};
    WiFi.macAddress(mac);
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return  String(macStr);
}

#endif /* ESPIXELSTICK_H_ */
