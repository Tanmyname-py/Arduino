#include <Servo.h> 
Servo myservo; // inisiasi nama variabel servo
int pos = 0 ; // deklarasi variabel intuk posisi servo 

void setup(){
  myservo.attach(6); // inisiasi pin servo
}

void loop(){
  for ( pos = 0; pos <=180; pos +=1 ){
     myservo.write(pos);
     delay(20);
  }
  for ( pos = 180; pos >=180; pos -=1 ){
     myservo.write(pos);
     delay(20);
  }
  }
