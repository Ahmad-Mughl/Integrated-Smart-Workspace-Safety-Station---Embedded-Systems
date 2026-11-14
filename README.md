# Integrated-Smart-Workspace-Safety-Station---Embedded-Systems
📌 Project Overview

The Integrated Smart Workspace Safety Station is an embedded systems project developed using C++ in the Energia IDE. The system monitors environmental conditions in a workspace using an OPT3001 ambient light sensor and a TMP006 temperature sensor.

The station continuously measures light intensity and temperature, evaluates the readings against predefined safety thresholds, and classifies the workspace into three operating zones: SAFE, CAUTION, and DANGER.

A built-in RGB LED provides visual status indication, while a buzzer generates audible alerts when unsafe environmental conditions are detected. The system also includes a maintenance mode to temporarily disable safety alerts and a reset button to clear latched danger alarms.

The project demonstrates practical applications of embedded systems, I2C communication, sensor interfacing, conditional logic, digital input/output, and real-time monitoring.

🎯 Project Objectives

Monitor workspace temperature and ambient light intensity.

Interface OPT3001 and TMP006 sensors using I2C communication.

Establish predefined environmental safety thresholds.

Classify workspace conditions into SAFE, CAUTION, and DANGER zones.

Provide visual alerts using an RGB LED.

Generate audible warnings using a buzzer.

Implement a maintenance mode for servicing operations.

Implement alarm latching and manual reset functionality.

Display real-time sensor readings and system status through Serial Monitor.

✨ Key Features

Real-Time Environmental Monitoring: Continuously measures ambient light and temperature.

Three-Level Safety Classification: Identifies SAFE, CAUTION, and DANGER conditions.

RGB LED Indication: Displays the current safety status through different LED colors.

Audible Alarm System: Generates different buzzer tones depending on the detected safety zone.

Latched Danger Alarm: Maintains the danger alarm state until manually reset.

Maintenance Mode: Temporarily disables normal safety indications and buzzer alerts.

Manual Alarm Reset: Allows the user to clear the latched alarm using a push button.

Serial Monitoring: Displays temperature, light intensity, operating mode, and safety zone.

🛠️ Hardware Requirements

Component

Purpose

TI LaunchPad Development Board

Main microcontroller platform

OPT3001 Light Sensor

Measures ambient light intensity

TMP006 Temperature Sensor

Measures temperature

RGB LED

Provides visual safety indications

Buzzer

Generates audible warnings

PUSH1 Button (S1)

Resets the latched alarm

Push Button (S2)

Toggles maintenance mode

Connecting Wires

Hardware interfacing

💻 Software Requirements

Energia IDE

C++ / Arduino-style programming

Wire Library for I2C communication

Serial Monitor for real-time monitoring

⚙️ System Architecture

The system consists of five major functional blocks:

Environmental Sensing

Data Acquisition and Processing

Safety Classification

Visual and Audible Feedback

User Control Interface

1. Environmental Sensing

Two sensors are used to monitor workspace conditions.

OPT3001 Ambient Light Sensor

Measures surrounding light intensity.

Communicates with the microcontroller through I2C.

Provides measurements in lux.

Helps identify insufficient lighting conditions.

TMP006 Temperature Sensor

Measures environmental temperature.

Communicates with the microcontroller through I2C.

Provides temperature readings for safety assessment.

Helps identify elevated temperature conditions.

2. Data Acquisition and Processing

The microcontroller retrieves sensor measurements through the I2C interface.

The OPT3001 reading is converted into lux using its exponent and mantissa values, while the TMP006 reading is processed to calculate temperature.

The acquired measurements are then compared against predefined safety thresholds.

3. Safety Classification

The system classifies workspace conditions into three safety zones.

Safety Zone

Light Intensity

Temperature

DANGER

Below 50 lux

Above 35°C

CAUTION

Below 200 lux

Above 30°C

SAFE

Within acceptable thresholds

Within acceptable thresholds

Classification Logic:

DANGER: Activated when light intensity falls below 50 lux OR temperature exceeds 35°C.

CAUTION: Activated when light intensity falls below 200 lux OR temperature exceeds 30°C, provided no danger condition exists.

SAFE: Activated when neither danger nor caution conditions are detected.

4. Visual and Audible Feedback

The system provides immediate feedback according to the detected safety zone.

Operating Zone

LED Indication

Buzzer

SAFE

Green LED

OFF

CAUTION

Blue LED

1000 Hz tone for 100 ms

DANGER

Blinking Red LED

Continuous 2500 Hz tone

The red LED blinks at approximately 250 ms intervals during danger conditions.

5. User Control Interface

Two push buttons provide user interaction.

S1 – Alarm Reset

Clears the latched danger alarm.

Prints an alarm reset message on the Serial Monitor.

S2 – Maintenance Mode

Toggles maintenance mode ON or OFF.

Turns all three RGB LED channels ON.

Disables the buzzer while maintenance mode is active.

Returns the system to normal safety operation when disabled.

📊 Safety Thresholds

The following thresholds are defined in the source code:

Parameter

Threshold

Purpose

Danger Light Level

50 lux

Detects critically low lighting

Caution Light Level

200 lux

Detects insufficient lighting

Danger Temperature

35°C

Detects high temperature

Caution Temperature

30°C

Detects elevated temperature

These values are configurable through the threshold constants in the program.

🔌 Hardware Pin Configuration

Hardware Component

Microcontroller Pin

Red LED

RED_LED

Green LED

GREEN_LED

Blue LED

BLUE_LED

Buzzer

Pin 40

S1 Reset Button

PUSH1

S2 Maintenance Button

Pin 2

OPT3001

I2C

TMP006

I2C

I2C Device Addresses

Sensor

I2C Address

OPT3001

0x44

TMP006

0x40

🧠 Embedded Systems Concepts Used

Concept

Implementation

I2C Communication

Communication with OPT3001 and TMP006

Sensor Interfacing

Environmental data acquisition

Digital Input

Push-button control

Digital Output

RGB LED control

PWM/Tone Generation

Buzzer alerts using tone()

Conditional Statements

Safety zone classification

Boolean Variables

Maintenance and alarm states

Functions

Modular sensor and feedback operations

Serial Communication

Real-time system monitoring

Timing Functions

Delays and LED blinking using millis()

🔄 Working Principle

System Initialization: The microcontroller initializes Serial communication, I2C communication, GPIO pins, and both environmental sensors.

Sensor Acquisition: The OPT3001 measures ambient light intensity, while the TMP006 measures temperature.

Threshold Comparison: The measured values are compared against predefined danger and caution thresholds.

Safety Classification: The system determines whether the workspace is in SAFE, CAUTION, or DANGER mode.

Feedback Generation: The RGB LED and buzzer provide visual and audible indications according to the detected zone.

Alarm Latching: When a danger condition occurs, the alarm state is latched until the user presses S1.

Maintenance Operation: Pressing S2 toggles maintenance mode, temporarily disabling normal alarm feedback.

Serial Monitoring: The current operating mode, temperature, light intensity, and safety zone are continuously displayed.

🖥️ Serial Monitor Output

The system displays real-time environmental readings and operating status.
