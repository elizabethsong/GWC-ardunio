// Robotics with the BOE Shield - RoamingWithWhiskers
// Go forward.  Back up and turn if whiskers indicate BOE Shield bot bumped
// into something. 

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
 
void setup()                                 // Built-in initialization block
{ 
  pinMode(7, INPUT);                         // Set right whisker pin to input
  pinMode(5, INPUT);                         // Set left whisker pin to input  

  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(13);                      // Attach left signal to pin 13 
  servoRight.attach(12);                     // Attach right signal to pin 12

  Serial.begin(9600);
  
}  
 
void loop()                                  // Main loop auto-repeats
{
  int wLeft = 5;               // Copy left result to wLeft  
  int wRight = 7;              // Copy right result to wRight

  if((digitalRead(wLeft) == LOW) && (digitalRead(wRight) == LOW))          // If both whiskers contact
  {
    backward(1000);                          // Back up 1 second
    turnLeft(800);                           // Turn left about 120 degrees
    Serial.println("Both whiskers.");
    digitalWrite(8, HIGH);
    digitalWrite(2, HIGH);
  }
  else if(digitalRead(wLeft) == LOW)                       // If only left whisker contact
  {
    backward(1000);                          // Back up 1 second
    turnRight(400);                          // Turn right about 60 degrees
    Serial.println("Left whisker.");
    digitalWrite(8, HIGH);
  }
  else if(digitalRead(wRight) == LOW)                       // If only right whisker contact
  {
    backward(1000);                          // Back up 1 second
    turnLeft(400);   // Turn left about 60 degrees
    Serial.println("Right whisker.");
    digitalWrite(2, HIGH);
  }
  else                                       // Otherwise, no whisker contact
  {
    forward(20);                             // Forward 1/50 of a second
    Serial.println("Forward.");
    digitalWrite(2, LOW); 
    digitalWrite(8, LOW);
  }
}

void forward(int time)                       // Forward function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnLeft(int time)                      // Left turn function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnRight(int time)                     // Right turn function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
}

void backward(int time)                      // Backward function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel clockwise
  servoRight.writeMicroseconds(1300);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
}

