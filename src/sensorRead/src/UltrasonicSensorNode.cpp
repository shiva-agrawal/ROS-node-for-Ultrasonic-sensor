/*
Developer   : Shiva Agrawal
Date        : 20.10.2018
ver         : 1.0
Description : Ultrasonic sensor node to get the distance measurement in cm 
demo call   : open the terminal
              rosrun sensorRead UltrasonicSensorNode

*/

#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <iostream>
#include "wiringPi.h"

typedef unsigned int     uint32_t;
typedef float            float_t;


/*
Function to set the IO pins of raspberry pi used for ultrasonic sensor
*/
void initUltrasonicSensor()
{
	// pin modes
	pinMode(28, OUTPUT);   // header pin 38 connected to trigger of sensor
	pinMode(29, INPUT);   // header pin 40 connected to echo of the sensor
	
	// set trigger pin as low by default
	digitalWrite(28, LOW);
	delay(1000);  // 1 sec time to settle the sensoR
}


/*
function calculates the distance from the obstacle in front of the sensor by sending 
the short duration pulse and calculating the return time.
It used speed of sound in air for calculations and then return the measured distance in cm

@return : measured distance in cm
*/
float_t calculateDistanceInCm()
{
    uint32_t pulse_start = 0;
	uint32_t pulse_end = 0;
	uint32_t pulse_duration = 0;
	float_t distanceInCm = 0;
	float_t SOUND_SPEED_IN_AIR_IN_CM_PER_SEC = 34300;
	
    //measurement process
	
	digitalWrite(28, HIGH); //set trigger high
	delayMicroseconds(10);  // keep trigger high for 10 microseconds
	digitalWrite(28, LOW);  // set trigger low
	
	// sense the high time of the echo pulse 
	
	while(digitalRead(29)==0)
	{
		pulse_start = micros();
		}
		
	while(digitalRead(29)==1)
	{
		pulse_end = micros();
		}
	
	// distance calculation
	
	pulse_duration = pulse_end - pulse_start;	
	
	distanceInCm = pulse_duration*0.000001 * SOUND_SPEED_IN_AIR_IN_CM_PER_SEC/2;
	
	return distanceInCm;
}


/*
main function: it implements the ROS publisher node named as UltrasonicSensorNode
This node measure the distance and publish it on the topic ultrasonicSensorData once every second.
The measurement data is publishes as Float32 of std_msgs (inbulit ROS message type)
*/
int main(int argc, char **argv)
{
	wiringPiSetup();
	
	initUltrasonicSensor();
    
    ros::init(argc, argv, "UltrasonicSensorNode");
    
    ros::NodeHandle n;
    
    ros::Publisher sensorDataPublisher = n.advertise<std_msgs::Float32>("ultrasonicSensorData", 100);
    
    ros::Rate loop_rate(1);
    
    while(ros::ok())
    
    {
		std_msgs::Float32 distanceInCm;
		
		distanceInCm.data = calculateDistanceInCm();
		
		ROS_INFO("Ultrasonic sensor measurement");
		ROS_INFO("Distance from Object :%f cm \n",distanceInCm.data);
		
		sensorDataPublisher.publish(distanceInCm);
		
		ros::spinOnce();
		
		loop_rate.sleep();
		
		
	}
    
    return 0;
	
}
