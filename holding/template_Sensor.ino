
// Mesh Setup
#include "meshSettings.h"
// Declare your topic information for the task and any other variables required
String location;
String topic_name = "temperature";
String topic_value;

// Declare sensor-specific libraries required


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
  mesh.update();


}
