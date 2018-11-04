// Jonas Van Der Donckt
#include "GraphicsCard.h"
using namespace std;

GraphicsCard::GraphicsCard(unsigned int capacity) : MemoryDevice(capacity)  {
    setPowerConsumption(100);
    this->setPriority(5);
    this->setManufacturer("NVIDEA");
    this->setVersion("rev a2");
    this->setSerialNumber("3654654687");
}


std::string GraphicsCard::getName() const{
    return "Graphics card: 3D controller: NVIDIA Corporation GM107M [GeForce GTX 960M]";
}

GraphicsCard::~GraphicsCard(){
}

// a graphics card clears memory when disabled/removed.
void GraphicsCard::disable() {
    this->dumpMemory();
    MemoryDevice::disable();
    this->writeBytes("", 0);
}

