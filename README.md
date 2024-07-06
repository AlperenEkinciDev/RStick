**Alperen Ekinci,<br />
2024 Hacettepe University Term Project I,<br />
RStick Project, Prototyping and Showcasing By Developing The Game S.T.R.I.D.E.R**

Summary
============
In a gaming landscape dominated by traditional control devices such as keyboards, mice and gamepads, a new cost-effective method to elevate player immersion is needed. This project intends to design and implement a handheld device called R-Stick, a motion and key-press controlled Bluetooth device.<br />

Project Demonstration: https://www.youtube.com/watch?v=9k_XwhJBLDw

This repository aims to document this project.<br />

Details
============

* **RStick - Component Selection**<br />
Using off the shelf products such as HC-05 Bluetooth Module, ADXL345 Accelerometer and cheap 3D printed parts, greatly reduces the cost of this prototype.But in a future where this becomes a consumer product its cost can be reduced by creating custom PCBs and cheaper casing;<br />
  	- 1x Arduino Nano<br />
	- 1x Bluetooth Module -> HC05(Has both Slave/Master) for future on-device feedback capability<br />
	- 2x Accelerometer -> ADXL345<br />
	- 6x Small buttons. For thumb, 1 action and 1 calibration buttons, 4 for remaining fingers<br />
	- 1x 9V Battery<br />
	- 1 Breadboard, to connect everything together<br />
	- Connector cables<br />

* **RStick - Body 3D Design/Print/Assembly**<br />
	- 3D Printed connectors, component holders, protective casing and handle are modelled using Blender.<br />
	- Then these models are printed using Creality Ender-3 v2 3D printer using PLA as the material.<br />

* **RStick - Driver Code**<br />
	- The two ADXL345 accelerometer modules are simultaneously connected in I2C mode using "Wire" Arduino library.<br />
	- The HC-05 Bluetooth module is connected using "SoftwareSerial" Arduino library. Communicates with one of computers COM serials.
	- ["RStick_accCombined.ino"](Rstick/RStick_accCombined/RStick_accCombined.ino) includes methods for both the accelerometers and the Bluetooth module.<br />

* **S.T.R.I.D.E.R - Digital game made for showcase purposes.** (Also playable with keyboard - mouse)<br />
	- Programs such as Unity Game Engine, Blender, Substance Painter etc. are used for the development and [design](https://www.artstation.com/artwork/5vrDAJ).<br />
	- For Unity to establish communication with the COM ports [Dwilches's "Ardity"](https://github.com/dwilches/Ardity) library is used.<br />
	- Test [build](S.T.R.I.D.E.R/BUILD) is included in this repository.<br />
