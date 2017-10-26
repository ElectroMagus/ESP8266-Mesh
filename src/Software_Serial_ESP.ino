#include <TinyGPS++.h>
#include <SoftwareSerial.h>

String location;

static const int RXPin = 12, TXPin = 14;
static const uint32_t GPSBaud = 9600;
SoftwareSerial ss(RXPin, TXPin);
TinyGPSPlus gps;


String displayInfo()  {
  while (ss.available() > 0)
    gps.encode(ss.read());
    location = String(gps.location.lat(), 6) + " " + String(gps.location.lng(), 6) + " " + String(gps.altitude.meters()) + " " + String(gps.speed.mph());
  return location;
};


// Mesh Stuff
#include "painlessMesh.h"
#define   MESH_PREFIX     "MPan"
#define   MESH_PASSWORD   "d0ntp33k"
#define   MESH_PORT       6767
painlessMesh  mesh;

size_t logServerId = 0;

// Send message to the logServer every 10 seconds
Task myLoggingTask(10000, TASK_FOREVER, []() {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& msg = jsonBuffer.createObject();
    msg["topic"] = "location";
    msg["value"] = location;

    String str;
    msg.printTo(str);
    if (logServerId == 0) // If we don't know the logServer yet
        mesh.sendBroadcast(str);
    else
        mesh.sendSingle(logServerId, str);

    // log to serial
    msg.printTo(Serial);
    Serial.printf("\n");
});

// End Mesh Stuff



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
  location = displayInfo();

  // This sketch displays information every time a new sentence is correctly encoded.
  /*
   while (ss.available() > 0)
     if (gps.encode(ss.read())) {
       displayInfo();
     };
   if (millis() > 5000 && gps.charsProcessed() < 10)
   {
     Serial.println(F("No GPS detected: check wiring."));
     while(true);
   };
*/
};

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("logClient: Received from %u msg=%s\n", from, msg.c_str());

  // Saving logServer
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(msg);
  if (root.containsKey("topic")) {
      if (String("logServer").equals(root["topic"].as<String>())) {
          // check for on: true or false
          logServerId = root["nodeId"];
          Serial.printf("logServer detected!!!\n");
      }
      Serial.printf("Handled from %u msg=%s\n", from, msg.c_str());
  }
}
