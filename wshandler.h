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

#ifndef WSHANDLER_H_
#define WSHANDLER_H_

/* 
  Packet Commands
    E1 - Get Elements

    G1 - Get Config
    G2 - Get Config Status
    
    T0 - Disable Testing
    T1 - Static Testing

    S1 - Set Network Config
    S2 - Set Device Config

    X1 - Get RSSI
    X2 - Get E131 Status
    Xh - Get Heap
    X6 - Reboot
*/

EFUpdate efupdate;
extern int counter_from_din;
extern int counter_to_din;
extern int counter_to_wifi;
extern int counter_from_wifi;
extern int counter_to_synth;

void procX(uint8_t *data, AsyncWebSocketClient *client) {
    switch (data[1]) {
        case '1':
            client->text("X1" + (String)WiFi.RSSI());
            break;
        case '2': {
            uint32_t seqErrors = 0;
            for (int i = 0; i < ((uniLast + 1) - config.universe); i++)
                seqErrors =+ seqError[i];
            client->text("X2" + (String)counter_from_wifi + ":" +
                    (String)counter_to_wifi + ":" +
                    (String)counter_from_din + ":" +
                    (String)counter_to_din + ":" +
                    (String)counter_to_synth + ":" );
            break;
        }
        case 'h':
            client->text("Xh" + (String)ESP.getFreeHeap());
            break;
        case 'U':
            client->text("XU" + (String)millis());
            break;
        case '6':  // Init 6 baby, reboot!
            reboot = true;
    }
}

void procE(uint8_t *data, AsyncWebSocketClient *client) {
    switch (data[1]) {
        case '1':
            // Create buffer and root object
            DynamicJsonBuffer jsonBuffer;
            JsonObject &json = jsonBuffer.createObject();

            // Pixel Types
            JsonObject &p_type = json.createNestedObject("p_type");
            p_type["WS2811 800kHz"] = static_cast<uint8_t>(PixelType::WS2811);
            p_type["GE Color Effects"] = static_cast<uint8_t>(PixelType::GECE);

            // Pixel Colors
            JsonObject &p_color = json.createNestedObject("p_color");
            p_color["RGB"] = static_cast<uint8_t>(PixelColor::RGB);
            p_color["GRB"] = static_cast<uint8_t>(PixelColor::GRB);
            p_color["BRG"] = static_cast<uint8_t>(PixelColor::BRG);
            p_color["RBG"] = static_cast<uint8_t>(PixelColor::RBG);
            p_color["GBR"] = static_cast<uint8_t>(PixelColor::GBR);
            p_color["BGR"] = static_cast<uint8_t>(PixelColor::BGR);


            String response;
            json.printTo(response);
            client->text("E1" + response);
            break;
    }
}

void procG(uint8_t *data, AsyncWebSocketClient *client) {
    switch (data[1]) {
        case '1': {
            String response;
            serializeConfig(response, false, true);
            client->text("G1" + response);
            break;
        }
        case '2':
            // Create buffer and root object
            DynamicJsonBuffer jsonBuffer;
            JsonObject &json = jsonBuffer.createObject();

            json["ssid"] = (String)WiFi.SSID();
            json["hostname"] = (String)WiFi.hostname();
            json["ip"] = WiFi.localIP().toString();
            json["mac"] = WiFi.macAddress();
            json["version"] = (String)VERSION;
            json["flashchipid"] = String(ESP.getFlashChipId(), HEX);
            json["usedflashsize"] = (String)ESP.getFlashChipSize();
            json["realflashsize"] = (String)ESP.getFlashChipRealSize();
            json["freeheap"] = (String)ESP.getFreeHeap();

            String response;
            json.printTo(response);
            client->text("G2" + response);
            break;
    }
}

void procS(uint8_t *data, AsyncWebSocketClient *client) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(reinterpret_cast<char*>(data + 2));
    if (!json.success()) {
        DBG_PORT.println(F("*** procS(): Parse Error ***"));
        DBG_PORT.println(reinterpret_cast<char*>(data));
        return;
    }

    switch (data[1]) {
        case '1':   // Set Network Config
            dsNetworkConfig(json);
            saveConfig();
            client->text("S1");
            break;
        case '2':   // Set Device Config
            dsDeviceConfig(json);
            saveConfig();
            client->text("S2");
            break;
    }
}


void procT(uint8_t *data, AsyncWebSocketClient *client) {
}

void handle_fw_upload(AsyncWebServerRequest *request, String filename,
        size_t index, uint8_t *data, size_t len, bool final) {
    if (!index) {
        WiFiUDP::stopAll();
        DBG_PORT.print(F("* Upload Started: "));
        DBG_PORT.println(filename.c_str());
        efupdate.begin();
    }

    if (!efupdate.process(data, len)) {
        DBG_PORT.print(F("*** UPDATE ERROR: "));
        DBG_PORT.println(String(efupdate.getError()));
    }

    if (efupdate.hasError())
        request->send(200, "text/plain", "Update Error: " +
                String(efupdate.getError()));

    if (final) {
        DBG_PORT.println(F("* Upload Finished."));
        efupdate.end();
        SPIFFS.begin();
        saveConfig();
        reboot = true;
    }
}

void wsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
        AwsEventType type, void * arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_DATA: {
            AwsFrameInfo *info = static_cast<AwsFrameInfo*>(arg);
            if (info->opcode == WS_TEXT) {
                switch (data[0]) {
                    case 'X':
                        procX(data, client);
                        break;
                    case 'E':
                        procE(data, client);
                        break;
                    case 'G':
                        procG(data, client);
                        break;
                    case 'S':
                        procS(data, client);
                        break;
                    case 'T':
                        procT(data, client);
                        break;
                }
            } else {
                DBG_PORT.println(F("-- binary message --"));
            }
            break;
        }
        case WS_EVT_CONNECT:
            DBG_PORT.print(F("* WS Connect - "));
            DBG_PORT.println(client->id());
            break;
        case WS_EVT_DISCONNECT:
            DBG_PORT.print(F("* WS Disconnect - "));
            DBG_PORT.println(client->id());
            break;
        case WS_EVT_ERROR:
            DBG_PORT.println(F("** WS ERROR **"));
            break;
    }
}

#endif /* ESPIXELSTICK_H_ */

