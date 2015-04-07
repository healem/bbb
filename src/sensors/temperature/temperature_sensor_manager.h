/*
 * TemperatureSensorManager.h
 *
 *  Created on: Apr 6, 2015
 *      Author: healem
 */

#ifndef TEMPERATURESENSORMANAGER_H_
#define TEMPERATURESENSORMANAGER_H_

#include "temperature_sensor.h"
#include <map>
#include <vector>

class TemperatureSensorManager {
private:
	std::map<std::string, TemperatureSensor *> mTempSensors;
	std::map<std::string, TemperatureSensor *>::iterator mTempSensorIt;
	std::string ds18b20BaseDir;
	std::string ds18b20File;
public:
	TemperatureSensorManager();
	virtual ~TemperatureSensorManager();
	void discoverSensors();
	int getTempInC(std::string id);
	int getTempInF(std::string id);
	std::vector<std::string> getAllSensors();
};

#endif /* TEMPERATURESENSORMANAGER_H_ */
