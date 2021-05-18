# ROS publisher node development for distance measurement using Ultrasonic sensor and Raspberry pi 3

Perception is the very first step for the development of any Robot or robotic system. As I am working the the field of robotics with the main focus towards self driving vehicles, this project is developed to implement the Ultrasonic sensor driver in the form of the ROS publisher node.

For the project, ROS node is developed using C++. The sensor (HC-SR04) is interfaced with Raspberry pi 3 model B running ROS Kinetic on it. The ROS node, mesures the distance from the obstacle in front of the sensor and publish it every once in a second (1 Hz).

The ROS node is tested for different distances and all the scrrenshots are stored here.


## Project Folder structure

1. docs 
    * Project details.pdf - detailed project report covering hardware and software description
    * HC-SR04_ultrasonic_module_user_guide.pdf - user guide to understand working of ultrasonic sensor
2. src
    * sensorRead - ROS package containing files of the project
    
3. test
    * Obstacle_at_measurement_01, Obstacle_at_measurement_01, Obstacle_at_measurement_01 - photos of the obstacle and sensor during test
    * ros master start.png - screenshot of Ubuntu Terminal for starting ROS master
    * UltrasonicSensorMeasurement_01, UltrasonicSensorMeasurement_02, UltrasonicSensorMeasurement_03 - ROS node output
