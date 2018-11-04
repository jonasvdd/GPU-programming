// Jonas Van Der Donckt
#include "DeviceState.h"


/* ---------------------------------------------
*                Destructor
 * ---------------------------------------------*/
DeviceState::~DeviceState() = default;
// since all data members are on the stack, it will
// auto delete them when out of scope


/* ---------------------------------------------
 *             Protected setters
 * ---------------------------------------------*/
void DeviceState::setPriority(unsigned int priority) {
    this->bootPriority = priority;
}



/* ---------------------------------------------
 *             Public setters
 * ---------------------------------------------*/
void DeviceState::enable(){this->active = true;}
void DeviceState::disable(){this->active = false;}



/* ---------------------------------------------
 *             Public getters
 * ---------------------------------------------*/
bool DeviceState::isEnabled() const { return this->active;}
unsigned int DeviceState::getBootPriority() const{
    return this->bootPriority;
}