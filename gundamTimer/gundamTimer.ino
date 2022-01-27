/*
  Controlling Servo with Millis
  https://forum.arduino.cc/t/controlling-servo-with-millis/222445/6

  Adapted code from:
  Arduino Tutorials: Control a LED with a Button
  https://www.youtube.com/watch?v=ksNbEuhO4fU
*/

#include <Servo.h>

Servo myservo;    // create servo object to control a servo

int buttonstate;
int stopstate;

int Button = 3;       // input for reading the push button
int greenLED = 7;     // output for controlling the green LED
int redLED = 2;       // output for controlling the red LED

// From https://forum.arduino.cc/t/controlling-servo-with-millis/222445/5
int position = 0 ;    // state variable
boolean forward = false ;   // state variable

unsigned long ts = millis () ;   // time accounting.
#define DELAY 20
// End of code from https://forum.arduino.cc/t/controlling-servo-with-millis/222445/5

void setup() {
  myservo.attach(9);    // attaches the servo on pin 9 to the servo object

  // Adapted from https://www.youtube.com/watch?v=ksNbEuhO4fU
  pinMode(Button, INPUT);   // initialize digital pin 3 as an output
  pinMode(greenLED, OUTPUT);     // initialize digital pin 2 as an output
  pinMode(redLED, OUTPUT);     // initialize digital pin 2 as an output
}

void loop() {
  buttonstate = digitalRead(Button);    // read button input
  
  if (buttonstate == HIGH) {
    buttonstate = LOW;
    stopstate = LOW;
    digitalWrite(redLED, LOW);          // set the redLED to off
    digitalWrite(greenLED, HIGH);       // set the greenLED to on
    delay(10000);                       // wait for 10 seconds
    digitalWrite(greenLED, LOW);        // set the greenLED to off
    digitalWrite(redLED, HIGH);
    
    while (stopstate == LOW) {
      stopstate = digitalRead(Button);

      // From https://forum.arduino.cc/t/controlling-servo-with-millis/222445/5
      if (millis () - ts >= DELAY)
      {
        //digitalWrite(redLED, HIGH);
        ts += DELAY ;   // setup timestamp for next time.
        if (forward)
        {
          myservo.write (-- position) ;  // progress the servo
          if (position == 0)  // test for reverse
            forward = false ;
        }
        else
        {
          myservo.write (++ position) ;  // progress the servo
          if (position == 60)  // test for reverse
            forward = true ;
        }
      }
      // End of code from https://forum.arduino.cc/t/controlling-servo-with-millis/222445/5
    }
  }
}
