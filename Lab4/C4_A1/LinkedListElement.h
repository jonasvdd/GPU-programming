// Jonas Van Der Donckt
#ifndef LINKEDLIST_ELEMENT_H
#define LINKEDLIST_ELEMENT_H

#include "MemoryDevice.h"

class LinkedListElement{
private: 
	MemoryDevice* device = nullptr;
	LinkedListElement * next = nullptr;
public:
	//todo constructor
	explicit LinkedListElement(MemoryDevice* device);
	~LinkedListElement();

	void recursiveDelete();

	//getters 
	LinkedListElement * getNext() const;
	MemoryDevice * getDevice() const;

    //setters
	void setNext(LinkedListElement * element);
    void setDevice(MemoryDevice * device);
};

#endif // !LINKEDLIST_ELEMENT_H
