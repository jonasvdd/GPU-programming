// Jonas Van Der Donckt
#include "LinkedListElement.h"

/* ---------------------------------------------
 *             Constructor & Destructor
 * ---------------------------------------------*/
LinkedListElement::LinkedListElement(MemoryDevice *device){
    this->device = device;
}


LinkedListElement::~LinkedListElement() { delete this->device; }


void LinkedListElement::recursiveDelete() {
    if (next != nullptr){
        next->recursiveDelete();
    }
    delete this;
}



/* ---------------------------------------------
 *             Public getters
 * ---------------------------------------------*/
LinkedListElement * LinkedListElement::getNext() const{return this->next;}
MemoryDevice * LinkedListElement::getDevice() const { return this->device;}


/* ---------------------------------------------
 *             Public setters
 * ---------------------------------------------*/
void LinkedListElement::setNext(LinkedListElement * element){	this->next = element;}
void LinkedListElement::setDevice(MemoryDevice *device) {this->device = device;}