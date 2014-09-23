#include <AFMotor.h>
#include <Servo.h>
#include <Time.h>
#include <stdlib.h>

Servo servo;
AF_DCMotor motor1(2, MOTOR12_64KHZ);
AF_DCMotor motor2(1, MOTOR12_64KHZ);
int trigpin = 15;
int echopin =14;
int duration, distance, max_distace, angle, distance1;
long st_time;
long ed_time;  
int length =1;

#define char *dir[] {"testing", "F"};
//char* ints;

void setup()
{
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  servo.attach(10);
  Serial.begin(9600);
  motor1.setSpeed(500);
  motor2.setSpeed(500);
  long st_time=millis();
  }

void loop()
{
  int duration, distance, max_distace, angle, distance1;
  max_distace,angle=0;
  servo.write(90);
  //delay(500);
  distance1=get_distance();
  Serial.println("distance forward");
  Serial.println(distance1);
   
  //if the distace if more than 15cm move forward
  
  if (distance1 > 15)

  {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  //if its less than 15 cm check for the angle of farthest obstical

  else
  {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
   
      int distance_0, distance_180;
      servo.write(0);
      distance_0 = get_distance();
      Serial.println(distance_0);
      servo.write(180);
      distance_180 = get_distance();
      Serial.println(distance_180);
      if(distance_0 <50 & distance_180 <50)
      {
      turn_around();
      }
      else
      {
        ed_time = millis()-st_time;
      if (distance_0 < distance_180)
      {
        Serial.println("turning right");
      turn_right();
      }
      else
      {
          Serial.println("turning left");
     turn_left();
      }
      
    }
    st_time = millis();  
  }
  Serial.println(distance);
}

//method to get distance from the nearest object
int get_distance()
{
  int dis,duration;
  digitalWrite(trigpin,HIGH);
  delay(150);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  int obj_dist = (duration/2)/29.1;
  Serial.println("distance from nearest obstrical is" + obj_dist);
  Serial.println(obj_dist);
  delay(300);
  return obj_dist;
  
}

//method to car to a specific angle
void turn_car(int angle1)
{
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(400);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
// turn left
void turn_left()
{
motor1.run(FORWARD);
motor2.run(BACKWARD);
delay(400);
stop();
}

// turn right
void turn_right()
{
motor1.run(BACKWARD);
motor2.run(FORWARD);
delay(500);
stop();
}

// turn around
void turn_around()
{
motor1.run(BACKWARD);
motor2.run(FORWARD);
delay(1000);
stop();
}

void stop()
{
motor1.run(RELEASE);
motor2.run(RELEASE);
}

void go_back(int time)
{
motor1.run(BACKWARD);
motor2.run(BACKWARD);
delay(time);
motor1.run(RELEASE);
motor2.run(RELEASE);

}


