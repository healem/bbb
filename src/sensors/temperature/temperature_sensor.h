/*
 * temperature_sensor.h
 *
 * Interface to Temperature sensor implementations
 *
 *  Created on: Feb 9, 2015
 *      Author: healem
 */

#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_

#include <string>

class TemperatureSensor {
public:
	virtual ~TemperatureSensor() = 0;
	virtual std::string getName() = 0;
	virtual int getTempInC() = 0;
	virtual int getTempInF() = 0;
	virtual int getTempRaw() = 0;
protected:
	TemperatureSensor();
};

#endif /* TEMPERATURESNESOR_H_ */
