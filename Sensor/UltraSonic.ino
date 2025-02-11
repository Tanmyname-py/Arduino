#define trigPin 12
#define echoPin 11 

void setup(){
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
}
void loop(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 10) {
    Serial.println("the distance is less than 10");
    delay(1500);
} 
if (distance > 60 || distance <= 0){
  Serial.println("The distance is more than 60");
}
}
