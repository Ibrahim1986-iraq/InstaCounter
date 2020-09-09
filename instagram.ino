

// A Simple program to show Instagram subscribers
// Credit to Roberto Delgado who wrote most of the code. I have just changed a few lines of it. 


// Libraries included

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "JsonStreamingParser.h"
#include <ArduinoJson.h>
#include "InstagramStats.h"
#include "theSwedishMaker.h"


const uint16_t WAIT_TIME = 20000; //Time between fecthing data.


// Define the typ of hardware and the pins used. 

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   12
#define DATA_PIN  15
#define CS_PIN    13

// Hardware SPI connection
//MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary output pins
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
String userName = "abrahim.1986"; // Your Instagram Username


WiFiClientSecure client; //For ESP8266 boards
InstagramStats instaStats(client);



// =======================================================================
// Configuration of router settings
// =======================================================================

const char* ssid     = "RaNGeR-UP";      // SSID of local network
const char* password = "GoWKratoS1";                // Password on network

void setup() 
{
  P.begin();
  P.setFont(fontSubs);
  
  // Connecting to wifi
  Serial.begin(115200);
  Serial.print("Connecting WiFi ");
  WiFi.begin(ssid, password);
  P.print(" WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("."); delay(500);
  }
  Serial.println("");
  Serial.print("Connected: "); Serial.println(WiFi.localIP());
  
  client.setInsecure();
}


void loop(void)
{

  Serial.println("Getting data ...");
  P.print("fetching");
  int cnt = 0;
  int yt1;
  long insta;
    while(1) {
    if(!cnt--) {
     cnt = 50;
      InstagramUserStats response = instaStats.getUserStats(userName);
      insta = response.followedByCount;    
    }
    
    // FORMATO

       String instaFollowers = num_format(insta);
    
    // PRINT

    delay(3500);
    P.print("&" + instaFollowers); 
    delay(5000);
    }}


String num_format(long num){
     String num_s;
     long num_original = num;
     if (num>99999 && num<=999999){
        num = num / 1000;
        long fraction = num_original%1000;
        String num_fraction = String(fraction);
        String decimal = num_fraction.substring(0,1);
        num_s = String(num) + "." + decimal + "K";          
    }
    else if(num>999999){
        num = num / 1000000;
        long fraction = num_original%1000000;
        String num_fraction = String(fraction);
        String decimal = num_fraction.substring(0,1);
        if (num_original<100000000){
          num_s = " " + String(num) + "." + decimal + "M";      
        }
        else{
        num_s = String(num) + "." + decimal + "M";
        }
    }
    else{
        int num_l = String(num).length();
        char num_f[15];
        int blankDigits = 6 - num_l;
        for(int i = 0; i < blankDigits; i++){
          num_f[i] = ' '; 
        }
        num_f[blankDigits] = '\0';
        num_s = num_f + String(num);
    }
    return num_s;
}    
