// Jonas Van Der Donckt
#include "RAMModule.h"

RAMModule::RAMModule(unsigned int capacity) : MemoryDevice(capacity){
	this->setPowerConsumption(100);
	this->setPriority(1);
	this->setManufacturer("Intel");
	this->setVersion("rev 06");
	this->setSerialNumber("944623172236");
}


std::string RAMModule::getName() const {
	return "RAM: Intel Corporation Xeon E3-1200 v3/4th Gen Core Processor DRAM Controller (rev 06)";
}


RAMModule::~RAMModule(){
	//todo;
}


void RAMModule::disable() {
    this->dumpMemory();
    MemoryDevice::disable();
    this->writeBytes("", 0);
}