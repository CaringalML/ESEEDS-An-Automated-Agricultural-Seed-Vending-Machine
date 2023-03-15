#include <SoftwareSerial.h>
#include<EEPROM.h>

SoftwareSerial sms(12,13);

String numbers = "";

volatile int pulsesx =0;
volatile int pulsesx2 =0;
volatile int pulsesx3 =0;
volatile int pulsesx4 =0;
volatile int pulsesx5 =0;
volatile int pulsesx6 =0;
volatile int pulsesx7 =0;
volatile int pulsesx8 =0;


String textMessage;

void setup() {
  // Automatically turn on the shield
 
  Serial.begin(19200);
  sms.begin(19200);

   sms.print("AT+CMGF=1\r");
  delay(100);

  sms.print("AT+CNMI=1,2,0,0,0\r");
  delay(100);

  pulsesx=EEPROM.read(1);
  pulsesx2=EEPROM.read(2);
  pulsesx3=EEPROM.read(3);
  pulsesx4=EEPROM.read(4);
   pulsesx5=EEPROM.read(5);
   pulsesx6=EEPROM.read(6);
   pulsesx7=EEPROM.read(7);
   pulsesx8=EEPROM.read(8);
   


   
  Serial.println(pulsesx);
  Serial.println(pulsesx2);
   Serial.println(pulsesx3);
  Serial.println(pulsesx4);
  Serial.println(pulsesx5);
  Serial.println(pulsesx6);
  Serial.println(pulsesx7);
  Serial.println(pulsesx8);
  
}

void loop() {




  if (Serial.available() > 0) {
    textMessage = Serial.readString();
    Serial.print(textMessage);
    delay(10);








  }
 
    if (textMessage.indexOf("A") >= 0) {
    
 numbers.concat(textMessage.charAt(2));
  numbers.concat(textMessage.charAt(3));
  numbers.concat(textMessage.charAt(4));
  numbers.concat(textMessage.charAt(5));
  numbers.concat(textMessage.charAt(6));
  numbers.concat(textMessage.charAt(7));
  

  Serial.println(numbers);
    
   
   pulsesx = numbers.toInt();
  EEPROM.write(1,pulsesx);

  delay(2000);
  numbers = "";
   textMessage = "";

    }
    else if (textMessage.indexOf("B") >= 0) {
    
 numbers.concat(textMessage.charAt(2));
  numbers.concat(textMessage.charAt(3));
  numbers.concat(textMessage.charAt(4));
  numbers.concat(textMessage.charAt(5));
  numbers.concat(textMessage.charAt(6));
  numbers.concat(textMessage.charAt(7));
  

  Serial.println(numbers);
    
   
   pulsesx2 = numbers.toInt();
  EEPROM.write(2,pulsesx2);

  delay(2000);
  numbers = "";
   textMessage = "";

    }
    else if (textMessage.indexOf("C") >= 0) {
    
 numbers.concat(textMessage.charAt(2));
  numbers.concat(textMessage.charAt(3));
  numbers.concat(textMessage.charAt(4));
  numbers.concat(textMessage.charAt(5));
  numbers.concat(textMessage.charAt(6));
  numbers.concat(textMessage.charAt(7));
  

  Serial.println(numbers);
    
   
   pulsesx3 = numbers.toInt();
  EEPROM.write(3,pulsesx3);

  delay(2000);
  numbers = "";
   textMessage = "";

    }
    else if (textMessage.indexOf("D") >= 0) {
    
 numbers.concat(textMessage.charAt(2));
  numbers.concat(textMessage.charAt(3));
  numbers.concat(textMessage.charAt(4));
  numbers.concat(textMessage.charAt(5));
  numbers.concat(textMessage.charAt(6));
  numbers.concat(textMessage.charAt(7));
  

  Serial.println(numbers);
    
   
   pulsesx4 = numbers.toInt();
  EEPROM.write(4,pulsesx4);

  delay(2000);
  numbers = "";
   textMessage = "";

    }

    else if (textMessage.indexOf("E") >= 0) {
    
 numbers.concat(textMessage.charAt(2));
  numbers.concat(textMessage.charAt(3));
  numbers.concat(textMessage.charAt(4));
  numbers.concat(textMessage.charAt(5));
  numbers.concat(textMessage.charAt(6));
  numbers.concat(textMessage.charAt(7));
  

  Serial.println(numbers);
    
   
   pulsesx5 = numbers.toInt();
  EEPROM.write(5,pulsesx5);

  delay(2000);
  numbers = "";
   textMessage = "";

    }

else if (textMessage.indexOf("F") >= 0) {
    
 numbers.concat(textMessage.charAt(2));
  numbers.concat(textMessage.charAt(3));
  numbers.concat(textMessage.charAt(4));
  numbers.concat(textMessage.charAt(5));
  numbers.concat(textMessage.charAt(6));
  numbers.concat(textMessage.charAt(7));
  

  Serial.println(numbers);
    
   
   pulsesx6 = numbers.toInt();
  EEPROM.write(6,pulsesx6);

  delay(2000);
  numbers = "";
   textMessage = "";

    }



    
    else if (textMessage.indexOf("G") >= 0) {
    
 numbers.concat(textMessage.charAt(2));
  numbers.concat(textMessage.charAt(3));
  numbers.concat(textMessage.charAt(4));
  numbers.concat(textMessage.charAt(5));
  numbers.concat(textMessage.charAt(6));
  numbers.concat(textMessage.charAt(7));
  

  Serial.println(numbers);
    
   
   pulsesx7 = numbers.toInt();
  EEPROM.write(7,pulsesx7);

  delay(2000);
  numbers = "";
   textMessage = "";

    }
    
    else if (textMessage.indexOf("H") >= 0) {
    
 numbers.concat(textMessage.charAt(2));
  numbers.concat(textMessage.charAt(3));
  numbers.concat(textMessage.charAt(4));
  numbers.concat(textMessage.charAt(5));
  numbers.concat(textMessage.charAt(6));
  numbers.concat(textMessage.charAt(7));
  

  Serial.println(numbers);
    
   
   pulsesx8 = numbers.toInt();
  EEPROM.write(8,pulsesx8);

  delay(2000);
  numbers = "";
   textMessage = "";

    }
 
}
