#include <UIPEthernet.h>
#include <utility/logging.h>
#include <SPI.h>
#include <PubSubClient.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  //myservo.writeMicroseconds(millis() % 2000);
//  for (pos = 0; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);  // waits 15ms for the servo to reach the position
//  }
//  for (pos = 150; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
}

void acionaPortao(int direcao){
    if(direcao = 0){
      for(pos = 0; pos <= 150; pos += 1){
        myservo.write(pos);
        delay(20);
        Serial.println("Portao Fechando");
      }
     
    }
    else{
      for(pos = 0; pos <= 150; pos -= 1){
        myservo.write(pos);
        delay(20);
        Serial.println("Portao Abrindo");
    }
}

