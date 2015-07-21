/**
 * Author: Charl Thiem
 * Created: 2015-07-21
 * Description: This program searches a onewire bus for devices.
 *
 * Credit:
 * I give credit to the following references who inspired this program
 * http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
 */
//
#include <Arduino.h>
#include <OneWire.h>

// The digital port to which your one wire devices are connected
OneWire  ds(7);  // Connect your 1-wire device to pin 3


/**
 * This function does the actual work of finding the devices
 */
void discoverOneWireDevices(void) {
	byte i;
	byte present = 0;
	byte data[12];
	byte addr[8];

	Serial.print("Looking for 1-Wire devices...\n\r");
	while(ds.search(addr)) {
		Serial.print("\n\rFound \'1-Wire\' device with address:\n\r");
		for( i = 0; i < 8; i++) {
			Serial.print("0x");
			if (addr[i] < 16) {
				Serial.print('0');
			}
			Serial.print(addr[i], HEX);
			if (i < 7) {
				Serial.print(", ");
			}
		}
		if ( OneWire::crc8( addr, 7) != addr[7]) {
			Serial.print("CRC is not valid!\n");
			return;
		}
	}
	Serial.print("\n\r\n\rThat's it.\r\n");
	ds.reset_search();
	return;
}

/**
 * Setup the program for execution
 */
void setup(void) {
	Serial.begin(115200);

	// Since we don't want to do this in a loop, we can do it once at the setup
	discoverOneWireDevices();
}


void loop(void) {
	// We won't be doing anthing in the loop
}


