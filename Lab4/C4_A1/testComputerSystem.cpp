// Jonas Van Der Donckt

#include <iostream>
#include "ComputerSystem.h"
#include "GraphicsCard.h"
#include "HardDrive.h"
#include "RAMModule.h"

using namespace std;

void expect(string testName, int value, int toBe) {
	if (value != toBe) {
		cout << "ERROR: Expect " << testName << " returned " << value << " but expected was " << toBe << endl;
	} else {
		cout << "TEST Expect " << testName << " succeeded!" << endl;
	}
}

void expectData(string testName, string input, string toBe) {
	if (toBe.compare(input) == string::npos) {
		cout << "ERROR: Expect " << testName << " returned " << input << " but expected was " << toBe << endl;
	} else {
		cout << "TEST Expect " << testName << " succeeded!" << endl;
	}
}

/**
 * This function is used to test if the enable/disable-function of ComputerSystem works correctly.
 */
void testEnabledDisabled() {
	ComputerSystem* computerSystem = new ComputerSystem(300);
	GraphicsCard* graphicsCard = new GraphicsCard(100);
	computerSystem->addDevice(graphicsCard);
	expect("graphicsCard card to be enabled", graphicsCard->isEnabled(), true);
	graphicsCard->disable();
	expect("graphicsCard card to be disabled", graphicsCard->isEnabled(), false);

	RAMModule* ram = new RAMModule(500);
	ram->disable();
	HardDrive* hdd = new HardDrive(1000);
	hdd->disable();
	delete computerSystem;
	delete ram;
	delete hdd;
}

void testPowerConsumption() {
	ComputerSystem* computerSystem = new ComputerSystem(150);
	GraphicsCard* graphicsCard = new GraphicsCard(100);
	computerSystem->addDevice(graphicsCard);
	expect("system to operate with just enough power", computerSystem->canOperate(), true);
	HardDrive* hdd = new HardDrive(2);
	computerSystem->addDevice(hdd);
	expect("system not to operate anymore", computerSystem->canOperate(), false);

	delete computerSystem;
}

void testWriteReadData() {
	ComputerSystem* computerSystem = new ComputerSystem(150);
	GraphicsCard* graphicsCard = new GraphicsCard(100);
	computerSystem->addDevice(graphicsCard);

	computerSystem->writeToDevice(graphicsCard->getDeviceID(), "blabla", 6);
	char* result = new char[7];
	result[6] = '\0';
	computerSystem->readFromDevice(graphicsCard->getDeviceID(), result, 6);
	expectData("read and written data to be the same", result, "blabla");
	delete[] result;

	computerSystem->writeToDevice(graphicsCard->getDeviceID(), "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 100);
	result = new char[101];
	result[100] = '\0';
	computerSystem->readFromDevice(graphicsCard->getDeviceID(), result, 100);
	expectData("to be written 100 bytes", result, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	delete[] result;

	computerSystem->writeToDevice(graphicsCard->getDeviceID(), "blabla", 6);
	result = new char[7];
	result[6] = '\0';
	computerSystem->readFromDevice(graphicsCard->getDeviceID(), result, 100);
	// We expect to only have read the 6 bytes that were written earlier
	expectData("to have read less than requested", result, "blabla");
	delete[] result;
	delete computerSystem;
}

void testBootPriorityOrder() {
	ComputerSystem* computerSystem = new ComputerSystem(150);
	GraphicsCard* graphicsCard = new GraphicsCard(100);
	computerSystem->addDevice(graphicsCard);
	RAMModule* module = new RAMModule(50);
	computerSystem->addDevice(module);
	HardDrive* hdd = new HardDrive(1000);
	computerSystem->addDevice(hdd);

	cout << "Order printed should be RAM --> HDD --> GraphicsCard. Check manually if correct!" << endl;
	computerSystem->listDevices();

	delete computerSystem;
}

void testRemoveDevice() {
	ComputerSystem* computerSystem = new ComputerSystem(150);
	GraphicsCard* graphicsCard = new GraphicsCard(100);
	computerSystem->addDevice(graphicsCard);
	RAMModule* module = new RAMModule(50);
	computerSystem->addDevice(module);
	HardDrive* hdd = new HardDrive(1000);
	computerSystem->addDevice(hdd);

	cout << "3 pieces of hardware should be listed:" << endl;
	computerSystem->listDevices();
	cout << "Now only 2 pieces of hardware should be listed:" << endl;
	computerSystem->removeDevice(hdd);
	computerSystem->listDevices();

	delete computerSystem;
}

int main() {
    for(int i =0; i < 100; i++){
        testPowerConsumption();
        testWriteReadData();
        testBootPriorityOrder();
        testRemoveDevice();
    }
	//system("PAUSE");
	return 0;
}
