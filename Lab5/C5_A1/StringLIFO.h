// Jonas Van Der Donckt

#ifndef CONTAINER_STRINGLIFO_H
#define CONTAINER_STRINGLIFO_H

#include "LFO.h"
#include "StringFIFO.h"

template<int MaxElems = 10>
class StringLIFO : public LFO<LIFO, std::string, MaxElems> {
public:
    /* ---------------------------------------------
     *      	   Constructors and stuff
     * ---------------------------------------------*/
    StringLIFO() = default;

    template <dataStructure behavior_>
    StringLIFO(LFO<behavior_, std::string, MaxElems> &other){
        this->data = other.getData();
        this->behavior = LIFO;
    }

    const std::string Top()  {
        auto thisCpy = LFO<LIFO, std::string, MaxElems>(*this);
        std::string result;
        while(!thisCpy.isEmpty()){
            result.append(thisCpy.Top());
            thisCpy.Pop();
        }
        return result;
    }

    /* ---------------------------------------------
     *      	        Methods
     * ---------------------------------------------*/
    void Pop() {
        this->data.clear();
    }

    template <dataStructure Behavior_>
    bool Palindrome(LFO<Behavior_, std::string, MaxElems> &other){
        if (other.getBehavior() == FIFO){  // todo why cant I access protected content in this fkjdkljekldeje
            LFO<FIFO, std::string, MaxElems> temp = other;
            StringFIFO<MaxElems> strFifo =  StringFIFO<MaxElems>(temp);
            return strFifo.Top() == this->Top();
        }
        return false;
    }

    template <dataStructure Behavior_>
    bool Palindrome2(LFO<Behavior_, std::string, MaxElems> &other){
        if(other.getBehavior() == LIFO){
            LFO<FIFO, std::string, MaxElems> temp = other;
            StringFIFO<MaxElems> strFifo =  StringFIFO<MaxElems>(temp);
            return this->operator==(strFifo);
        }
        LFO<LIFO, std::string, MaxElems> temp = other;
        StringLIFO<MaxElems> strLifo =  StringLIFO<MaxElems>(temp);
        return this->operator==(strLifo);
    }
};

#endif //CONTAINER_STRINGLIFO_H
