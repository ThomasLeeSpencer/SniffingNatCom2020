//stepper motor variables and pins
int MotorPin = 13;  //LED connected to digital pin 13
int OnPin = 7; //En connected to pin 7
int DirectionPin = 4; //Dr connected to pin 4
int counter = 0;
int counter1 = 0;
int toggle = 1;

//define variables
int stepDelay = 8000;
int DesiredAnglePulse = 90;
int DesiredAngleFirst = 5*360-15-DesiredAnglePulse; //pulses start in same initial direction 
int EncoderSteps = 2000*(DesiredAnglePulse/360); //2000 encoder steps per revolution, maxed out at 65535, resets to 0

int FirstSteps = DesiredAngleFirst*1.11111; //This motor is 0.9deg per step so (360 deg/rev)/(0.9 deg/step) is 400 steps per revolution, (400 steps/rev)/(360 deg/rev) = (1.1111 steps/deg)
int PulseSteps = DesiredAnglePulse*1.11111;
int originalSteps = PulseSteps;

// encoder variables and pins
enum PinAssignments 
{
  encoderPinA = 2,
  encoderPinB = 3
};

volatile unsigned int encoderPos = 0;
unsigned int lastReportedPos = 1;

boolean A_set = false;
boolean B_set = false;


void setup() 
{
  pinMode(MotorPin, OUTPUT);  //sets the digital pin as output
  pinMode(OnPin, OUTPUT); //sets the digital pin as output
  pinMode(DirectionPin, OUTPUT);  //sets the digital pin as output
  digitalWrite(OnPin, HIGH);
  digitalWrite(DirectionPin, LOW); //start counter clockwise if low
  
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  digitalWrite(encoderPinA, HIGH);  //turn on pull-up resistor
  digitalWrite(encoderPinB, HIGH);  //turn on pull-up resistor

  //encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  //encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  Serial.begin(9600);
}

void loop() 
{
  counter1 = counter1+1;
  if(counter1 < FirstSteps) //1.8 steps per degree so to get 90 deg use 50 steps. 2 "counts" per step so 100 counts per 90 deg
  {
    //first slowly pump out two full rotations to remove previous air
    digitalWrite(MotorPin, HIGH);   
    delayMicroseconds(2000);
    digitalWrite(MotorPin, LOW);    
    delayMicroseconds(2000); 
  }
  //after initial rotations, pulse normally
  counter = counter+1;
  int sweepStart = min(encoderPos,65535 - encoderPos); //take encoder reading at beginning of sweep
  if(counter1 >= FirstSteps && counter < PulseSteps) //if done with initial clearing pumps, and isn't time to switch direction
  {
    //Move rotor
    digitalWrite(MotorPin, HIGH);   
    delayMicroseconds(stepDelay); //Max speed is at 215, 1066.6 gives freq of 5 hz with 45 degree angle (input of 50)
    digitalWrite(MotorPin, LOW);    
    delayMicroseconds(stepDelay); //@250, Takes 500 us per 1.8 degrees so 0.045 seconds to rotate 90 deg or 1 rev in 0.18 sec so 5.55 revs per second max (5.55 Hz pulses)
    if(lastReportedPos != encoderPos) //allows encoder readings to be seen in Serial Monitor window
    {
      //Commented out because reading from serial port slows performance
      //Serial.print("Index:");
      //Serial.print(encoderPos, DEC);
      //Serial.println();
      lastReportedPos = encoderPos;
    }
  }
  else if(counter1 >= FirstSteps && counter >= PulseSteps) //switch direction
  {
    int sweepEnd = min(encoderPos,65535 - encoderPos); //take encoder reading at end of sweep
    int deltaSteps = EncoderSteps - (sweepEnd - sweepStart); //find steps lost or gained as indicated by encoder
    PulseSteps = originalSteps + (deltaSteps/5);  //divide deltaSteps by 5 to convert it to stepper motor steps, since there are 2000 encoder steps/rev and 400 stepper motor steps/rev
    switch (toggle) 
    {
      case 1:
      digitalWrite(DirectionPin,LOW); //change direction to counterclockwise
      toggle=2; //alternate variable for next sweep
      break;
      case 2:
      digitalWrite(DirectionPin,HIGH);  //change direction to clockwise
      toggle=1; //alternate variable for next sweep
      break;
    }
    counter = 0; //reset count to again move the desired number of degrees
    counter1=FirstSteps+1; //make sure it doesn't go back to first pulses if counter1 exceeds number allowed for class "int"
  }
} //end main loop

//Interrupt on A changing state
void doEncoderA() 
{
  //Test transition
  A_set = digitalRead(encoderPinA) == HIGH;
  //and adjust counter + if A leads B
  encoderPos += (A_set != B_set) ? +1 : -1;
}

//Interrupt on B changing state
void doEncoderB() 
{
  //Test transition
  B_set = digitalRead(encoderPinB) == HIGH;
  //and adjust counter + if B follows A
  encoderPos += (A_set == B_set) ? +1 : -1;
}

