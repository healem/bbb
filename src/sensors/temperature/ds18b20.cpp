/*
 * ds18b20.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: healem
 */
#include <string>
#include "ds18b20.h"

DS18B20::DS18B20(const std::string& name) {
	mName = name;
}

DS18B20::~DS18B20() {
	// TODO Auto-generated destructor stub
}

std::string DS18B20::getName(){
	return mName;
}

int DS18B20::getTempInC(){
	return 0;
}

int DS18B20::getTempInF(){
	return 0;
}
