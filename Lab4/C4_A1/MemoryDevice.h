// Jonas Van Der Donckt
#ifndef MEMORY_DEVICE_H
#define MEMORY_DEVICE_H

#include "HardwareDescriptor.h"
#include "DeviceState.h"


/* ---------------------------------------------
 *             	   CONSTANTS
 * ---------------------------------------------*/
#define NULL_CHAR '\0'
#define FIRST_ID 1

// data members.
static unsigned int id = FIRST_ID;


class MemoryDevice : public HardwareDescriptor, public DeviceState {
private:
	//data members 
	unsigned int deviceID;
	const unsigned int maxStorage;			// in Bytes
	unsigned int powerConsumption;			// in Watts
	char * data = nullptr;					// to store data
protected: 
	/**
	 * @param val, The new value for the power consumption
	 */
	void setPowerConsumption(unsigned int val); 
public:
	/**
	 * Creates an instance of Memorydevice, assigns a unique
	 * Id to each device.
	 * @param capacity the maximum memory storage capacity.
	 */
	MemoryDevice(unsigned int capacity);

    /**
     * Abstract desctructor, will be implemented by the
     * derived classes
     */
	virtual ~MemoryDevice();

    /**
     * @return returns the power consumption if enabled, 0 otherwise
     */
	unsigned int getPowerConsumption() const;

    /**
     * @return returns the device ID if enabled, 0 otherwise
     */
	unsigned int getDeviceID() const;

    /**
     * @return returns the memory capacity if enabled, 0 otherwise
     */
	unsigned int getMemoryCapacity() const; //todo moet ik dit nog gebruiken ??
	
	virtual std::string getName() const = 0;

	// write/ reads data of the size amount to/from the device
	// returns the amount of bytes successfully read. should only work when the 
	// device is enabled
	size_t writeBytes(char * data, size_t amount);
	size_t readBytes(char * out_Data, size_t amount);

    /**
	 * 	dumps memory in the std::cout, should only work when the device is enabled
	 */
	void dumpMemory();
};

#endif // !MEMORY_DEVICE_H
