#include <String.h>
#include <SPI.h>
#include <Ethernet.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h> //including stepper motor library
#include <SoftwareSerial.h>
#include<EEPROM.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial SIM900(10, 12);




// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "eseeds.000webhostapp.com";
String PATH_ONE   = "/conone.php";
String PATH_TWO   = "/contwo.php";
String PATH_THREE   = "/conthree.php";
String PATH_FOUR   = "/confour.php";
String PATH_FIVE   = "/confive.php";
String PATH_SIX   = "/consix.php";





//Define "i"
int i;

//defining pins section
//Stepper Connect 1
int stepIN1Pin1 = 22;
int stepIN2Pin1 = 24;
int stepIN3Pin1= 26;
int stepIN4Pin1 = 28;

//Stepper Connect 2
int stepIN1Pin2 = 23; 
int stepIN2Pin2 = 25;
int stepIN3Pin2 = 27;
int stepIN4Pin2 = 29;

//Stepper Connect 3
int stepIN1Pin3 = 30;
int stepIN2Pin3 = 32;
int stepIN3Pin3 = 34;
int stepIN4Pin3 = 36;

//Stepper Connect 4
int stepIN1Pin4 = 31;
int stepIN2Pin4 = 33;
int stepIN3Pin4 = 35;
int stepIN4Pin4 = 37;

//Stepper Connect 5
int stepIN1Pin5 = 38;
int stepIN2Pin5 = 40;
int stepIN3Pin5 = 42;
int stepIN4Pin5 = 44;

//Stepper Connect 6
int stepIN1Pin6 = 39;
int stepIN2Pin6 = 41;
int stepIN3Pin6 = 43;
int stepIN4Pin6 = 45;

const byte intPin =2;

//////////////////////////////////////////////////////////
volatile byte count =0;
const int coinhopper =3;
///////////////////////////////////////////////////////////
int motorPin = 4;
int sukli = 5;
///////////////////////////////////////////////////////////

//Relay for motors to turn on para makasolo ng batak!
int andarOne = 46;
int andarTwo = 47;
int andarThree = 48;
int andarFour = 49;
int andarFive = 50;
int andarSix = 51;

// ilaw dispence
int blue = 6;
int red = 7;

//Sa sales ng isang araw declaration
volatile int sales1 =0;
volatile int sales2 =0;
volatile int sales3 =0;
volatile int sales4 =0;
volatile int sales5 =0;
volatile int sales6 =0;

volatile int total = 0;


int stepsPerRevolution = 2048; // amount of steps per revolution

String textMessage;
String numbers = "";

const int buttonOne = A1;
const int buttonTwo = A2;
const int buttonThree = A3;
const int buttonFour = A4;
const int buttonFive = A5;
const int buttonSix = A6;

const int buwanReset = A9;
const int tingnan = A10;

int coinSlotSignal; 
volatile int coinCount = 0;

volatile int requiredCoins = 10;
volatile int requiredCoinsTwo = 20;
volatile int requiredCoinsThree = 30;
volatile int requiredCoinsFour = 40;
volatile int requiredCoinsFive = 50;
volatile int requiredCoinsSix = 60;

int una = 15;
int pangalawa = 15;
int patatlo = 15;
int paapat = 10;
int palima =10;
int paanim = 10;

boolean coinInserted = false;

//define each stepper
// 1
Stepper myStepper1(stepsPerRevolution, stepIN1Pin1, stepIN3Pin1, stepIN2Pin1, stepIN4Pin1);
//2
Stepper myStepper2(stepsPerRevolution, stepIN1Pin2, stepIN3Pin2, stepIN2Pin2, stepIN4Pin2);
//3
Stepper myStepper3(stepsPerRevolution, stepIN1Pin3, stepIN3Pin3, stepIN2Pin3, stepIN4Pin3);
//4
Stepper myStepper4(stepsPerRevolution, stepIN1Pin4, stepIN3Pin4, stepIN2Pin4, stepIN4Pin4);
//5
Stepper myStepper5(stepsPerRevolution, stepIN1Pin5, stepIN3Pin5, stepIN2Pin5, stepIN4Pin5);
//6
Stepper myStepper6(stepsPerRevolution, stepIN1Pin6, stepIN3Pin6, stepIN2Pin6, stepIN4Pin6);


void setup() {
  Serial.begin(19200);
   SIM900.begin(19200);
  lcd.begin(16,2);
 lcd.init();
  lcd.backlight();
  delay(20000);
   SIM900.print("AT+CMGF=1\r"); 
  delay(500);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(500);
  
//   //Reset relay
//   pinMode(gsmRelay,OUTPUT);
//  digitalWrite(gsmRelay,HIGH);
//  delay(1000);
//  digitalWrite(gsmRelay,LOW);
//  delay(1000);
//  digitalWrite(gsmRelay,HIGH);
  
  pinMode(intPin , INPUT_PULLUP);
  attachInterrupt (0,countPulses, CHANGE);
  
  attachInterrupt(digitalPinToInterrupt(coinhopper),coinPulse,FALLING);
  pinMode(coinhopper,INPUT_PULLUP);
  //Relay for coin hopper
  pinMode(motorPin,OUTPUT);
  digitalWrite(motorPin,HIGH);
  
  pinMode(sukli,INPUT_PULLUP);
  pinMode(buttonOne,INPUT_PULLUP);
   pinMode(buttonTwo,INPUT_PULLUP);
    pinMode(buttonThree,INPUT_PULLUP);
     pinMode(buttonFour,INPUT_PULLUP);
     pinMode(buttonFive,INPUT_PULLUP);
     pinMode(buttonSix,INPUT_PULLUP);
     
     pinMode(buwanReset,INPUT_PULLUP);
     pinMode(tingnan,INPUT_PULLUP);  
 
//Relay setup for motors panga
  pinMode(andarOne,OUTPUT);
  digitalWrite(andarOne,HIGH);
  
  pinMode(andarTwo,OUTPUT);
  digitalWrite(andarTwo,HIGH);
  
  pinMode(andarThree,OUTPUT);
  digitalWrite(andarThree,HIGH);
  
  pinMode(andarFour,OUTPUT);
  digitalWrite(andarFour,HIGH);
  
  pinMode(andarFive,OUTPUT);
  digitalWrite(andarFive,HIGH);
  
  pinMode(andarSix,OUTPUT);
  digitalWrite(andarSix,HIGH);

  pinMode(blue,OUTPUT);
  digitalWrite(blue,HIGH);

  pinMode(red,OUTPUT);
  digitalWrite(red,HIGH);
  
  // Assign Stepper Speed
  myStepper1.setSpeed(15);
  myStepper2.setSpeed(15);
  myStepper3.setSpeed(15);
  myStepper4.setSpeed(15);
  myStepper5.setSpeed(15);
  myStepper6.setSpeed(15);

  requiredCoins=EEPROM.read(1);
 requiredCoinsTwo=EEPROM.read(2);
  requiredCoinsThree=EEPROM.read(3);
  requiredCoinsFour=EEPROM.read(4);
  requiredCoinsFive=EEPROM.read(5);
  requiredCoinsSix=EEPROM.read(6);
  
  coinCount = EEPROM.read(7);

  
  //una = EEPROM.read(6);
  //pangalawa = EEPROM.read(7);
  //patatlo = EEPROM.read(8);
  //paapat = EEPROM.read(9);
  
  Serial.println(requiredCoins);
  Serial.println(requiredCoinsTwo);
  Serial.println(requiredCoinsThree);
  Serial.println(requiredCoinsFour);
  Serial.println(requiredCoinsFive);
  Serial.println(requiredCoinsSix);

  delay(1000);
  
}

void countPulses(){
  int val = digitalRead(intPin);
 Serial.println(val);

  if (val==LOW){
 
  coinCount++;
  EEPROM.write(7,coinCount);
  Serial.println(coinCount);
  
 }

}


void loop() {
  LaGay();

   if (SIM900.available() > 0) {
    textMessage = SIM900.readString();
    Serial.print(textMessage);
    delay(10);
 }

  if (textMessage.indexOf("P1") >= 0) {
    

numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));

  Serial.println(numbers);
    
   
   requiredCoins = numbers.toInt();
  EEPROM.write(1,requiredCoins);

  delay(2000);
  numbers = "";
   textMessage = "";

    }
    ///////////////////////////////////////////////////////////////////
    
     else if (textMessage.indexOf("P2") >= 0) {
    
numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
  

  Serial.println(numbers);  
   
   requiredCoinsTwo = numbers.toInt();
  EEPROM.write(2,requiredCoinsTwo);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
    //////////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P3") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
Serial.println(numbers);
   
   requiredCoinsThree = numbers.toInt();
  EEPROM.write(3,requiredCoinsThree);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
    /////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P4") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
    Serial.println(numbers);
   
   requiredCoinsFour = numbers.toInt();
  EEPROM.write(4,requiredCoinsFour);

  delay(2000);
  numbers = "";
  textMessage = "";

    }

     /////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P5") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
    Serial.println(numbers);
   
   requiredCoinsFive = numbers.toInt();
  EEPROM.write(5,requiredCoinsFive);

  delay(2000);
  numbers = "";
  textMessage = "";

    }

     /////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P6") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
    Serial.println(numbers);
   
   requiredCoinsSix = numbers.toInt();
  EEPROM.write(6,requiredCoinsSix);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
    
    if(digitalRead(sukli)==LOW) {
    
    digitalWrite(motorPin,LOW);
    //digitalWrite(gsmRelay,LOW);
    Serial.println("nag susukli");
  }

  if(digitalRead(buwanReset)==LOW) {
    
    total = 0;
    
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Sales Cleared");
   lcd.setCursor(0,1);
   lcd.print("Php: ");
   lcd.print(total);                       
   delay(2000);
   
   
  }

  if(digitalRead(tingnan)==LOW) {
    
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Sales of the Day");
   lcd.setCursor(0,1);
   lcd.print("Php: ");
   lcd.print(total);                       
   delay(2000);
   araw();
   delay(1000);
   SalesDay();
   
  }

      
   if (digitalRead(buttonOne) == LOW)       // eto yung sa button na code
      {
         if(una <= 0)
         {
            
            Serial.println("Wala ng Stock!");
            una = 15;
         }
         else
         {
                  if(coinCount >= requiredCoins  )
                      {
                        Serial.println(" Delivering 1 ");
                          
                          PinDot();
                
                          digitalWrite(andarOne,LOW);
                          delay(2000);
                          
                          una = una - 1;
                          coinCount = coinCount - requiredCoins;

                          EEPROM.write(7,coinCount);                         
                             Serial.println(coinCount);
                            myStepper1.step(stepsPerRevolution); //run motor
                           
                           SendMessage();
                           digitalWrite(andarOne,HIGH);
                           
                           digitalWrite(blue,HIGH);
                            digitalWrite(red,LOW);
                            salamat();
                            
                           //kinita sa isang araw
                           sales1 = sales1 + requiredCoins;
                           Serial.print("Sales1 is: ");
                           Serial.println(sales1);
                           
                           total = sales1 + sales2 + sales3 + sales4 + sales5 + sales6;
                           Serial.print("Total is: ");
                           Serial.println(total);
                           Serial.println("  ");

                            
                           
                           lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("RemainingCredits");
                           lcd.setCursor(0,1);
                           lcd.print("Php: P");
                           lcd.print(coinCount);
                          
                          delay(2500);
                          lcd.clear();
                          araw();
                          delay(800);
                          NotifOne();
                          delay(800);
                          SalesDay();
                          digitalWrite(red,HIGH);

                           aa();
          
                        }
                   else if(coinCount <= requiredCoins)
                        {
                          lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("Required Amount!");
                           lcd.setCursor(0,1);
                           lcd.print("Php: ");
                           lcd.print(requiredCoins);
                           Serial.println("Required Amount!");
                          delay(1000);
                          lcd.clear();
                        }
           }
        }
        else if (digitalRead(buttonTwo) == LOW)       // eto yung sa button na code
         {
            if(pangalawa <= 0)
             {
                
                Serial.println("Wala ng Stock!");
                pangalawa = 15;
              }
             else
              {
                     if(coinCount >= requiredCoinsTwo  )
                        {
                           Serial.println(" Delivering 2 ");
                          PinDot();
                          
                          digitalWrite(andarTwo,LOW);
                          delay(2000);
                          
                          pangalawa = pangalawa - 1;
                          coinCount = coinCount - requiredCoinsTwo;

                          EEPROM.write(7,coinCount);
                          Serial.println(coinCount);
                            myStepper2.step(stepsPerRevolution); //run motor
                           
                           SendDos();
                           digitalWrite(andarTwo,HIGH);
                           
                           digitalWrite(blue,HIGH);
                            digitalWrite(red,LOW);
                           salamat();
                           
                           //kinita sa isang araw
                           sales2 = sales2 + requiredCoinsTwo;
                           Serial.print("Sales2 is: ");
                           Serial.println(sales2);
                           
                           total = sales1 + sales2 + sales3 + sales4 + sales5 + sales6;
                           Serial.print("Total is: ");
                           Serial.println(total);
                           Serial.println("  ");
                           
                           
                          lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("RemainingCredits");
                           lcd.setCursor(0,1);
                           lcd.print("Php: P");
                           lcd.print(coinCount);
                           
             
                          delay(2500);
                          lcd.clear();
                          araw();
                          
                           delay(800);
                          NotifTwo();
                          delay(800);
                          SalesDay();
                          digitalWrite(red,HIGH);

                          bb();
      
                        }
                     else if(coinCount <=requiredCoinsTwo)
                         {
                           lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("Required Amount!");
                           lcd.setCursor(0,1);
                           lcd.print("Php: ");
                           lcd.print(requiredCoinsTwo);
                           Serial.println("Required Amount!");
                          delay(1000);
                          lcd.clear();
                           
                         }
               }
        }
        else if (digitalRead(buttonThree) == LOW)       // eto yung sa button na code
          {
              if(patatlo <= 0)
                {
                  
                  Serial.println("Wala ng Stock!");
                  patatlo = 15;
                }
              else
                {
                      if(coinCount >= requiredCoinsThree )
                        {
                          
                          PinDot();
                          
                          digitalWrite(andarThree,LOW);
                          delay(2000);
                          
                          patatlo = patatlo - 1;
                          coinCount = coinCount - requiredCoinsThree;
                          EEPROM.write(7,coinCount);
                          Serial.println(coinCount);
                           myStepper3.step(stepsPerRevolution); //run motor
                           
                           SendTres();
                           digitalWrite(andarThree,HIGH);

                           digitalWrite(blue,HIGH);
                            digitalWrite(red,LOW);
                           salamat();
                           
                           //kinita sa isang araw
                           sales3 = sales3 + requiredCoinsThree;
                           Serial.print("Sales3 is: ");
                           Serial.println(sales3);
                           
                           total = sales1 + sales2 + sales3 + sales4 + sales5 + sales6;
                           Serial.print("Total is: ");
                           Serial.println(total);
                           Serial.println("  ");
                          
                           
                           lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("RemainingCredits");
                           lcd.setCursor(0,1);
                           lcd.print("Php: P");
                           lcd.print(coinCount);

                          delay(2500);
                          lcd.clear();
                          araw();
                          
                           delay(800);
                          NotifThree();
                          delay(800);
                          SalesDay();
                          digitalWrite(red,HIGH);

                          cc();
          
                 }
               else if(coinCount <= requiredCoinsThree)
                  {
                           lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("Required Amount!");
                           lcd.setCursor(0,1);
                           lcd.print("Php: ");
                           lcd.print(requiredCoinsThree);
                           Serial.println("Required Amount!");
                          delay(1000);
                          lcd.clear();
                       
                  }
              }
        }
        else if (digitalRead(buttonFour) == LOW)       // eto yung sa button na code
          {
              if(paapat <= 0)
                { 
                  
                  Serial.println("Wala ng Stock!");
                  paapat = 10;
                 }
               else
                 {
                       if(coinCount >= requiredCoinsFour  )
                          {
                            
                             PinDot();
                             
                             digitalWrite(andarFour,LOW);
                             delay(2000);
                             
                              paapat = paapat - 1;
                             coinCount = coinCount - requiredCoinsFour;
                             EEPROM.write(7,coinCount);
                             Serial.println(coinCount);
                             
                             myStepper4.step(stepsPerRevolution); //run motor
                           
                            SendKwatro();
                            digitalWrite(andarFour,HIGH);

                            digitalWrite(blue,HIGH);
                            digitalWrite(red,LOW);
                            salamat();
                            
                            //kinita sa isang araw
                            sales4 = sales4 + requiredCoinsFour;
                           Serial.print("Sales4 is: ");
                           Serial.println(sales4);
                           
                           total = sales1 + sales2 + sales3 + sales4 + sales5 + sales6;
                           Serial.print("Total is: ");
                           Serial.println(total);
                           Serial.println("  ");
                           
                           
                              lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("RemainingCredits");
                           lcd.setCursor(0,1);
                           lcd.print("Php: P");
                           lcd.print(coinCount);
                             
                             delay(2500);
                             lcd.clear();
                             araw();
                       
                              delay(800);
                          NotifFour();
                          delay(800);
                          SalesDay();
                          digitalWrite(red,HIGH);

                          dd();
        
                           }
                else if(coinCount < requiredCoinsFour)
                   {
                          lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("Required Amount!");
                           lcd.setCursor(0,1);
                           lcd.print("Php: ");
                           lcd.print(requiredCoinsFour);
                           Serial.println("Required Amount!");
                          delay(1000);
                          lcd.clear();
                       
                   }
             }
        }       

         else if (digitalRead(buttonFive) == LOW)       // eto yung sa button na code
          {
              if(palima <= 0)
                { 
                  
                  Serial.println("Wala ng Stock!");
                  palima = 10;
                 }
               else
                 {
                       if(coinCount >= requiredCoinsFive  )
                          {
                            
                             PinDot();
                             
                             digitalWrite(andarFive,LOW);
                             
                             delay(2000);
                             
                              palima = palima - 1;
                             coinCount = coinCount - requiredCoinsFive;
                             EEPROM.write(7,coinCount);
                             Serial.println(coinCount);
                             
                             myStepper5.step(stepsPerRevolution); //run motor
                           
                            SendSingko();
                            digitalWrite(andarFive,HIGH);
                            
                            digitalWrite(blue,HIGH);
                            digitalWrite(red,LOW);
                            salamat();
                            
                            //kinita sa isang araw
                             sales5 = sales5 + requiredCoinsFive;
                           Serial.print("Sales5 is: ");
                           Serial.println(sales5);
                           
                           total = sales1 + sales2 + sales3 + sales4 + sales5 + sales6;
                           Serial.print("Total is: ");
                           Serial.println(total);
                           Serial.println("  ");
                           
                           
                              lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("RemainingCredits");
                           lcd.setCursor(0,1);
                           lcd.print("Php: P");
                           lcd.print(coinCount);
                             
                             delay(2500);
                             lcd.clear();
                             araw();
                             
                               delay(800);
                               NotifFive();
                               delay(800);
                               SalesDay();
                               digitalWrite(red,HIGH);

                               ee();
        
                           }
                else if(coinCount < requiredCoinsFive)
                   {
                          lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("Required Amount!");
                           lcd.setCursor(0,1);
                           lcd.print("Php: ");
                           lcd.print(requiredCoinsFive);
                           Serial.println("Required Amount!");
                          delay(1000);
                          lcd.clear();
                       
                   }
             }
        }

        else if (digitalRead(buttonSix) == LOW)       // eto yung sa button na code
          {
              if(paanim <= 0)
                { 
                  
                  Serial.println("Wala ng Stock!");
                  paanim = 10;
                 }
               else
                 {
                       if(coinCount >= requiredCoinsSix )
                          {
                            
                             PinDot();
                             
                              digitalWrite(andarSix,LOW);
                              
                             delay(2000);
                             
                              paanim = paanim - 1;
                             coinCount = coinCount - requiredCoinsSix;
                             EEPROM.write(7,coinCount);
                             Serial.println(coinCount);
                             
                             myStepper6.step(stepsPerRevolution); //run motor
                           
                            SendSais();
                            digitalWrite(andarSix,HIGH);

                            digitalWrite(blue,HIGH);
                            digitalWrite(red,LOW);
                            salamat();
                            
                            //kinita sa isang araw
                            sales6 = sales6 + requiredCoinsSix;
                           Serial.print("Sales6 is: ");
                           Serial.println(sales6);
                           
                           total = sales1 + sales2 + sales3 + sales4 + sales5 + sales6;
                           Serial.print("Total is: ");
                           Serial.println(total);
                           Serial.println("  ");
                         
                           
                              lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("RemainingCredits");
                           lcd.setCursor(0,1);
                           lcd.print("Php: P");
                           lcd.print(coinCount);
                             
                             delay(2500);
                             lcd.clear();
                             araw();
                              
                              delay(800);
                              NotifSix();
                              delay(800);
                              SalesDay();
                              digitalWrite(red,HIGH);

                              ff();
        
                           }
                else if(coinCount < requiredCoinsSix)
                   {
                          lcd.clear();
                           lcd.setCursor(0,0);
                           lcd.print("Required Amount!");
                           lcd.setCursor(0,1);
                           lcd.print("Php: ");
                           lcd.print(requiredCoinsSix);
                           Serial.println("Required Amount!");
                          delay(1000);
                          lcd.clear();
                       
                   }
             }
        }
        else if(count == coinCount)
          {
           //Serial.print("Completed");
           digitalWrite(motorPin,HIGH);
                    
           coinCount = coinCount - count;
           EEPROM.write(7,coinCount);
           Serial.println(coinCount);
           count =0;
           Serial.println(count);
           
           }
}
void LaGay() {
if (coinCount==0)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Seeds Vendo");
    lcd.setCursor(0,1);
    lcd.print("-(INSERT COINS)-");
    delay(1000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Seeds Prices");
     lcd.setCursor(0,1);
     lcd.print("A:");
     lcd.print(requiredCoins);
     lcd.print(", B:");
     lcd.print(requiredCoinsTwo);
     lcd.print(", C:");
     lcd.print(requiredCoinsThree);
     delay(1200);
     
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Seeds Prices");
     lcd.setCursor(0,1);
     lcd.print("D:");
     lcd.print(requiredCoinsFour);
     lcd.print(", E:");
     lcd.print(requiredCoinsFive);
     lcd.print(", F:");
     lcd.print(requiredCoinsSix);
     delay(1200);

     //////////////////////////////////////////////////////////////////////////////
     if (SIM900.available() > 0) {
    textMessage = SIM900.readString();
    Serial.print(textMessage);
    delay(10);
 }

  if (textMessage.indexOf("P1") >= 0) {
    

 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));

  Serial.println(numbers);
    
   
   requiredCoins = numbers.toInt();
  EEPROM.write(1,requiredCoins);

  delay(2000);
  numbers = "";
   textMessage = "";

    }
    ///////////////////////////////////////////////////////////////////
    
     else if (textMessage.indexOf("P2") >= 0) {
    
numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
  
  

  Serial.println(numbers);  
   
   requiredCoinsTwo = numbers.toInt();
  EEPROM.write(2,requiredCoinsTwo);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
    //////////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P3") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
Serial.println(numbers);
   
   requiredCoinsThree = numbers.toInt();
  EEPROM.write(3,requiredCoinsThree);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
    /////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P4") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
    Serial.println(numbers);
   
   requiredCoinsFour = numbers.toInt();
  EEPROM.write(4,requiredCoinsFour);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
     /////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P5") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
    Serial.println(numbers);
   
   requiredCoinsFive = numbers.toInt();
  EEPROM.write(5,requiredCoinsFive);

  delay(2000);
  numbers = "";
  textMessage = "";

    }

     /////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P6") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
    Serial.println(numbers);
   
   requiredCoinsSix = numbers.toInt();
  EEPROM.write(6,requiredCoinsSix);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Seeds Vendo");
     lcd.setCursor(0,1);
     lcd.print("Php: P");
     lcd.print(coinCount);
     delay(50);
     

     /////////////////////////////////////////////////////
     if (SIM900.available() > 0) {
    textMessage = SIM900.readString();
    Serial.print(textMessage);
    delay(10);
 }

  if (textMessage.indexOf("P1") >= 0) {
    

 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));

  Serial.println(numbers);
    
   
   requiredCoins = numbers.toInt();
  EEPROM.write(1,requiredCoins);

  delay(2000);
  numbers = "";
   textMessage = "";

    }
    ///////////////////////////////////////////////////////////////////
    
     else if (textMessage.indexOf("P2") >= 0) {
    
numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
  

  Serial.println(numbers);  
   
   requiredCoinsTwo = numbers.toInt();
  EEPROM.write(2,requiredCoinsTwo);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
    //////////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P3") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
Serial.println(numbers);
   
   requiredCoinsThree = numbers.toInt();
  EEPROM.write(3,requiredCoinsThree);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
    /////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P4") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
    Serial.println(numbers);
   
   requiredCoinsFour = numbers.toInt();
  EEPROM.write(4,requiredCoinsFour);

  delay(2000);
  numbers = "";
  textMessage = "";

    }

    /////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P5") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
    Serial.println(numbers);
   
   requiredCoinsFive = numbers.toInt();
  EEPROM.write(5,requiredCoinsFive);

  delay(2000);
  numbers = "";
  textMessage = "";

    }

     /////////////////////////////////////////////////////////////
    else if (textMessage.indexOf("P6") >= 0) {
    
 numbers.concat(textMessage.charAt(54));
  numbers.concat(textMessage.charAt(55));
  numbers.concat(textMessage.charAt(56));
  numbers.concat(textMessage.charAt(57));
  numbers.concat(textMessage.charAt(58));
 
  
    Serial.println(numbers);
   
   requiredCoinsSix = numbers.toInt();
  EEPROM.write(6,requiredCoinsSix);

  delay(2000);
  numbers = "";
  textMessage = "";

    }
  }
 
}

void  PinDot() {
  // Print "Delivering..."
  digitalWrite(blue,LOW); 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Delivering... ");
 delay(1000);
}

void  salamat() {
  // Print "salamat po" 
//  digitalWrite(blue,HIGH);
//  digitalWrite(red,LOW);
//  delay(4000);
//  digitalWrite(red,HIGH);

  lcd.clear(); // Clears the display
  lcd.setCursor(0, 1);
  lcd.print("Kuhanin sa Baba"); // Prints on the LCD
  delay(1500);
  
 lcd.clear(); // Clears the display
  lcd.setCursor(0, 0);
  lcd.print("Thank You po!^-^"); // Prints on the LCD
  delay(1250);
}


void SendMessage(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09127476965\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container One is: "+ String(una));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void SendDos(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09127476965\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Two is: "+ String(pangalawa));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void SendTres(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09127476965\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Three is: "+ String(patatlo));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void SendKwatro(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09127476965\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Four is: "+ String(paapat));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void SendSingko(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09127476965\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Five is: "+ String(palima));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void SendSais(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09127476965\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Six is: "+ String(paanim));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void araw(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09127476965\"\r");
delay(500);
String dataMessage ("The Total Sales of the day is: "+ String(total));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//for client number////////////////////////

void NotifOne(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09289973440\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container One is: "+ String(una));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void NotifTwo(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09289973440\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Two is: "+ String(pangalawa));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void NotifThree(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09289973440\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Three is: "+ String(patatlo));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void NotifFour(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09289973440\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Four is: "+ String(paapat));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void NotifFive(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09289973440\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Five is: "+ String(palima));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void NotifSix(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09289973440\"\r");
delay(500);
String dataMessage ("The Remaining Item for Container Six is: "+ String(paanim));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

void SalesDay(){

SIM900.print("AT+CMGF=1\r"); // Select SMS Message Format (see SIM900 AT Commands Reference)
delay(500);
SIM900.println("AT+CMGS=\"09289973440\"\r");
delay(500);
String dataMessage ("The Total Sales of the day is: "+ String(total));
SIM900.print(dataMessage);
delay(500);
SIM900.println((char)26);
delay(500);
SIM900.println();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void coinPulse() 
{
  
if(digitalRead(coinhopper)==LOW) {
  count++;
  Serial.println(count);   
 }
 if(count == coinCount)
          {
           //Serial.print("Completed");
           digitalWrite(motorPin,HIGH);
           //delay(500); 
               
           coinCount = coinCount - count;
           EEPROM.write(7,coinCount);
           Serial.println(coinCount);
           count =0;
           Serial.println(count);
           
           }
  }




  void aa(){
    
    String queryString = String("?tiraone=") + String(una) + String("&bentaone=") + String(sales1)+ String("&lahat=") + String(total);
     
  // initialize the Ethernet shield using DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to obtaining an IP address using DHCP");
    while(true);
  }

  // connect to web server on port 80:
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " " + PATH_ONE + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    
    Serial.println(HTTP_METHOD + " " + PATH_ONE + queryString + " HTTP/1.1");
    Serial.println("Host: " + String(HOST_NAME));
    delay(500);
     Serial.println("Nag Send na");
  
    
    client.println("Connection: close");
    client.println(); // end HTTP header

    while(client.connected()) {
      if(client.available()){
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {// if not connected:
    Serial.println("connection failed");
  }
  }


  void bb(){
    
       String queryString = String("?tiratwo=") + String(pangalawa) + String("&bentatwo=") + String(sales2)+ String("&lahat=") + String(total);
     
  // initialize the Ethernet shield using DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to obtaining an IP address using DHCP");
    while(true);
  }

  // connect to web server on port 80:
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " " + PATH_TWO + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    delay(500);
     Serial.println("Nag Send na");
  
    
    client.println("Connection: close");
    client.println(); // end HTTP header

    while(client.connected()) {
      if(client.available()){
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {// if not connected:
    Serial.println("connection failed");
  }
  }


  void cc(){
    
   String queryString = String("?tirathree=") + String(patatlo) + String("&bentathree=") + String(sales3)+ String("&lahat=") + String(total);
     
  // initialize the Ethernet shield using DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to obtaining an IP address using DHCP");
    while(true);
  }

  // connect to web server on port 80:
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " " + PATH_THREE + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    delay(500);
     Serial.println("Nag Send na");
  
    
    client.println("Connection: close");
    client.println(); // end HTTP header

    while(client.connected()) {
      if(client.available()){
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {// if not connected:
    Serial.println("connection failed");
  }
  }


  void dd(){
    
    String queryString = String("?tirafour=") + String(paapat) + String("&bentafour=") + String(sales4)+ String("&lahat=") + String(total);
     
  // initialize the Ethernet shield using DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to obtaining an IP address using DHCP");
    while(true);
  }

  // connect to web server on port 80:
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " " + PATH_FOUR + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    delay(500);
     Serial.println("Nag Send na");
  
    
    client.println("Connection: close");
    client.println(); // end HTTP header

    while(client.connected()) {
      if(client.available()){
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {// if not connected:
    Serial.println("connection failed");
  }
  }


  void ee(){
    
   String queryString = String("?tirafive=") + String(palima) + String("&bentafive=") + String(sales5)+ String("&lahat=") + String(total);
     
  // initialize the Ethernet shield using DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to obtaining an IP address using DHCP");
    while(true);
  }

  // connect to web server on port 80:
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " " + PATH_FIVE + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    delay(500);
     Serial.println("Nag Send na");
  
    
    client.println("Connection: close");
    client.println(); // end HTTP header

    while(client.connected()) {
      if(client.available()){
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {// if not connected:
    Serial.println("connection failed");
  }
  }



  void ff(){
    
     String queryString = String("?tirasix=") + String(paanim) + String("&bentasix=") + String(sales6)+ String("&lahat=") + String(total);
     
  // initialize the Ethernet shield using DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to obtaining an IP address using DHCP");
    while(true);
  }

  // connect to web server on port 80:
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " " + PATH_SIX + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    delay(500);
     Serial.println("Nag Send na");
  
    
    client.println("Connection: close");
    client.println(); // end HTTP header

    while(client.connected()) {
      if(client.available()){
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {// if not connected:
    Serial.println("connection failed");
  }
  }
