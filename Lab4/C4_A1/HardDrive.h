// Jonas Van Der Donckt
#ifndef HARD_DRIVE_H
#define HARD_DRIVE_H

#include "MemoryDevice.h"

// a HardDrive is a specific type of memory device that can be used to read/write data to
// a HardDrive keeps the data when it is disabled / removed from the computer system

class HardDrive : public MemoryDevice 
{
public:
	HardDrive(unsigned int capacity);
	~HardDrive();
	std::string getName() const;
protected:
private:
};

#endif