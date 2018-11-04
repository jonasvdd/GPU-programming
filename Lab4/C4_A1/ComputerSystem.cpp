// Jonas Van Der Donckt
#include "ComputerSystem.h"
#include <iostream>

ComputerSystem::ComputerSystem(int psuWattage){
	this->totalWattage = psuWattage;
	headptr = nullptr;
}

ComputerSystem::~ComputerSystem(){
	// destructor TODO
    if (headptr != nullptr){
        headptr->recursiveDelete();
    }
}

void ComputerSystem::listDevices(){
	LinkedListElement * elementptr = headptr;
	// we assume that the list is already sorted.
    std::cout << "-------------- Devices ----------" << std::endl;
	while(elementptr != nullptr){
		MemoryDevice * device = elementptr->getDevice();
		std::cout << "name: " << device->getName() << std::endl;
		std::cout << "mnfr: " << device->getManufacturer() << std::endl;
		std::cout << "vers: " << device->getVersion() << std::endl;
		std::cout << "ID:   " << device->getDeviceID() << std::endl;
		std::cout << "on:   " << device->isEnabled() << std::endl;
        std::cout << "prior:" << device->getBootPriority() << std::endl;
        std::cout << "sernr:" << device->getSerialNumber() << "\n" << std::endl;
        elementptr = elementptr->getNext();
	}
}

bool ComputerSystem::canOperate() const {
	unsigned int totalConsumed = 0;
	LinkedListElement * elementptr = headptr;
	while (elementptr != nullptr){
		MemoryDevice * listDevice = elementptr->getDevice();
		totalConsumed += listDevice->isEnabled() ? listDevice->getPowerConsumption() : 0;
		elementptr = elementptr->getNext();
	}
	return totalWattage > totalConsumed;
}

void ComputerSystem::addDevice(MemoryDevice * device){
	if(headptr == nullptr){
		headptr = new LinkedListElement(device);
	}
	else {
		LinkedListElement * elementptr = headptr;
		LinkedListElement * prevElementptr = nullptr;
		while(elementptr != nullptr){
			MemoryDevice * listDevice = elementptr->getDevice();
			if(listDevice->getBootPriority() > device->getBootPriority()){
				// we need to change
				LinkedListElement * newElement = new LinkedListElement(device);
				if (prevElementptr != nullptr){
                    prevElementptr->setNext(newElement);
                }
                else {
                    headptr = newElement;
                }
				newElement->setNext(elementptr);
				break;
			}
			else if(elementptr->getNext() == nullptr){
				// we reached the end of the list
				LinkedListElement * newElement = new LinkedListElement(device);
				elementptr->setNext(newElement);
				break;
			}
			prevElementptr = elementptr;
			elementptr = elementptr->getNext();
		}
	}
}


void ComputerSystem::removeDevice(MemoryDevice * device){
	LinkedListElement * elementptr = headptr;
	LinkedListElement * prevElementptr = nullptr;
	while(elementptr != nullptr){
		MemoryDevice * listDevice = elementptr->getDevice();
		if (listDevice->getDeviceID() == device->getDeviceID()){
			// if it is the first element, the head pointed needs to be change
			if(prevElementptr == nullptr){
					headptr = elementptr->getNext();
			}
			// if there exist a successor it needs to be connected.
			prevElementptr->setNext(elementptr->getNext());
			delete elementptr;
			break;
		}
		prevElementptr = elementptr;
		elementptr = elementptr->getNext();
	}
}


void ComputerSystem::writeToDevice(unsigned int deviceID, char * data, size_t amount){
	LinkedListElement * elementptr = headptr;
	while(elementptr != nullptr){
		MemoryDevice * device = elementptr->getDevice();
		if (device->getDeviceID() == deviceID){
			device->writeBytes(data, amount);
			break;
		}
		elementptr = elementptr->getNext();
	}
}


void ComputerSystem::readFromDevice(unsigned int deviceID, char * data, size_t amount){
	LinkedListElement * elementptr = headptr;
	while(elementptr != nullptr){
		MemoryDevice * device = elementptr->getDevice();
		if (device->getDeviceID() == deviceID){
			device->readBytes(data, amount);
			break;
		}
		elementptr = elementptr->getNext();
	}
}


void ComputerSystem::printDeviceMemory(unsigned int deviceID){
	LinkedListElement * elementptr = headptr;
	while(elementptr != nullptr){
		MemoryDevice * device = elementptr->getDevice();
		if (device->getDeviceID() == deviceID){
			device->dumpMemory();
			break;
		}
		elementptr = elementptr->getNext();
	}
}