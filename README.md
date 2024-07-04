//Alperen Ekinci, 2024 Hacettepe University Term Project I, RStick Project, Prototyping and Showcasing By Developing The Game S.T.R.I.D.E.R//

In a gaming landscape dominated by traditional control devices such as keyboards, mice and gamepads, a new cost-effective method to elevate player immersion is needed. This project intends to design and implement a handheld device called R-Stick, a motion and key-press controlled Bluetooth device.<br />

This repository aims to document this project.<br />

* **RStick - Component Selection**<br />
Using off the shelf products such as HC-05 Bluetooth Module, ADXL345 Accelerometer and cheap 3D printed parts, greatly reduces the cost of this prototype.But in a future where this becomes a consumer product its cost can be reduced by creating custom PCBs and cheaper casing;<br />
  	-1x Arduino Nano<br />
	-1x Bluetooth Module -> HC05(Has both Slave/Master) for future on-device feedback capability<br />
	-2x Accelerometer -> ADXL345<br />
	-6x Small buttons, one for thumb action one for calibration and 4 for remaining fingers<br />
	-1x 9V Battery<br />
	-1 Breadboard, to connect everything together<br />
	-Connector cables<br />

* **RStick - Body 3D Design/Print/Assembly**<br />
	-3D Printed connectors, component holders, protective casing and handle are modelled using Blender.<br />
	-Then these models are printed Using Creality Ender-3 v2 3D printer using PLA as the material.<br />

* **RStick - Driver Code**<br />
	-"RStick_accCombined.ino" includes both the accelerometers and the Bluetooth module.<br />
	-The two ADXL345 accelerometer modules are simultaneously connected in I2C mode using "Wire" C library.<br />
	-The HC-05 Bluetooth module is connected using "SoftwareSerial" C library. Sent to the computers COM serial.

* **S.T.R.I.D.E.R - Showcase digital game made using Unity Game Engine** (Also playable with keyboard - mouse)<br />
