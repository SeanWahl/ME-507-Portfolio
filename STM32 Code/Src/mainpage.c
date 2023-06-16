/*! \mainpage 		ME 507 Portfolio
	\brief			Welcome to my portfolio!
	\details		This portfolio documents all the work I put into the Spring 2023 ME 507 Term Project, meant to emulate a Hungry Hungry Hippo type competition.

	\section repo 	Repository Reference
					All files referenced in this repository can be found at the following github: https://github.com/SeanWahl/ME-507-Portfolio 
					Note: All code in the "Additional Code" file has been done by my project partner, Ryan Johnson.

	\section over	Overview
					The goal of this project was simple: design a robot that can compete in a Hungry Hungry Hippo competition in which the robot should move around
					an arena 
					
	\section pages	Pages
					Please peruse through the following subpages to explore the topics you're interested in hearing about!
					- \subpage pcb
					- \subpage sens
					- \subpage mech

	\author 	Sean Wahl
    \date 		June 16, 2023
 */ 

/*! \page pcb 	PCB Design
				For this project, we had to design a full circuit board in order to take battery power and to perform everything that a Hungry Hungry Hippo might need
				to do. I undertook this task and used Fusion 360's Electronics software to design this. The PCB had the following major components:
				- 1 STM32F411CEU6 MCU
				- 1 12V to 5V Switching Regulator
				- 1 5V to 3.3V Linear Voltage Regulator
				- 1 5V Relay
				- 4 DRV8251 H-Bridges for Motor Driving
				- Reset Button
				- 25 MHz crystal oscillator (non-functional)

				Along with these components, we've accounted for connectors for all the peripherals we'll need to control off of the PCB. You can see those in the \subpage sens section.

				You can find all the PCB files in the Github under the Fusion 360 Files Tab. Below are two pictures of the PCB, one bare and one fully assembled.

				\image html PCBBARE.png

				\image html PCBASY.png
 */

/*! \page sens 	Motors and Sensors
				In order to plan for a functioning robot, we needed to choose several sensors that allowed for autonomy. The sensors we included are as follows:
				- 2 Line Followers
				- 1 Color/Proximity Sensor
				- 3 Motors (2 with Encoders)
				- 1 IMU
				- 1 Limit Switch
				- 1 SPI connection (not used)

				The above connections allow for the robot to follow lines, detect colored ping pong balls, drive around, collect balls, orient itself, and detect when it
				is full. We never actually used the SPI connection and instead connected an Arduino with an nrf24L01+ to the board's I2C lines. This was so we could implement
				a deadman's switch for autonomous movement and a joystick for remote control.

				I wrote the code for the IMU, Encoders, Color/Proximity Sensor, and Line Followers which can all be found in this portfolio's files. Ryan wrote the code for the Arduino's
				and Joystick and pulled code for the nrf24's from an online repository.
 */

 /*! \page mech Mechanical Design
				Ryan Johnson was in charge of the mechanical design. A picture is included below but essentially we have two direct drive wheels press-fit onto motor shafts,
				two collector wheels to intake ping pong balls, a ball-chute to hold the ping pong balls, and a follower wheel to balance the design.

				\image html mechdes.png
 */