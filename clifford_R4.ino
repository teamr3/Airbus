#include <Adafruit_NeoPixel.h>

//#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            19
#define NUMPIXELS      12
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500;

int currentColour = 0;
int currentXoffset;
int currentYoffset;
int blobCounter;




//IO Pin Assignments 
int drillPin = 15;

int quillSolPin = 0;
int housingSolPin = 1;
int bigBenPin = 2;

int xStepperStep = 4;
int xStepperDir = 3;
int yStepperStep = 5;
int yStepperDir = 14;

int lsA = 6;
int lsB = 7;
int lsC = 8;
int lsD = 9;
int lsE = 10;
int lsF = 11;

int pauseButton = 16;
 
// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
int led = 13;



//Hole Pattern Data
const float plateAngle = 0.0;

float datumHoles[3][2] = {
{-250.0,0.0},
{-250.0,-250.0},
{250.0,0.0}
};

float constrainedHoles[10][2] = {
{12.5,-212.5},
{37.5,-212.5},
{62.5,-212.5},
{87.5,-212.5},
{112.5,-212.5},
{137.5,-212.5},
{162.5,-212.5},
{187.5,-212.5},
{212.5,-212.5},
{237.5,-212.5}
};

float patternCoords[252][2] = {
{-225.0,75.0}, {-225.0,50.0}, {-225.0,25.0}, {-225.0,0.0}, {-225.0,-25.0}, {-225.0,-50.0}, {-225.0,-75.0}, 
{-200.0,75.0}, {-200.0,50.0}, {-200.0,25.0}, {-200.0,0.0}, {-200.0,-25.0}, {-200.0,-50.0}, {-200.0,-75.0}, 
{-175.0,75.0}, {-175.0,50.0}, {-175.0,25.0}, {-175.0,0.0}, {-175.0,-25.0}, {-175.0,-50.0}, {-175.0,-75.0}, 
{-150.0,75.0}, {-150.0,50.0}, {-150.0,25.0}, {-150.0,0.0}, {-150.0,-25.0}, {-150.0,-50.0}, {-150.0,-75.0}, 
{-125.0,75.0}, {-125.0,50.0}, {-125.0,25.0}, {-125.0,0.0}, {-125.0,-25.0}, {-125.0,-50.0}, {-125.0,-75.0}, 
{-100.0,75.0}, {-100.0,50.0}, {-100.0,25.0}, {-100.0,0.0}, {-100.0,-25.0}, {-100.0,-50.0}, {-100.0,-75.0}, 
{-75.0,75.0}, {-75.0,50.0}, {-75.0,25.0}, {-75.0,0.0}, {-75.0,-25.0}, {-75.0,-50.0}, {-75.0,-75.0}, 
{-50.0,75.0}, {-50.0,50.0}, {-50.0,25.0}, {-50.0,0.0}, {-50.0,-25.0}, {-50.0,-50.0}, {-50.0,-75.0}, 
{-25.0,75.0}, {-25.0,50.0}, {-25.0,25.0}, {-25.0,0.0}, {-25.0,-25.0}, {-25.0,-50.0}, {-25.0,-75.0}, 
{0.0,75.0}, {0.0,50.0}, {0.0,25.0}, {0.0,0.0}, {0.0,-25.0}, {0.0,-50.0}, {0.0,-75.0}, 
{25.0,75.0}, {25.0,50.0}, {25.0,25.0}, {25.0,0.0}, {25.0,-25.0}, {25.0,-50.0}, {25.0,-75.0}, 
{50.0,75.0}, {50.0,50.0}, {50.0,25.0}, {50.0,0.0}, {50.0,-25.0}, {50.0,-50.0}, {50.0,-75.0}, 
{75.0,75.0}, {75.0,50.0}, {75.0,25.0}, {75.0,0.0}, {75.0,-25.0}, {75.0,-50.0}, {75.0,-75.0}, 
{100.0,75.0}, {100.0,50.0}, {100.0,25.0}, {100.0,0.0}, {100.0,-25.0}, {100.0,-50.0}, {100.0,-75.0}, 
{125.0,75.0}, {125.0,50.0}, {125.0,25.0}, {125.0,0.0}, {125.0,-25.0}, {125.0,-50.0}, {125.0,-75.0}, 
{150.0,75.0}, {150.0,50.0}, {150.0,25.0}, {150.0,0.0}, {150.0,-25.0}, {150.0,-50.0}, {150.0,-75.0}, 
{175.0,75.0}, {175.0,50.0}, {175.0,25.0}, {175.0,0.0}, {175.0,-25.0}, {175.0,-50.0}, {175.0,-75.0}, 
{200.0,75.0}, {200.0,50.0}, {200.0,25.0}, {200.0,0.0}, {200.0,-25.0}, {200.0,-50.0}, {200.0,-75.0}, 
{225.0,75.0}, {225.0,50.0}, {225.0,25.0}, {225.0,0.0}, {225.0,-25.0}, {225.0,-50.0}, {225.0,-75.0}, 
{25.0,275.0}, {25.0,250.0}, {25.0,225.0}, {25.0,200.0}, {25.0,175.0}, {25.0,150.0}, {25.0,125.0}, 
{50.0,275.0}, {50.0,250.0}, {50.0,225.0}, {50.0,200.0}, {50.0,175.0}, {50.0,150.0}, {50.0,125.0}, 
{75.0,275.0}, {75.0,250.0}, {75.0,225.0}, {75.0,200.0}, {75.0,175.0}, {75.0,150.0}, {75.0,125.0}, 
{100.0,275.0}, {100.0,250.0}, {100.0,225.0}, {100.0,200.0}, {100.0,175.0}, {100.0,150.0}, {100.0,125.0}, 
{125.0,275.0}, {125.0,250.0}, {125.0,225.0}, {125.0,200.0}, {125.0,175.0}, {125.0,150.0}, {125.0,125.0}, 
{150.0,275.0}, {150.0,250.0}, {150.0,225.0}, {150.0,200.0}, {150.0,175.0}, {150.0,150.0}, {150.0,125.0}, 
{175.0,275.0}, {175.0,250.0}, {175.0,225.0}, {175.0,200.0}, {175.0,175.0}, {175.0,150.0}, {175.0,125.0}, 
{200.0,275.0}, {200.0,250.0}, {200.0,225.0}, {200.0,200.0}, {200.0,175.0}, {200.0,150.0}, {200.0,125.0}, 
{225.0,275.0}, {225.0,250.0}, {225.0,225.0}, {225.0,200.0}, {225.0,175.0}, {225.0,150.0}, {225.0,125.0}, 
{-225.0,-125.0}, {-225.0,-150.0}, {-225.0,-175.0}, {-225.0,-200.0}, {-225.0,-225.0}, {-225.0,-250.0}, {-225.0,-275.0}, 
{-200.0,-125.0}, {-200.0,-150.0}, {-200.0,-175.0}, {-200.0,-200.0}, {-200.0,-225.0}, {-200.0,-250.0}, {-200.0,-275.0}, 
{-175.0,-125.0}, {-175.0,-150.0}, {-175.0,-175.0}, {-175.0,-200.0}, {-175.0,-225.0}, {-175.0,-250.0}, {-175.0,-275.0}, 
{-150.0,-125.0}, {-150.0,-150.0}, {-150.0,-175.0}, {-150.0,-200.0}, {-150.0,-225.0}, {-150.0,-250.0}, {-150.0,-275.0}, 
{-125.0,-125.0}, {-125.0,-150.0}, {-125.0,-175.0}, {-125.0,-200.0}, {-125.0,-225.0}, {-125.0,-250.0}, {-125.0,-275.0}, 
{-100.0,-125.0}, {-100.0,-150.0}, {-100.0,-175.0}, {-100.0,-200.0}, {-100.0,-225.0}, {-100.0,-250.0}, {-100.0,-275.0}, 
{-75.0,-125.0}, {-75.0,-150.0}, {-75.0,-175.0}, {-75.0,-200.0}, {-75.0,-225.0}, {-75.0,-250.0}, {-75.0,-275.0}, 
{-50.0,-125.0}, {-50.0,-150.0}, {-50.0,-175.0}, {-50.0,-200.0}, {-50.0,-225.0}, {-50.0,-250.0}, {-50.0,-275.0}, 
};

boolean holeIsDrilled [252];

double absoluteXPosition, absoluteYPosition;
double localXPosition, localYPosition; //Position of the centre drill 
float cameraXOffset = -50.0; //Measure these values (to the centre drill)
float cameraYOffset = 50.0;

boolean encodersEnabled = false;
int encoderAXPin = 0;
int encoderBXPin = 0;
int encoderAYPin = 0;
int encoderBYPin = 0;

long programStartTime = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(115200);

  //Initialize IO Pins
  pinMode(led, OUTPUT);  
  digitalWrite(led, LOW);

  pinMode(drillPin, OUTPUT);
  digitalWrite(drillPin, HIGH);

  pinMode(quillSolPin, OUTPUT);
  pinMode(housingSolPin, OUTPUT);
  pinMode(bigBenPin, OUTPUT);

  digitalWrite(quillSolPin, HIGH);
  digitalWrite(housingSolPin, HIGH);
  digitalWrite(bigBenPin, HIGH);

  pinMode(xStepperStep,OUTPUT);
  pinMode(xStepperDir,OUTPUT);
  pinMode(yStepperStep,OUTPUT);
  pinMode(yStepperDir,OUTPUT);

  digitalWrite(xStepperStep,HIGH);
  digitalWrite(xStepperDir,HIGH);
  digitalWrite(yStepperStep,HIGH);
  digitalWrite(yStepperDir,HIGH);

  pinMode(lsA, INPUT);
  pinMode(lsB, INPUT);
  pinMode(lsC, INPUT);
  pinMode(lsD, INPUT);
  pinMode(lsE, INPUT);
  pinMode(lsF, INPUT);

  pinMode(pauseButton, INPUT_PULLUP);
  digitalWrite(pauseButton, HIGH);
//
//  if (encodersEnabled)
//  {
//    //Enable pins with pullup resistors, attach ISRs
//    pinMode(encoderAXPin, INPUT);
//    digitalWrite(encoderAXPin, HIGH);
//    pinMode(encoderBXPin, INPUT);
//    digitalWrite(encoderBXPin, HIGH);
//    attachInterrupt(encoderAXPin, encoderAX, CHANGE);
//    attachInterrupt(encoderBXPin, encoderBX, CHANGE);
//
//    pinMode(encoderAYPin, INPUT);
//    digitalWrite(encoderAYPin, HIGH);
//    pinMode(encoderBYPin, INPUT);
//    digitalWrite(encoderBYPin, HIGH);
//    attachInterrupt(encoderAYPin, encoderAY, CHANGE);
//    attachInterrupt(encoderBYPin, encoderBY, CHANGE);
//    
//  }

  for (int i=0; i<252; i++)
    holeIsDrilled[i] = false;

  //Adjust coordinates
  mirrorX();
  if (plateAngle != 0.0)
  {
    rotateCoords();
  }

  
  pixels.begin();
  setColour(5);

  
}

// the loop routine runs over and over again forever:
void loop() {

//   digitalWrite(housingSolPin, LOW);\
//   delay(5000);
//
//  fireBigBen();
//  drillsOn();
//  housingDown();
//   digitalWrite(housingSolPin, LOW);
//  delay(20000);
//  housingUp();
//  drillsOff();
//  delay(5000);
//  retractBigBen();
//
//  abort();
  
  delay(1000);
  
  while(digitalRead(pauseButton)==HIGH)
  {
    delay(1);
    digitalWrite(led, HIGH);
  }
  programStartTime = millis();
  
  delay(7000);
  
  fireBigBen();

 //homeMachine();

 //seekDatum();

 absoluteXPosition = 0.0;
 absoluteYPosition = 0.0;
 
 //lookForHole();

 localXPosition = datumHoles[0][0];
 localYPosition = datumHoles[0][1];


 drillConstrainedHoles();

// seekDatum();
//
// lookForHole();

 drillHolePattern();

 endSequence();
  
}

void handlePauseButton()
{
  
  if (digitalRead(pauseButton) == HIGH)
  {
    drillsOff();
    housingUp();
    quillUp();
    while(digitalRead(pauseButton) == HIGH)
    {
      delay(1);
    }
  }
}

void handleTimeout()
{
  if(millis() - programStartTime > 3660000)
  {
    endSequence();
  }
}

void endSequence()
{
  digitalWrite(led, HIGH);
  drillsOff();
  quillUp();
  housingUp();
  
  homeMachine();
  retractBigBen();
  while(true)
  {
    delay(1000);
  }

}

