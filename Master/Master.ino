/*
Communication from Arduino UNO master and Arduino UNO slave...
This program use I2C communication between 2 Arduino UNO
Original project --> https://www.youtube.com/watch?v=znREIPzi854
A4 slave --> A4 Master
A5 slave --> A5 Master

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

// Master I2C
#include <Wire.h>
#define I2C_ADDR 0x78

union databuff{
float tc[5]; // use an array of 5 float
uint8_t buff[20]; // the size of 1 float is 4 ... so 5 * 4 = 20
} dati;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(2000);
  Serial.println("Master");
}

void loop() {
  // Send command
  Wire.beginTransmission(0x78);
  Wire.write(0x01); // only if slave accepts command
  Wire.endTransmission();

  // Receive response
int nb = Wire.requestFrom(I2C_ADDR, 20 /*how many byte i need from slave*/);
if(nb == 20) {
  int i = 0;
  while (Wire.available()){
  char c = Wire.read();
  dati.buff[i] = (uint8_t)c;
  i++;
    }
  }
  Serial.println(dati.tc[0]);
  delay(3000);
}
