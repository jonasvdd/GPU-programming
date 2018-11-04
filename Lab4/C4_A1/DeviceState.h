// Jonas Van Der Donckt
#ifndef DEVICE_STATE_H
#define DEVICE_STATE_H


class DeviceState{
private:
	// data members
	bool active;
	unsigned int bootPriority;
protected:
    // setter
	void setPriority(unsigned int priority);
public:
    virtual // destructor
	~DeviceState();

	// setters
	void enable();
	void disable();
	
	// getters 
	bool isEnabled() const;
	unsigned int getBootPriority() const ;
};

#endif // !DEVICE_STATE_H
