// Jonas Van Der Donckt
#include "MemoryDevice.h"
#include "HardwareDescriptor.h"
#include "LinkedListElement.h"


class ComputerSystem{
private:
	LinkedListElement * headptr;
	int totalWattage;
public:
	// constructor & destructor
	ComputerSystem(int psuWattage);
	~ComputerSystem();

	void listDevices();
	bool canOperate() const;
	void addDevice (MemoryDevice* device);
	void removeDevice(MemoryDevice * device);
	void writeToDevice(unsigned int deviceID, char * data, size_t amount);

	void readFromDevice(unsigned int deviceID, char * data, size_t amount);
	void printDeviceMemory(unsigned int deviceID);
};
