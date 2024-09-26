# Laberinto Maze Solving Robot

## Overview
This repository contains the code and documentation for the Laberinto team's robot, developed for the RoboCupJunior 2023 Rescue Maze category. The robot is designed to navigate a maze, detect victims, and deploy rescue kits autonomously.

## Team Members
- **Ahmed Wael**: Software Development
- **Ahmad Zaki**: Team Leader, Software Development
- **Abdullah Ayman**: Electrical System
- **Adam Mohamed**: Mechanical Design

Mentors:
- **Adham Amr**
- **Amr El Shabacy**

## Robot Overview
Our robot is equipped with a variety of sensors and custom mechanisms, allowing it to effectively navigate through a maze, identify victims, and deploy rescue kits.

### Hardware
- **PCB Plate**: The robot’s top plate doubles as a PCB, minimizing wiring and simplifying debugging. It connects the microcontrollers and other electrical components.
- **Rescue Kit Mechanism**: The robot features a 3D-printed mechanism that holds and deploys up to 12 rescue kits (6 on each side), with the ability to deploy kits to either side depending on victim positioning.
- **Sensors**:
  - 5x **TOF Sensors** for distance measurement
  - 2x **OpenMV H7 Cameras** for victim detection
  - **IMU** for orientation and movement control

### Electrical System
- **Microcontrollers**: The robot uses an Arduino Mega for controlling actuators and rescue mechanisms, and an Arduino Nano for sensor readings, which are communicated to the Mega via SPI.
- **Power**: Powered by a 9600 mAh 3S battery and a DC-DC voltage regulator.

### Software
The robot uses a right-hand algorithm to navigate the maze, supplemented by data from TOF sensors and encoders. The algorithm records wall and victim positions during the first pass through the maze, then attempts to visit unvisited tiles.

Key features:
- **Victim Detection**: Uses OpenMV cameras to detect and classify victims based on color (red, yellow, green) or shape.
- **IMU**: The built-in IMU in the Arduino Nano is used for accurate 90-degree turns and detecting ramps.

## Performance and Testing
The robot was tested extensively with different maze configurations to optimize both the hardware and software systems. Testing includes:
- **Hardware**: A checklist is used to verify that all mechanical and electrical components are functioning properly before each test.
- **Software**: The algorithm is tested by running the robot on various maps, adjusting and improving its performance based on the scores achieved.

## References
- [Laberinto GitHub Repository](https://github.com/AWael8/Laberinto-Maze-Solving-Robot)
