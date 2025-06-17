
//Devshree EcoBin arduino final
#include <Servo.h>


//Servos
const int servoPin_1 = 9;
Servo myservo;


//Ultrasonic Sensor #1 (blue and orange wires) : LEVEL DETECTION
const int trigPin_s1 = 5; 
const int echoPin_s1 = 4; 


//Ultrasonic Sensor #2 (green and grey wires) : LEVEL DETECTION switched wit bottom
const int trigPin_s2 = 13; 
const int echoPin_s2 = 12; 


//Ultrasonic Sensor #3 (purple and yellow wires) : PYTHON SCRIPT TRIGGERER
const int trigPin_s3 = 7;
const int echoPin_s3 = 6;


//Led #1
const int ledPin_1 = 2;


//Led #2
const int ledPin_2 = 3;

int previous_iteration = 1;


void setup() {
  // put your setup code here, to run once:



  //Servos
  myservo.attach(servoPin_1);


  //Ultrasonic Sensor #1
  pinMode(trigPin_s1, OUTPUT);
  pinMode(echoPin_s1, INPUT);


  //Ultrasonic Sensor #2
  pinMode(trigPin_s2, OUTPUT);
  pinMode(echoPin_s2, INPUT);


  //Ultrasonic Sensor #3
  pinMode(trigPin_s3, OUTPUT);
  pinMode(echoPin_s3, INPUT);


  //LEDs
  pinMode(ledPin_1, OUTPUT);
  pinMode(ledPin_2, OUTPUT);


  Serial.begin(115200);
}


void loop() {
  // put your main code here, to run repeatedly:


  //For Ultrasonic sensor #1:
  digitalWrite(trigPin_s1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_s1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_s1, LOW);


  long duration = pulseIn(echoPin_s1, HIGH);
  int distance = (duration * 0.034) / 2;


  //For Ultrasonic sensor #2
  digitalWrite(trigPin_s2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_s2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_s2, LOW);


  long duration2 = pulseIn(echoPin_s2, HIGH);
  int distance2 = (duration2 * 0.034) / 2;

   //Conditionals for Ultrasonic Sensor's LED mechanism #2:
 
  if (distance2 < 10) {
    digitalWrite(ledPin_1, HIGH);
  } else {
  digitalWrite(ledPin_1, LOW);
  }


  if (distance2 > 10) {
    digitalWrite(ledPin_1, LOW);
  }

  //Conditionals for Ultrasonic Sensor's LED mechanism #1:
  if (distance < 10) {
    digitalWrite(ledPin_2, HIGH);
  }

 
  if (distance > 10) {
    digitalWrite(ledPin_2, LOW);
  }




if (previous_iteration == 1) {
  previous_iteration = 0;
  // For Ultrasonic Sensor #3
  digitalWrite(trigPin_s3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_s3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_s3, LOW);

  long duration3 = pulseIn(echoPin_s3, HIGH);
  int distance3 = (duration3 * 0.034) / 2;

  if (distance3 < 20) {
    Serial.println("detected");
    Serial.read();
    
    //distance3 = 55;
    // delay(1000);
  }
  //distance3 = 55;

  myservo.write(90);
  if (Serial.available() > 0) {
    char result = Serial.read();
    if (result == '2') {
      myservo.write(0);  // Tilt left
      delay(3000);        // Wait for 3 seconds
    } else if (result == '0') {
      myservo.write(180); // Tilt right for any other input
      delay(3000);        // Wait for 3 seconds
    }

    myservo.write(90);      // Move back to the center position
    delay(1000);           // Wait for 1 second before the next iteration
  }
}
  previous_iteration = 1;
}



 
 


