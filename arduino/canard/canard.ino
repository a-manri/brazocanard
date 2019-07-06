//Librerias
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;


Servo servito1;
Servo servito2;
Servo servito3;
Servo servito4;


void servito1_cb( const std_msgs::UInt16&  cmd_msg){
  servito1.write(cmd_msg.data); //set servito angle, should be from 0-180   
}

void servito2_cb( const std_msgs::UInt16&  cmd_msg){
  servito2.write(cmd_msg.data); //set servito angle, should be from 0-180   
}

void servito3_cb( const std_msgs::UInt16&  cmd_msg){
  servito3.write(cmd_msg.data); //set servito angle, should be from 0-180   
}

void servito4_cb( const std_msgs::UInt16&  cmd_msg){
  servito4.write(cmd_msg.data); //set servito angle, should be from 0-180   
}

ros::Subscriber<std_msgs::UInt16> sub1("servito1", servito1_cb);
ros::Subscriber<std_msgs::UInt16> sub2("servito2", servito2_cb);
ros::Subscriber<std_msgs::UInt16> sub3("servito3", servito3_cb);
ros::Subscriber<std_msgs::UInt16> sub4("servito4", servito4_cb);


void setup() {
  
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  
  Serial.begin(9600);
  servito1.attach(4);
  servito2.attach(5);
  servito3.attach(6);
  servito4.attach(7);
}

void loop() {
  nh.spinOnce();
  delay(20);  // put your main code here, to run repeatedly:

}
