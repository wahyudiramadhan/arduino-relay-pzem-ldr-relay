#include "CTBot.h"
#define LDR D3 
#define RELAY D4
#define RELAY2 D7
//================================
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(D5,D6 );
//================================
int LDRValue;     // result of reading the analog pin
CTBot myBot;
TBMessage msg;
String ssid = "free";       //ssid wifi
String pass = "1sampe8ya";  //password wifi
String token = "1105302957:AAHbm8kOEDr9cTxscieHeB5gOsebowusR0w"; //token telegram
const int id = 898383350; //id chat
void setup() {
  Serial.begin(9600);
  Serial.println("Starting TelegramBot...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
    pinMode(RELAY, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(LDR, INPUT);
}
void loop() {
  //===============
  LDRValue = digitalRead(LDR);
 // Serial.println(LDRValue);      
  delay(100);                    
  //===============
  TBMessage msg;
  // LDRValue = digitalRead(LDR);
   //===============
  float voltage = pzem.voltage();
  if(voltage != NAN){
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
  }else{
    Serial.println("Error reading voltage");
  }
  float current = pzem.current();
  if(current != NAN){
    Serial.print("Current: "); Serial.print(current); Serial.println("A");
  }else{
    Serial.println("Error reading current");
  }
  float power = pzem.power();
  if(current != NAN){
    Serial.print("Power: "); Serial.print(power); Serial.println("W");
  }else{
    Serial.println("Error reading power");
  }
  float energy = pzem.energy();
  if(current != NAN){
    Serial.print("Energy: "); Serial.print(energy,3); Serial.println("kWh");
  }else{
  Serial.println("Error reading energy");
  }
  float frequency = pzem.frequency();
  if(current != NAN){
    Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
  }else{
    Serial.println("Error reading frequency");
  }
  float pf = pzem.pf();
  if(current != NAN){
    Serial.print("PF: "); Serial.println(pf);
  }else{
    Serial.println("Error reading power factor");
  }
  Serial.println();
  delay(2000);
//======================================================
if(myBot.getNewMessage(msg)){
    if (msg.text.equalsIgnoreCase("ON")){          //perintah ON untuk menghidupkan lampu
        digitalWrite(RELAY, LOW);
        myBot.sendMessage(msg.sender.id, "LAMPU DI NYALAKAN");    
    }else if (msg.text.equalsIgnoreCase("Off")) {   //perintah OFF di gunakan untuk mematikan lampu
        digitalWrite(RELAY, HIGH);                      
        myBot.sendMessage(msg.sender.id, "LAMPU DI MATIKAN");
//======================================================================================================================
     }else if (msg.text.equalsIgnoreCase("ac on")) {   //perintah OFF di gunakan untuk mematikan lampu
        digitalWrite(RELAY2, LOW);                      
        myBot.sendMessage(msg.sender.id, "AC DI HIDUPKAN");
     }else if (msg.text.equalsIgnoreCase("ac Off")) {   //perintah OFF di gunakan untuk mematikan lampu
        digitalWrite(RELAY2, HIGH);                      
        myBot.sendMessage(msg.sender.id, "AC DI MATIKAN");
//======================================================================================================================
    }else if (msg.text.equalsIgnoreCase("menu")) {  //menu untuk mengakses menu kontrol
        myBot.sendMessage(msg.sender.id, "~Menu~ \n [kontrol lampu] \n -On \n -off \n cek lampu \n [kontrol AC] \n -ac on \n -ac off \n cek ac \n -About"); 

    }else if (msg.text.equalsIgnoreCase("About")) {   //about untuk mengakses data pemilik
        myBot.sendMessage(msg.sender.id, "SELAMAT DATANG DI RUANG CONTROL AYU");
    }else if (msg.text.equalsIgnoreCase("cek lampu")) {  
       if(LDRValue==0){
          myBot.sendMessage(msg.sender.id, "LAMPU NYALA");
       }else{
         myBot.sendMessage(msg.sender.id, "LAMPU MATI");
      }
      }else if (msg.text.equalsIgnoreCase("cek ac")) {  
       if(power > 0){
          myBot.sendMessage(msg.sender.id, "ac NYALA");
       }else{
         myBot.sendMessage(msg.sender.id, "ac MATI");
      } 
}else{
       myBot.sendMessage(msg.sender.id, "perintah error \n silahkan buka menu");
    }
}
delay(500); 
}
