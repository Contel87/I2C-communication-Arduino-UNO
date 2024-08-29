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


// Slave I2C
#include <Wire.h>
#define I2C_ADDR 0x78

int reg;
unsigned long t1;

union databuff{
float tc[5]; // use an array of 5 float
uint8_t buff[20]; // the size of 1 float is 4 ... so 5 * 4 = 20
} dati;


void setup() {
  Wire.begin(I2C_ADDR);
  Wire.onReceive(riceviDati);
  Wire.onRequest(inviaDati);
  Serial.begin(115200);
  delay(2000);
  Serial.println("Slave");

}

void loop() {
if( (millis() - t1) > 5000 ){
for (int i=0; i<5/*5 float*/;i++){
  Serial.print("Sonda: ");Serial.print(i);
dati.tc[i] = 20.5f; // valore da trasmettere
Serial.print(" C ");Serial.println(dati.tc[i]);
}
t1 = millis();
}

}

void riceviDati(int n){
reg = (uint8_t)Wire.read();
}

void inviaDati(){
 for(int i = 0; i < 20/*buff*/; i++){
  Wire.write((int)dati.buff[i]); // int compatibile R3 R4???? (buff non vuole un byte???)
 }
}
