/*
   LoRaLib Transmit Example

   This example transmits LoRa packets with one second delays
   between them. Each packet contains up to 256 bytes
   of data, in the form of:
    - Arduino String
    - null-terminated char array (C-string)
    - arbitrary binary data (byte array)

   For more detailed information, see the LoRaLib Wiki
   https://github.com/jgromes/LoRaLib/wiki

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/LoRaLib/
*/

// include the library
#include <LoRaLib.h>

// create instance of LoRa class using SX1278 module
// this pinout corresponds to RadioShield
// https://github.com/jgromes/RadioShield
// NSS pin:   10 (4 on ESP32/ESP8266 boards)
// DIO0 pin:  2
// DIO1 pin:  3
SX1278 lora = new LoRa;

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

void setup() {
  Serial.begin(9600);

  // initialize SX1278 with default settings
  //Serial.print(F("Initializing ... "));
  
  int state = lora.begin();
  if (state == ERR_NONE) {
    //Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
  emon1.voltage(A0, 660, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(A1, 11);       // Current: input pin, calibration.

}

void loop() {
  //Serial.print("Sending packet ... ");
  emon1.calcVI(1,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  
  float powerFactor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  
  Serial.print("Vrms: ");
  Serial.println(supplyVoltage);
  Serial.print("Irms: ");
  Serial.println(Irms);
  Serial.print("pf: ");
  Serial.println(powerFactor);
  Serial.print("P: ");
  Serial.println(realPower);
  Serial.print("Q: ");
  Serial.println(apparentPower);
  Serial.println();
  
  String V=String(supplyVoltage);
  String I=String(Irms);
  String P=String(realPower);
  String S=String(apparentPower);
  String pf=String(powerFactor);

  int state00 = lora.transmit("V: ");
    int state01 = lora.transmit(V);
  int state10 = lora.transmit("I: ");
    int state11 = lora.transmit(I);
  int state20 = lora.transmit("pf: ");
    int state21 = lora.transmit(pf); 
  int state30 = lora.transmit("P: ");
    int state31 = lora.transmit(P); 
  int state50 = lora.transmit("S: ");
    int state51 = lora.transmit(S);

  if (state00 == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(" success!");

  delay(2500);
}
}
