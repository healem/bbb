/*
 * ds18b20.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: healem
 */
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "ds18b20.h"
#include "../../common/logger.h"

DS18B20::DS18B20(const std::string& name) {
	mName = name;
	mFile = "w1_slave";
	mBaseDir = "/etc/bbb/dev/temp/";
	mSensorPath = mBaseDir + mName + "/" + mFile;
}

DS18B20::~DS18B20() {
	// TODO Auto-generated destructor stub
}

std::string DS18B20::getName(){
	return mName;
}

int DS18B20::getTempInC(){
	int rawTemp = DS18B20::getTempRaw();
	int tempInC = rawTemp / 1000;

	// If temp is 0, the fetch is likely invalid - try again
	if(tempInC == 0)
	{
		WARN("Returned temp is 0, likely had issue - retrying");
		rawTemp = DS18B20::getTempRaw();
		tempInC = rawTemp / 1000;
	}

	return tempInC;
}

int DS18B20::getTempInF(){
	int tempInC = DS18B20::getTempInC();
	int tempInF = tempInC * 9 / 5 + 32;
	INFO("Temp in C: %d, Temp in F: %d", tempInC, tempInF);
	return tempInF;
}

int DS18B20::getTempRaw(){
	std::ifstream sensorOutput(mSensorPath.c_str());
	int rawTemp = 0;
	if(sensorOutput.is_open())
	{
		if(! sensorOutput.eof())
		{
	        // First line of sensor output contains crc result
			// Second line of sensor output contains temp
	        std::string crcLine;
	        std::string tempLine;
	        std::getline(sensorOutput, crcLine);
	        std::getline(sensorOutput, tempLine);

	        std::string crcText = DS18B20::getValueFromLine(crcLine);
	        DEBUG("Raw temp crc: %s", crcLine.c_str());
	        std::string tempText = DS18B20::getValueFromLine(tempLine);
	        DEBUG("Raw temp text: %s", tempLine.c_str());
	        if(isCrcValid(crcText))
	        {
	        	sscanf(tempText.c_str(), "%d", &rawTemp);
	        	DEBUG("Temp text: %s, Temp int: %d", tempText.c_str(), rawTemp);
	        }
		}
	}
	return rawTemp;
}

std::string DS18B20::getValueFromLine(std::string line)
{
	std::string delimiter = "=";

	//we only care about what's after the delimiter
	size_t position = 0;
	std::string value;
	position = line.find(delimiter);
	value = line.substr(position + delimiter.length(), std::string::npos);

	return value;
}

bool DS18B20::isCrcValid(std::string crcValue)
{
	std::string validString = "YES";
	bool isValid;
	if(crcValue.find(validString) < std::string::npos)
	{
		isValid = true;
	}
	else
	{
		isValid = false;
	}

	return isValid;
}
