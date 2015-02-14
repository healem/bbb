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
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	TemperatureSensor *ds = new DS18B20("test");
	cout << "Sensor name:" << ds->getName() << endl;

	return 0;
}
