// Jonas Van Der Donckt
#include "HardDrive.h"

HardDrive::HardDrive(unsigned int capacity) : MemoryDevice(capacity) {
	this->setPowerConsumption(100);
	this->setPriority(3);
	this->setManufacturer("Samsung");
	this->setVersion("EXT06L0Q");
	this->setSerialNumber("S1NYNSAG900140");
}

std::string HardDrive::getName() const{
	return "SSD: SAMSUNG MZ7TE512HMHP-000L2";
}

HardDrive::~HardDrive(){}
