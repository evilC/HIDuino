# HIDuino
Experiments with Arduino based HID manipulation  
To allow controlling of HID devices programmatically from a Windows PC  
Initially, the goal is to allow driving of HID Joysticks on Windows without the need for custom device drivers such as [vJoy](https://sourceforge.net/projects/vjoystick/)  
As a stretch goal, a [USB Host Shield](https://github.com/felis/USB_Host_Shield_2.0) could be used to allow the user to plug devices into the Arduino, which are then read via serial by code on the PC (Without Windows seeing them as HID devices), 
and then sending (mutated) data back to the Ardiuno, which then sends it back to the PC as HID input data (Sort of like what [Interception](https://github.com/oblitum/Interception) does for keyboard and mouse)  

If / when this code becomes useful, I would be looking to implement it as a Provider for [UCR](https://github.com/Snoothy/UCR), to allow end-users to consume it via a GUI application
