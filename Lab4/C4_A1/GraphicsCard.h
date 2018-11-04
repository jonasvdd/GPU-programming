// Jonas Van Der Donckt
#ifndef GRAPHICS_CARD_H
#define GRAPHICS_CARD_H

#include "MemoryDevice.h"

class GraphicsCard : public MemoryDevice
{
private:
protected:
public:
    GraphicsCard(unsigned int capacity);
    ~GraphicsCard();
    std::string getName() const override;

    /**
     * a graphics card clears memory when disabled/removed from the computer system
     */
    void disable();
};

#endif //GRAPHICS_CARD_H
