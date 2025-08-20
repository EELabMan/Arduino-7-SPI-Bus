/*
Exploring Arduino - Code Listing 9-2: LED and Speaker Volume SPI Digital Potentiometer Control 
http://www.exploringarduino.com/content/ch9

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Changes LED brightness using voltage input instead of PWM
//Controls speaker volume and tone

//Include SPI library
#include <SPI.h>

const int SPEAKER=8; //Speaker Pin
int freq = 100;

//When using the SPI library, you only have to worry
//about picking your chip selects
//By default, 11 = MOSI, 12 = MISO, 13 = CLK
const int CS1=10; //Chip Select Chip 1
const int CS2=9;  //Chip Select Chip 2

const byte REG0=B00000000; //Register 0 Write command
const byte REG1=B00010000; //Register 1 Write command

void setup()
{
  //Set pin directions for CS
  pinMode(CS1, OUTPUT);
  pinMode(CS2, OUTPUT);
 
  //Initialize SPI
  SPI.begin();
}

//This will set one pot to the specififed level
//Chip 1 (CS 10) Register 0 is Red
//Chip 1 (CS 10) Resiter 1 is Yellow
//Chip 2 (CS 9) Register 0 is Green
//Chip 2 (CS 9) Register 1 is the Speaker
void setReg(int CS, int reg, int level)
{
  digitalWrite(CS, LOW);  //Set the given CS pin low
  SPI.transfer(reg);      //Choose the register to write to
  SPI.transfer(level);    //Set the LED level (0-128)
  digitalWrite(CS, HIGH); //Set the given CS pin high again
}

void loop()
{
  tone(SPEAKER, freq); //set speaker to given frequency
  for (int i=0; i<=128; i++)
  {
    setReg(CS1, REG0, i);
    setReg(CS1, REG1, i);
    setReg(CS2, REG0, i);
    setReg(CS2, REG1, i);
    delay(10);
  }
  delay(300);
  for (int i=128; i>=0; i--)
  {
    setReg(CS1, REG0, i);
    setReg(CS1, REG1, i);
    setReg(CS2, REG0, i);
    setReg(CS2, REG1, i);
    delay(10);
  } 
  delay(300);
  freq = freq+100;
  if (freq > 2000) freq = 100;
  
}

