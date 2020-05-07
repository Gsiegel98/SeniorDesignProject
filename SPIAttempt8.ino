#include <SPI.h>

// pin 13: SCK aka CLK, pin 12: MISO, pin 11: MOSI, pin 10: SS
// Links for help: https://www.arduino.cc/en/reference/SPI
// https://arduino.stackexchange.com/questions/16348/how-do-you-use-spi-on-an-arduino
// I believe that the DAC should use MSB when sending data

// set pin 10 as the slave select for the digital pot:
// const int slaveSelectPin = 10;

// We used DDRB and PORTB to make the code more efficient and run faster
// As opposed to pinMode() and digitalWrite()

void setup(void) {
  
  // put your setup code here, to run once:
  // pinMode(10, OUTPUT);  // set the slaveSelectPin as an output
  DDRB = DDRB | B000100; //sets pin 10 as output without affecting others
  //digitalWrite(slaveSelectPin, HIGH);  // ensure SS stays high for now
  // "Slave Select (SS) goes low to assert it."
  SPI.begin ();           // Initialize the SPI
  
} //end of setup


void loop() {
  int greaterMax = 225; //max for greater 8 bits
  int greaterMax1 = 224;
  int lesserMax = 256;  //max for lesser 8 bits
  int lesserMax1 = 255;
  for(int i = 0; i < greaterMax; i++) {    // Go up
    for(int j = 0; j < lesserMax; j+=2) {
      SPI.beginTransaction (SPISettings (16000000, MSBFIRST, SPI_MODE0));  // 16 MHz clock, MSB first, mode 0
      //digitalWrite(slaveSelectPin, LOW);    // take the SS pin low to select the chip
      PORTB = PORTB & B101000; // Designed to set pin 10 LOW, without affecting pin 13 or 10
      SPI.transfer(i);                  //  send in the value via SPI
      SPI.transfer(j);                  //  send in the value via SPI
      //digitalWrite(slaveSelectPin, HIGH);   // take the SS pin high to de-select the chip
      PORTB = PORTB | B000100; // Designed to set pin 10 HIGH, without affecting pin 13 or 10
      SPI.endTransaction ();                // transaction over
    }
  }
  for(int i = 0; i < greaterMax; i++) {    // Stay Up
    for(int j = 0; j < lesserMax; j+=2) {
      SPI.beginTransaction (SPISettings (16000000, MSBFIRST, SPI_MODE0));  // 16 MHz clock, MSB first, mode 0
      PORTB = PORTB & B101000;  // take the SS pin low to select the chip
      SPI.transfer(greaterMax);            //  send in the value via SPI
      SPI.transfer(lesserMax1);            //  send in the value via SPI
      PORTB = PORTB | B000100;  // take the SS pin high to de-select the chip
      SPI.endTransaction ();               // transaction over
    }
  }
  for(int i = 0; i < greaterMax; i++) {    // Go Down
    for(int j = 0; j < lesserMax; j+=2) { 
      SPI.beginTransaction (SPISettings (16000000, MSBFIRST, SPI_MODE0));  // 16 MHz clock, MSB first, mode 0
      PORTB = PORTB & B101000;  // take the SS pin low to select the chip
      SPI.transfer(greaterMax1-i);        //  send in the value via SPI
      SPI.transfer(lesserMax1-j);         //  send in the value via SPI
      PORTB = PORTB | B000100;   // take the SS pin high to de-select the chip
      SPI.endTransaction ();              // transaction over
    }
  }
  for(int i = 0; i < greaterMax; i++) {  // Stay Down
    for(int j = 0; j < lesserMax; j+=2) {
      SPI.beginTransaction (SPISettings (16000000, MSBFIRST, SPI_MODE0));  // 16 MHz clock, MSB first, mode 0
      PORTB = PORTB & B101000;    // take the SS pin low to select the chip
      SPI.transfer(0);                  //  send in the value via SPI
      SPI.transfer(0);                  //  send in the value via SPI
      PORTB = PORTB | B000100; // take the SS pin high to de-select the chip
      SPI.endTransaction ();                // transaction over
    }
  }
}




