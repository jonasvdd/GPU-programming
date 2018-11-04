// Jonas Van Der Donckt
#ifndef HARDWARE_DESCRIPTOR
#define HARDWARE_DESCRIPTOR

#include <string>

class HardwareDescriptor
{
private:
    std::string manufacturer;
    std::string version;
    std::string serialNumber;

protected: 
	// setters
	void setManufacturer(std::string man);
	void setVersion(std::string vers);
	void setSerialNumber(std::string number);
public:
	// destructors
	~HardwareDescriptor();
    // getters
    std::string getManufacturer() const;
    std::string getVersion() const;
    std::string getSerialNumber() const ;
};

#endif // !HARDWARE_DESCRIPTOR