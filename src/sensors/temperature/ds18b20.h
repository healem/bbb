/*
 * ds18b20.h
 *
 *  Created on: Feb 9, 2015
 *      Author: healem
 */

#ifndef DS18B20_H_
#define DS18B20_H_

#include "temperature_sensor.h"

class DS18B20: public TemperatureSensor {
private:
	std::string mName;
	std::string mSensorPath;
	std::string getValueFromLine(std::string line);
	bool isCrcValid(std::string crcValue);
public:
	DS18B20(const std::string& name, const std::string& path);
	virtual ~DS18B20();
	virtual std::string getName();
	virtual int getTempInC();
	virtual int getTempInF();
	virtual int getTempRaw();
};

#endif /* DS18B20_H_ */
