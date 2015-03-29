//============================================================================
// Name        : bbb.cpp
// Author      : Mike Healey
// Version     :
// Copyright   : Copyright (c) 2015 Mike Healey
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "sensors/temperature/temperature_sensor.h"
#include "sensors/temperature/ds18b20.h"

using namespace std;

int main() {
	TemperatureSensor *woodBoiler = new DS18B20("woodBoiler");
	TemperatureSensor *upstairsBoilerFeed = new DS18B20("upstairsBoilerFeed");
	TemperatureSensor *mainfloorBoilerFeed = new DS18B20("mainfloorBoilerFeed");
	TemperatureSensor *hotwaterBoilerFeed = new DS18B20("hotwaterBoilerFeed");
	cout << woodBoiler->getName() << " : " << woodBoiler->getTempInF() << endl;
	cout << upstairsBoilerFeed->getName() << " : " << upstairsBoilerFeed->getTempInF() << endl;
	cout << mainfloorBoilerFeed->getName() << " : " << mainfloorBoilerFeed->getTempInF() << endl;
	cout << hotwaterBoilerFeed->getName() << " : " << hotwaterBoilerFeed->getTempInF() << endl;

	return 0;
}
