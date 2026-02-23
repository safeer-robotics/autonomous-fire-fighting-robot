# Autonomous Firefighting Robot

This is my Industrial Robotics coursework project. I designed and tested an autonomous firefighting robot that can detect a fire direction, move safely in an indoor area, avoid obstacles, and then activate a fire response action. I built and tested the full system in Autodesk Tinkercad first, so I could validate the circuit and control logic before making a real prototype.

Tinkercad live demo:
https://www.tinkercad.com/things/8jLVSEBx8tk-autonomous-firefighting-robot?sharecode=nugWTiz1tKH3NpDTqJD4J3bhmhl7Qs6w_UPtOAC5yE0

Note: Anyone can open the link and view the circuit and code. To change anything, a user usually needs to log in and make a copy.

## Project goal

My goal was to build a simple and complete robotics workflow where the robot senses the environment, makes a decision, moves, and then responds. The robot should search for a fire source, identify the direction of the fire, drive toward it safely, avoid obstacles, stop at a safe distance, and trigger a fire response behaviour.

## What I built

Fire direction detection using multiple LDR light sensors placed on the left, centre, and right

Obstacle detection using an ultrasonic distance sensor

Autonomous navigation logic for forward movement, left and right turning, and recovery behaviour

Motor control using DC motors and a motor driver

Servo control for steering or nozzle aiming as a concept

Fire response output in simulation to represent a pump or fan action

## How it works

The robot keeps reading the sensors in a loop.

First, it checks the ultrasonic sensor distance. If an obstacle is close, the robot slows down or stops and turns away to keep a safe path. If it cannot move safely, it reverses and performs a recovery turn.

Then it checks the LDR sensors. If the left sensor reads higher light, the robot turns left. If the right sensor reads higher light, it turns right. If the centre sensor reads higher light, the robot moves forward. When the fire source is considered close enough, the robot stops and activates the fire response output. In a real build, this output can control a fan, pump, or servo based nozzle.

This project helped me understand that good robotics behaviour needs stable sensor readings, correct thresholds, and careful timing so the robot does not react randomly.

## Components used in the Tinkercad setup

Arduino Uno R3

LDR sensors for left, centre, and right fire direction sensing

Ultrasonic sensor for obstacle detection

DC motors for movement

Motor driver for controlling the motors

Servo motor for steering or nozzle direction concept

LED and resistors for status or fire response indication

## Tools and language

Autodesk Tinkercad for simulation

Arduino C or C++ for programming

Embedded concepts like sensor integration, motor control, thresholds, and decision logic

## Repository structure

README.md contains the project overview and working explanation

docs folder contains the coursework report PDF

code folder contains the Arduino sketch file

media folder can contain screenshots if added

## How to run it in Tinkercad

Open the Tinkercad link

Click Start Simulation

Test fire direction sensing by moving a light source near the LDR sensors

Place obstacles and confirm the robot changes direction safely

Check that the robot stops and triggers the fire response action when the fire is close

## Real prototype notes

This project was tested in simulation, but it can be built as a real prototype using the same components. For real hardware, I would calibrate the sensors, handle noise, improve power management, and test carefully with proper safety precautions.

## What I learned

Designing robot behaviour using sensor feedback

Combining fire sensing and obstacle avoidance in one control logic

Motor and servo control using Arduino

Testing and validating in simulation before building hardware

Writing a complete technical coursework report with results, limitations, and improvements

## Author

Safeer Ahmed
Email: safeerahmed5471@gmail.com
