#include "Arduino.h"


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

// String that is sent to request data
char Char1 = 'R';
char Char2 = '\n';
String SendCommand = String(Char1) + String(Char2);

// PWM output pins. This disables timer1 and timer2
int PinPWM1 = 12;
int PinPWM2 = 11;
int PinPWM3 = 10;
int PinPWM4 = 9;

// Initialize input readings
int ch0 = 0;
int ch1 = 0 ;
int ch2 = 0;
int ch3 = 0;
int ch4 = 0;
int ch5 = 0;
int ch6 = 0;
int ch7 = 0;
int ch8 = 0;
int ch9 = 0;
int ch10 = 0;
int ch11 = 0;
int ch12 = 0;
int ch13 = 0;
int ch14 = 0;
int ch15 = 0;

String Output15;

// Analog input channels
int Apin0 = 0;
int Apin1 = 1;
int Apin2 = 2;
int Apin3 = 3;
int Apin4 = 4;
int Apin5 = 5;
int Apin6 = 6;
int Apin7 = 7;
int Apin8 = 8;
int Apin9 = 9;
int Apin10 = 10;
int Apin11 = 11;
int Apin12 = 12;
int Apin13 = 13;
int Apin14 = 14;
int Apin15 = 15;

// Sample time
unsigned long timeS;

// Digital pin, LED for control purposes
int PinOut = 53;
int PinOut2 = 51;

// Set counters to zero
int value = 0;
int val = 0;
// int ReadLed = 0;

// the setup function runs once when you press reset or power the board
void setup() {

  analogReference(EXTERNAL);
  
  // Set the duty cycle for the PWM
  pinMode(PinPWM1, OUTPUT);
  analogWrite(PinPWM1, 128);
  pinMode(PinPWM2, OUTPUT);
  analogWrite(PinPWM2, 192);
  pinMode(PinPWM3, OUTPUT);
  analogWrite(PinPWM3, 171);
  pinMode(PinPWM4, OUTPUT);
  analogWrite(PinPWM4, 150);

  // initialize digital pin PinOut as an output.
  pinMode(PinOut, OUTPUT);
  digitalWrite(PinOut, HIGH);

  // initialize timer3
  noInterrupts();           // disable all interrupts
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3  = 0;

//  OCR3A = 31250;            // compare match register 16MHz/256/2Hz
  // OCR3A = 6250;            // compare match register 16MHz/256/10Hz
  OCR3A = 625;            // compare match register 16MHz/256/100Hz
  TCCR3B |= (1 << WGM12);   // CTC mode
  TCCR3B |= (1 << CS12);    // 256 prescaler
  TIMSK3 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts

  // initialize serial communication.
  Serial.begin(115200); // set the baud rate
  Serial.println("Ready"); // print "Ready" once

  // reserve memory for inputString
  inputString.reserve(200);

}



void loop() {

  // When a newline arrives:
  if (stringComplete) {
    digitalWrite(PinOut2, HIGH);
    //Serial.print("string2:"+inputString);
    //Serial.print("string3:"+String(Char1)+String(Char2));

    // Check it is the string that requests data
    if (inputString == SendCommand) {

      // Send values
      Output15 = String(timeS)+','+String(ch0)+','+String(ch1)+','+String(ch2)+','+String(ch3)+','+String(ch4)+','+String(ch5)+','
        +String(ch6)+','+String(ch7)+','+String(ch8)+','+String(ch9)+
        ','+String(ch10)+','+String(ch11)+','+String(ch12)+','+String(ch13)+','+String(ch14)+','+String(ch15);
      Serial.println(Output15);
      value = value + 1;

      //      digitalWrite(PinOut,HIGH);
      //      delay(50);
      //      digitalWrite(PinOut,LOW);
    }
    else {
      // If it is not the srting to request data, do this:

      //Serial.println("empty");
    }

    // clear the string:
    inputString = "";
    stringComplete = false;
    digitalWrite(PinOut2, LOW);
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  //Serial.flush();
  while (Serial.available()) {
    //delay(10);
    // get the new byte:
    char inChar = (char)Serial.read();
    //delay(10);
    //Serial.println(inChar);
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      //Serial.print("string1:"+inputString);
    }
  }
}

ISR(TIMER3_COMPA_vect)          // timer compare interrupt service routine
{
//  ReadLed=digitalRead(PinOut);
//  digitalWrite(PinOut, !ReadLed);   // toggle LED pin
//  digitalWrite(PinOut, HIGH);
//  delay(5);
  digitalWrite(PinOut, HIGH);
  
  analogRead(Apin0);
  ch0 = analogRead(Apin0);
  
  analogRead(Apin1);
  ch1 = analogRead(Apin1);
  
  analogRead(Apin2);
  ch2 = analogRead(Apin2);
  
  analogRead(Apin3);
  ch3 = analogRead(Apin3);
  
  analogRead(Apin4);
  ch4 = analogRead(Apin4);
  
  analogRead(Apin5);
  ch5 = analogRead(Apin5);
  
  analogRead(Apin6);
  ch6 = analogRead(Apin6);
  
  analogRead(Apin7);
  ch7 = analogRead(Apin7);
  
  analogRead(Apin8);
  ch8 = analogRead(Apin8);
  
  analogRead(Apin9);
  ch9 = analogRead(Apin9);
  
  analogRead(Apin10);
  ch10 = analogRead(Apin10);
  
  analogRead(Apin11);
  ch11 = analogRead(Apin11);
  
  analogRead(Apin12);
  ch12 = analogRead(Apin12);
  
  analogRead(Apin13);
  ch13 = analogRead(Apin13);
  
  analogRead(Apin14);
  ch14 = analogRead(Apin14);
  
  analogRead(Apin15);
  ch15 = analogRead(Apin15);

  timeS = millis();

  digitalWrite(PinOut, LOW);

}



