// Jonas Van Der Donckt

#ifndef CONTAINER_STRINGFIFO_H
#define CONTAINER_STRINGFIFO_H

#include "LFO.h"
//#include "StringLIFO.h"

template<int MaxElems = 10>
class StringFIFO : public LFO<FIFO, std::string, MaxElems> {
public:
    /* ---------------------------------------------
     *      	   Constructors and stuff
     * ---------------------------------------------*/
    StringFIFO() = default;

    template <dataStructure behavior_>
    StringFIFO(LFO<behavior_, std::string, MaxElems> &other){
        //todo this may need to change.
        this->data = other.getData();
        this->behavior = FIFO;
    }

    /* ---------------------------------------------
     *      	        Methods
     * ---------------------------------------------*/
    const std::string Top() const  {
        auto thisCpy = LFO<FIFO, std::string, MaxElems>(*this);
        std::string result;
        while(!thisCpy.isEmpty()){
            result.append(thisCpy.Top());
            thisCpy.Pop();
        }
        return result;
    }

    void Pop() { this->data.clear(); }

    template <dataStructure Behavior_>
    bool Palindrome(LFO<Behavior_, std::string, MaxElems> &other){
        if (other.getBehavior() == LIFO){
            // todo can't cast here because i will get a circular dependency ... so we will make it a FIFO string
            LFO<FIFO, std::string, MaxElems> temp = other;
            StringFIFO<MaxElems> strFifo = StringFIFO<MaxElems>(temp);
            return this->Top() == strFifo.Top();
        }
        return false;
    }

    template <dataStructure Behavior_>
    bool Palindrome2(LFO<Behavior_, std::string, MaxElems> &other){
        if(Behavior_ == FIFO){
            LFO<LIFO, std::string, MaxElems>  temp = other;
            StringFIFO<MaxElems> strFifo = StringFIFO<MaxElems>(temp);
            return this->operator==(strFifo);
        }
        LFO<FIFO, std::string, MaxElems>  temp = other;
        StringFIFO<MaxElems> strFifo = StringFIFO<MaxElems>(temp);
        return this->operator==(strFifo);
    }
};

#endif //CONTAINER_STRINGFIFO_H
