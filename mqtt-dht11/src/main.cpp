#include <Arduino.h>
#include <Wire.h>
#include <UnoWiFiDevEd.h>
#include <DHT.h>

#define CONNECTOR "mqtt"
// MQTT topic on which we will publish
#define TOPIC "trojanc/learn-arduino/mqtt-dht11"

// Last millis that we sent an update
unsigned long lastupdate = 0;

// DHT connected to pin 5
DHT dht(5, DHT11);

void setup(void){
	Serial.begin(115200);
	Serial.println(F("TrojanC - Learn Arduino:: mqtt-dht11"));
	Ciao.begin();
	dht.begin();
}


void loop(void){
	// If we updated 2 seconds ago
	if(((unsigned long)(millis() - lastupdate)) >= 2000){
		lastupdate = millis();
		float temperature = dht.readTemperature();
		Serial.print(F("Temperature: "));Serial.println(temperature);
		Ciao.write(CONNECTOR, TOPIC, String(temperature));
	}
}
