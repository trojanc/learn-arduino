#include <Arduino.h>
#include <Wire.h>
#include <UnoWiFiDevEd.h>
#include <DHT.h>

#define PIN_DHT11 5
#define CONNECTOR "mqtt"
#define TOPIC "arduino/dht11"

unsigned long lastupdate = 0;

// DHT connected to pin 5
DHT dht(PIN_DHT11, DHT11);

void setup(void){
	Serial.begin(115200);
	Ciao.begin();
	dht.begin();
}


void loop(void){
	// If we updated 2 seconds ago
	if((millis() - lastupdate) <= 2000){
		lastupdate = millis();
		float temperature = dht.readTemperature();
		Serial.print(F("Temperature: "));Serial.println(temperature);
		Ciao.write(CONNECTOR, TOPIC, String(temperature));
	}
}
