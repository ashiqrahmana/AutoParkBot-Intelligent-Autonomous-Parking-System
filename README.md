# AutoParkBot-Intelligent-Autonomous-Parking-System
## Project Objective
To design and build a bot that can autonomously detect parking spaces and park itself. It was also designed to detect if the vehicle present in the parking space is a 2-wheeleer or a 4-wheeler  

![Project Arena Pic.](https://github.com/ashiqrahmana/AutoParkBot-Intelligent-Autonomous-Parking-System/blob/main/Images/Adv%20Mech%20Project%201%20arena.png)

## System Architecture
The bot has Arduino as the primary microcontroller. It takes in the sensor data and control the servos for the bot movement  

## Onboard Sensors
| Sensor | Type | Function | 
| ------ | ---- | -------- |
| QTI | IR | Line Following |
| HC-SR04 | Ultrasonic | Obstacle and vehicle detection |

## Circuit
To design and build a bot that can autonomously detect parking spaces and park itself. It was also designed to detect if the vehicle present in the parking space is a 2-wheeler or a 4-wheeler  

## Approach
### Callibration
Callibration of the sensors were done as the initial step. They had to be callibrated by the user in the following steps:
1. Place the sensor on a white surface and click the confirmation push button on the bot
2. Repeat the same procedure after placing the bot ona  black surface or line
For additional information refer this repo : <link>  

### Control and Data Processing
After callibration, the bot the starts moving followign the line and takign appropriate decisions at the intersection. Since the arena is in a cyclic so the mod logic is used to detrmine what action needs to taken at the partivcular intersection. The actions include:  
1. Taking left turn
2. Taking right turn 
3. Taking Uturn

The bot after parking displays the number of cars and bikes detected using three LEDs in binary format.

## Folder Structure 

## Assembled Bot 

## Final Result Visualised 

