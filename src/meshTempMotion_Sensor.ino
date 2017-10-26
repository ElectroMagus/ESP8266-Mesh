
// Mesh Setup
#include "meshSettings.h"
// Declare your topic information for the task and any other variables required

// Declare sensor-specific libraries required
#include <Arduino.h>
#include <Time.h>
#include <Base64.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D3  // DS18B20 pin
#define MOTION_PIN D6 // PIR Motion Sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
int lastRun = 0;
int diff = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Connected to debug port.");

  // Sensor Stuff
  DS18B20.begin();


  pinMode(MOTION_PIN, INPUT);
  attachInterrupt(MOTION_PIN, alertTaskCreate, RISING);


  // Mesh Stuff
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT, STA_AP, AUTH_WPA2_PSK, 6 );
  mesh.onReceive(&receivedCallback);
    // Add the task to the mesh scheduler
    mesh.scheduler.addTask(myLoggingTask);
    myLoggingTask.enable();

};

void loop() { // run over and over
    // Sensor Stuff

    int here = now();
    diff = here - lastRun;
    //Serial.println(diff);
  float temp;
  DS18B20.requestTemperatures();
  temp = DS18B20.getTempCByIndex(0);
  temp = temp * 1.8 + 32;
  topic_value = String(temp);
  mesh.update();
}

void alertTaskCreate() {
  Serial.println("Rising edge");
//  if(diff > 20) {
    // Creates alert to be sent in the scheduler
//    mesh.scheduler.addTask(myAlertingTask);
//    myAlertingTask.enable();
//    lastRun = now();
//    diff = 60;
//  } else {
//  }
}
