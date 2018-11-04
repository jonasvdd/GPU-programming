// Jonas Van Der Donckt
#include "MemoryDevice.h"
#include <iostream>

/* ---------------------------------------------
 *            Constructor & Destructor
 * ---------------------------------------------*/
MemoryDevice::MemoryDevice(unsigned int capacity) : maxStorage(capacity){
	this->deviceID = id++;
    enable();
}

MemoryDevice::~MemoryDevice() {
    delete[](data);
}



/* ---------------------------------------------
 *             Protected setters
 * ---------------------------------------------*/
void MemoryDevice::setPowerConsumption(unsigned int val){
    this->powerConsumption = val;
}


/* ---------------------------------------------
 *             Public getters
 * ---------------------------------------------*/
unsigned int MemoryDevice::getPowerConsumption() const {
    return this->isEnabled() ? this->powerConsumption : 0;
}

unsigned int MemoryDevice::getDeviceID() const {
    return  this->isEnabled() ? this->deviceID : 0;
}

unsigned int MemoryDevice::getMemoryCapacity() const {
    return this->isEnabled() ? this->maxStorage : 0;
}



size_t MemoryDevice::writeBytes(char *data, size_t amount) {
    delete[] this->data;
    this->data = new char[amount];
    if (this->isEnabled()) {
        size_t index = 0;
        while (index < amount && data[index] != NULL_CHAR) {
            this->data[index] = data[index];
            index++;
        }
        return index;
    }
    return 0;
}

size_t MemoryDevice::readBytes(char *out_Data, size_t amount) {
    if (this->isEnabled() && this->data != nullptr) {
        size_t index = 0;
        while (index < amount && this->data[index] != NULL_CHAR) {
            out_Data[index] = this->data[index];
            index++;
        }
        return index;
    }
    return 0;
}


void MemoryDevice::dumpMemory() {
    // which memory should be dumperd in std::cout ?? todo
    if (data != nullptr){
        std::cout << static_cast<std::string>(data) << std::endl;
    } else {
        std::cout << "\tThere is no data to be dumped" << std::endl;
    }
}







