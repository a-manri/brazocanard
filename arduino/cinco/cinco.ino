#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> //incluir libreria Servo.h
#include <ros.h> //incluir libreria ros.h
#include "std_msgs/MultiArrayLayout.h" //incluir mensajes del tipo MultiArrayLayout
#include "std_msgs/MultiArrayDimension.h" //incluir mensajes del tipo MultiArrayDimension
#include "std_msgs/UInt16MultiArray.h" //incluir mensajes del tipo UInt16MultiArray

ros::NodeHandle  nh; //iniciar NodeHandle (encargado de iniciacion y comunicacion de nodos)

//nombrar servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

void servo_cb( const std_msgs::UInt16MultiArray&  cmd_msg){
  servo1.write(cmd_msg.data[0]); //angulo que toma el servo1
  servo2.write(cmd_msg.data[1]); //angulo que toma el servo2
  servo3.write(cmd_msg.data[2]); //angulo que toma el servo3
  servo4.write(cmd_msg.data[3]); //angulo que toma el servo4
  servo5.write(cmd_msg.data[4]); //angulo que toma el servo5
  digitalWrite(13, HIGH-digitalRead(13));  //prender/apagar led
}


ros::Subscriber<std_msgs::UInt16MultiArray> sub("servo", servo_cb); //suscribir a topico /servo

//
void setup(){
  pinMode(13, OUTPUT);

  nh.initNode(); //iniciar nodo de ROS
  nh.subscribe(sub);

  servo1.attach(8); //asignar al pin 8
  servo2.attach(9); //asignar al pin 9
  servo3.attach(10); //asignar al pin 10
  servo4.attach(11); //asignar al pin 11
  servo5.attach(12); //asignar al pin 12
}

//evitar que el programa termine (repetir)
void loop(){
  nh.spinOnce();
  delay(1);
}
