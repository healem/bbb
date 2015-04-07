//============================================================================
// Name        : bbb.cpp
// Author      : Mike Healey
// Version     :
// Copyright   : Copyright (c) 2015 Mike Healey
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "sensors/temperature/temperature_sensor_manager.h"

using namespace std;

int main() {
	TemperatureSensorManager *tsm = new TemperatureSensorManager();
	tsm->discoverSensors();
	std::vector<std::string> sensors = tsm->getAllSensors();
	std::vector<std::string>::iterator sensorIt;
	for(sensorIt = sensors.begin(); sensorIt != sensors.end(); ++sensorIt)
	{
		cout << *sensorIt << " : " << tsm->getTempInF(*sensorIt) << endl;
	}

	return 0;
}
