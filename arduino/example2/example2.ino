#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/UInt16MultiArray.h"

ros::NodeHandle  nh;

Servo servo1;
Servo servo2;

void servo_cb( const std_msgs::UInt16MultiArray&  cmd_msg){
  servo1.write(cmd_msg.data[0]); //set servo angle, should be from 0-180  
  servo2.write(cmd_msg.data[1]); 
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}


ros::Subscriber<std_msgs::UInt16MultiArray> sub("servo", servo_cb);

void setup(){
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);


  servo1.attach(9); //attach it to pin 9
  servo2.attach(10);//attach it to pin10
}

void loop(){
  nh.spinOnce();
  delay(1);
}
