// Jonas Van Der Donckt
#ifndef RAM_MODULE_H
#define RAM_MODULE_H

#include "MemoryDevice.h"

// a RAMModule is a specific type of memory device that can be used to read/write data to

class RAMModule : public MemoryDevice 
{
protected:
private:
public:
	RAMModule(unsigned int capacity);
	~RAMModule();
	std::string getName() const;

	/**
 	* a RAMModule clears memory when disabled/removed from the computer system
 	*/
	void disable();
};

#endif