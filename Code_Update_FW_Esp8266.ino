#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

const char* host = "esp8266-webupdate";
const char* update_path = "/";
const char* update_username = "admin";
const char* update_password = "admin";
const char* ssid = "WIFI_update";
const char* password = "123456789";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void setup(void){
  //Khởi tạo serial với baud 115200
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.softAP(ssid, password);
  
  // In địa chỉ IP
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  MDNS.begin(host);
  // Tạo server
  httpUpdater.setup(&httpServer, update_path, update_username, update_password);
  httpServer.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local%s in your browser and login with username '%s' and password '%s'\n", host, update_path, update_username, update_password);
}

void loop(void){
  httpServer.handleClient();
  MDNS.update();
  digitalWrite(LED_BUILTIN, LOW);
  delay(500); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500); 
}
