#include <Servo.h>

//Pins used: 2345,54329876//Change some pins

// Include Libraries
#include <Servo.h>
#include <Keypad.h>



// Define pins for distance sensors
#define trigPin1 2
#define echoPin1 30
#define trigPin2 3
#define echoPin2 31


// define global variables
long sduration1, sduration2;
float sdistance1, sdistance2;
bool movementL, movementR;
bool enterNums;
String enteredNums;
int x;
int angle;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
Servo turnS;
Servo shootS;
int ena=6;
int in1=32;
int in2=33;
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28, 29}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup()
{

Serial.begin (9600);
// PinModes
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(ena, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
turnS.attach(4);
shootS.attach(5);
// Get Starting Positions


// Use Ultrasonic Left
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
sduration1 = pulseIn(echoPin1, HIGH);
// Use Ultrasonic Right
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
sduration2 = pulseIn(echoPin2, HIGH);
// Calculate distance
sdistance1 = sduration1 * 0.034 / 2;
sdistance2 = sduration2 * 0.034 / 2;
enterNums = false;
}

void loop() {
// Define kind of variables
long duration1, duration2;
float distance1, distance2;

// Use Ultrasonic Left
digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
// Use Ultrasonic Right
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
// Calculate distance
distance1 = duration1 * 0.034 / 2;
distance2 = duration2 * 0.034 / 2;

// Test print
if (enterNums == false){
  getNumbers();
}
if (enterNums == true) {
  getDirection(distance1, distance2, sdistance1, sdistance2);
  shootEmJohn(angle);
  delay(100);
}
}
// Test print function

void getDirection(int d1, int d2, int s1, int s2)
{
  int angle1;
  if ((d1 < (s1-7)))
  {
    Serial.println("LEFT");
    angle1=atan2(d1/x);
    angle=angle1*(180/3.14159)
  }
  if ((d2 < (s2-7)))
  {
    Serial.println("RIGHT");
    angle1=atan2(d2/x);
    angle=angle1*(180/3.14159)


  }
  
}
void getNumbers()
{
  String customKey=customKeypad.getKey();
  if (customKey){
    if (customKey != 'A'){
      enteredNums = enteredNums+customKey;

    }
    if (customKey == 'A'){
      x = int(enteredNums);
      enterNums = true;
    }
  }
  
}
void shootEmJohn(a)
{
  turnS.write(a);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 255);
  delay(200);
  shootS.write(30);
  delay(1000);
  turnS.write(-a);
  shootS.write(0);
  analogWrite(ena,0);  
}

