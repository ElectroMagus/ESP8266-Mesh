# ESP8266-Mesh
Creating a prototype sensor network using painlessMesh library.  A serial bridge to a RPi 3 is collecting all the Mesh debug data and sensor reports to a text file for analysis.

Current status:
3 different sensors configured as logClients and 1 logServer connected to a RPi via serial.  The RPi dumps everything to a text file.

It appears to be working pretty well in early testing.

Look in RPi for detailed debugging from the Mesh library.  One particular sensor (which provided GPS data) seemed to have a really hard time staying connected to the mesh.

ToDo:
* Update RPi logging script to split messages out into appropriate logfiles (Mesh, Sensor Data, etc).
* Write a handler to log Sensor Data in DB 
* Write a handler for Sensor Data to pass off to MQTT broker
  - Rate-Limit 
....
