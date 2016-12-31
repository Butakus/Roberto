# RobertoDriver
This is a driver to control Roberto's functions. Roberto is an experimental rover platform to test sensors, robotic parts and other toys.

The robot is currently controlled by a Raspberry Pi as main computer and an Arduino Mega as low-level driver.
Here you can find the code for the Arduino and the communication libraries for the Raspberry Pi.

## Author
Francisco Miguel Moreno
* butakus@gmail.com
* twitter.com/butakus

## Contents
lib/arduino contains the Arduino libraries libraries to control the hardware mounted on the robot (sensors and actuators).
lib/rpi contains the libraries for the RaspberryPi to enable the communication with the Arduino.

src/ contains the different Arduino modules developed for Roberto.

## TODOs
This will never end. What will be next?
* Add install script to copy Arduino libs into sketchbook directory.
* Finish documentation for current software.
* Add libraries for different sensors.
