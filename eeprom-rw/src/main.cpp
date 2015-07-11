#include <Arduino.h>
#include <EEPROM.h>

/**
 * This function will print the first 10 bytes of what is currently stored in the EEPROM
 * starting from byte 0
 */
void print10Bytes(){
	Serial.println("Current first 10 bytes in EEPROM");
	// Loop for 10 bytes (0-9)
	for(int i = 0 ; i < 10 ; i++){
		// read a byte from the current address of the EEPROM
		byte value = EEPROM.read(i);

		// Print the value as a char
		Serial.print((char)value);
	}
	// Just print out a new line to get the the next line
	Serial.println();
}

/**
 * This function will prompt the user to enter 10 characters, which will
 * then be stored in the EEPROM
 */
void write10Bytes(){

	Serial.println("Enter 10 characters you would like to store");

	int bytesRead = 0; // Number of bytes we have read

	// Loop for 10 bytes (0-9)
	while(bytesRead < 10){
		/*
		 * Check if something has been entered yet.
		 * If nothing was entered, the above for loop will just continue looping
		 * and checking this if statement untill you type something
		 */
		if(Serial.available()){
			// Read the next byte from the serial port
			byte b = Serial.read();

			// Print back on the serial what you just entered to get some feedback
			Serial.print((char)b);

			/*
			 * Write the byte you just entered into eeprom
			 * and increment the number of bytes that we have read
			 */

			EEPROM.write(bytesRead++, b);
		}
	}
	Serial.println(); // Create new line after input
	Serial.println("Done Reading");
}

/**
 * Setup for this app
 */
void setup(){
  // initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

}


/**
 * Forever loop to print the current 10 bytes in eeprom, and prompt to enter new values.
 */
void loop(){
	print10Bytes();
	write10Bytes();
}
