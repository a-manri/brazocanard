#!/usr/bin/env python

import rospy #importar ros para python
from std_msgs.msg import String, UInt16MultiArray #importar mensajes de ROS tipo String, y UInt16MultiArray
from sensor_msgs.msg import Joy #importar mensajes de tipo Joy

class Template(object):
	def __init__(self, args):
		super(Template, self).__init__()
		self.args = args
		self.sub = rospy.Subscriber('/duckiebot/joy', Joy, self.callback)
		self.pub = rospy.Publisher('/servo', UInt16MultiArray, queue_size=0)			
		self.uint = UInt16MultiArray()
		self.uint.data = [90, 90, 0, 180, 0] #angulos posicion inicial
	
	def callback(self,msg):
		back = msg.buttons[6]; #volver a posicion inicial
		y = msg.buttons[3]; #garra soltar
		x = msg.buttons[2]; #garra apretar
		dUp = msg.buttons[13]; #muneca arriba
		dDwn = msg.buttons[14]; #muneca abajo
		Rsv = msg.axes[4]; #pitch
		Rsh = msg.axes[3]; #yaw
		d = 0.15 #delta error
		
		#condiciones para movimiento (cambio de angulos)
		if y == 1 or x == 1: #garra
			if 0 <= self.uint.data[0] and self.uint.data[0] <= 180: 	
				rospy.loginfo("Garra")
				self.uint.data[0] = self.uint.data[0] + 10*x - 10*y
			if 0 >= self.uint.data[0]:
				self.uint.data[0]=0
			if 180 <= self.uint.data[0]:
				self.uint.data[0]=180

		elif dUp == 1 or dDwn == 1: #muneca
			if 0 <= self.uint.data[1] and self.uint.data[1] <= 180: 
				rospy.loginfo("Muneca")
				self.uint.data[1] = self.uint.data[1] + 10*dUp -10*dDwn
			if 0 >= self.uint.data[1]:
				self.uint.data[1] = 0
			if 180 <= self.uint.data[1]:
				self.uint.data[1] = 180	
		elif d < Rsv or Rsv < -d: #pitch
			if 0 <= self.uint.data[2] and self.uint.data[2] <= 180: 
				rospy.loginfo("Pitch")
				self.uint.data[2] = self.uint.data[2] + 5*Rsv
				self.uint.data[3] = 180 - self.uint.data[2]
			if 0>= self.uint.data[2]:
				self.uint.data[2]=0
				self.uint.data[3]=180
			if 180<= self.uint.data[2]:
				self.uint.data[2]=180	
				self.uint.data[3]=0
		elif d < Rsh or Rsh < -d: #yaw
			if 0 <= self.uint.data[4] and self.uint.data[4] <= 180:
				rospy.loginfo("Yaw")
				self.uint.data[4] = self.uint.data[4] + 5*Rsh
			if 0 >= self.uint.data[4]:
				self.uint.data[4]=0
			if 180 <= self.uint.data[4]:
				self.uint.data[4]=180

		elif back == 1: #volver a posicion inicial
			rospy.loginfo("Reset")
			self.uint.data = [90, 90, 0, 180, 0]

		else: #mantenerse quieto
			rospy.loginfo("Quieto")

		self.pub.publish(self.uint) #publicar los angulos en el topico /servo

def main():
	rospy.init_node('template') #creacion y registro del nodo
	obj = Template('args') # Crea un objeto del tipo Template, cuya definicion se encuentra arriba
	rospy.spin() #funcion de ROS que evita que el programa termine

if __name__ =='__main__':
	main()
