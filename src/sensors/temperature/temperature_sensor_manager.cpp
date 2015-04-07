/*
 * TemperatureSensorManager.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: healem
 */

#include "temperature_sensor_manager.h"
#include <dirent.h>
#include "ds18b20.h"

TemperatureSensorManager::TemperatureSensorManager() {
	std::map<std::string, TemperatureSensor*> mTempSensors;
	std::map<std::string, TemperatureSensor*>::iterator mTempSensorIt;
	ds18b20BaseDir = "/etc/bbb/dev/temp/";
	ds18b20File = "w1_slave";
}

TemperatureSensorManager::~TemperatureSensorManager() {

	for(mTempSensorIt = mTempSensors.begin(); mTempSensorIt != mTempSensors.end(); ++mTempSensorIt)
	{
		delete mTempSensorIt->second;
	}
}

void TemperatureSensorManager::discoverSensors()
{
	DIR *dirp = opendir(ds18b20BaseDir.c_str());
	dirent *dp;
	while((dp = readdir(dirp)) != NULL)
	{
		std::string name(dp->d_name);
		std::string path = ds18b20BaseDir + name + "/" + ds18b20File;
		// Remove "." and ".." from directory listing
		if(name != "." && name != "..")
		{
		    mTempSensors.insert(std::pair<std::string, TemperatureSensor *>(name, new DS18B20(name, path)));
		}
	}
	closedir(dirp);
}

int TemperatureSensorManager::getTempInC(std::string id)
{
	return mTempSensors[id]->getTempInC();
}

int TemperatureSensorManager::getTempInF(std::string id)
{
	return mTempSensors[id]->getTempInF();
}

std::vector<std::string> TemperatureSensorManager::getAllSensors()
{
	std::vector<std::string> sensors;
	for(mTempSensorIt = mTempSensors.begin(); mTempSensorIt != mTempSensors.end(); ++mTempSensorIt)
	{
		sensors.push_back(mTempSensorIt->second->getName());
	}

	return sensors;
}

