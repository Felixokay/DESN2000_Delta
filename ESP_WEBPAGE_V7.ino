#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>
#include <ESP8266mDNS.h>

//#include "index2.h"
#include "test.h"
#include "homefinal.h"
#include "unit2final.h"
#include "unit1_final.h"

 // #include "home_page.h"
 // #include "insolation.h"
 // #inlude "FAQ.h"
 // #include "help.h"
 // #include "syllabus.h"
 // #include " 



#define LED 2 // 
const char* ssid = "BigGreenHouse";
const char* password = "delta1996";
int a; 
ESP8266WebServer server(80);
SoftwareSerial esps(12, 14); // RX | TX
int data;
String power;
const int led=2;
String mystring = String(data);
int check_bit = 0;

void handleRoot(){
  check_bit = 0;
  esps.write(check_bit);
  
server.send(200,"text/html",MAIN_page );
}

void handlePOWER() {
  digitalWrite(LED,!digitalRead(LED));
  Serial.print("a is");
  Serial.println(a);
  String POWERvalue = String(a);
 //Toggle LED on data request ajax
 server.send(200, "text/plane", POWERvalue); //Send ADC value only to client ajax request
}

void handleUnit1() {
check_bit = 0;
Serial.print(check_bit);
esps.write(check_bit);
Serial.print("Test Sending check bit: " );
Serial.println(check_bit);



server.send(200,"text/html",UNIT_1);

}


void handleUnit2() {
check_bit = 1;
Serial.print(check_bit);

esps.write(check_bit);
Serial.print("Test Sending check bit: " );
Serial.println(check_bit);



//server.send(200,"text/html",UNIT_2);

}


void handleLED(){
digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
server.sendHeader("Location","/");
server.send(303);
void handleNotFound();
}




void setup() {

  
//New line to serial moniter 
 esps.begin(9600);
Serial.begin(9600);
Serial.println("");
WiFi.mode(WIFI_AP);

pinMode(LED_BUILTIN, OUTPUT);

WiFi.softAP(ssid,password);  // Start AP
IPAddress myIP = WiFi.softAPIP();
Serial.print("Access Point \"");
Serial.print(ssid);
Serial.println("\" started");

//If connectrion sucsessful show ip in serial moniter
Serial.print("Server ip:");
Serial.println(myIP); 



//
    //server stuff
server.on("/",HTTP_GET, handleRoot);
server.on("/LED",HTTP_POST,handleLED);
server.on("/readPOWER",handlePOWER);
server.on("/unit1",handleUnit1);
server.on("/unit2",handleUnit2);
server.begin(); 
Serial.println("Http server started");





}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  
  esps.write(check_bit);
 
  Serial.println("UNO connected !!!!");
  data = esps.read();
  Serial.println("Incoming Data...");
  Serial.print("Data =   ");
  Serial.println(data);

  
  Serial.print("Sending check bit:  ");
  Serial.println(check_bit);

  if (check_bit == 0){
    Serial.println("CHECKBIT 0");
    a = 17370.0 * data/255;
  }


  else if (check_bit == 1){
    Serial.println("CHECKBIT 1");
    a = 1000 * data/255;
  }

delay(500);

}
