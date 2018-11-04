// Jonas Van Der Donckt
#include "HardwareDescriptor.h"


/* ---------------------------------------------
 *                  Destructor
 * ---------------------------------------------*/
HardwareDescriptor::~HardwareDescriptor() = default;
// since std::string is on the stack it will
// auto delete out of scope.



/* ---------------------------------------------
 *                Protected setters
 * ---------------------------------------------*/
void HardwareDescriptor::setManufacturer(std::string man){
    this->manufacturer = std::move(man);
}

void HardwareDescriptor::setVersion(std::string vers){
    this->version = std::move(vers);
}

void HardwareDescriptor::setSerialNumber(std::string number){
    this->serialNumber = std::move(number);
}

/* ---------------------------------------------
 *                  Public getters
 * ---------------------------------------------*/
std::string HardwareDescriptor::getManufacturer() const {
    return this->manufacturer;
}

std::string HardwareDescriptor::getVersion() const {
    return this->version;
}

std::string HardwareDescriptor::getSerialNumber() const {
    return this->serialNumber;
}