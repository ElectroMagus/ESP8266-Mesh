
// Mesh Setup
#include "meshSettings.h"
// Declare your topic information for the task and any other variables required
String location;
String topic_name = "location";
String topic_value;

// Declare sensor-specific libraries required
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
    // GPS Setup
      static const int RXPin = 12, TXPin = 14;
      static const uint32_t GPSBaud = 9600;
      SoftwareSerial ss(RXPin, TXPin);
      TinyGPSPlus gps;

    // Function that outputs the most recent poll in:  LAT LONG HEIGHT(M) SPEED(MPH)
      String displayInfo()  {
        while (ss.available() > 0)
        gps.encode(ss.read());
        location = String(gps.location.lat(), 6) + " " + String(gps.location.lng(), 6) + " " + String(gps.altitude.meters()) + " " + String(gps.speed.mph());
      return location;
};


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Connected to debug port.");



  // Mesh Stuff
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT, STA_AP, AUTH_WPA2_PSK, 6 );
  mesh.onReceive(&receivedCallback);
    // Add the task to the mesh scheduler
    mesh.scheduler.addTask(myLoggingTask);
    myLoggingTask.enable();

};

void loop() { // run over and over
  location = displayInfo();
  topic_value = location;
  mesh.update();


}
