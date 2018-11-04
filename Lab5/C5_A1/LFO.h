// Jonas Van Der Donckt

#ifndef CONTAINER_LFO_H
#define CONTAINER_LFO_H

#include <vector>
#include <iostream>

/**
 * An enum that indicates the order of the LFO data
 */
enum dataStructure : unsigned char {
    LIFO = 0,   // lifo = stack
    FIFO = 1    // fifo = queue
};


template<dataStructure Behavior, typename DataType, int MaxElems = 10>
class LFO {
protected:
    // data members
    std::vector<DataType> data;
    dataStructure behavior = Behavior;
private:
    // since size returns an unsigned long
    unsigned long getMaxElems() const { return MaxElems > 0 ? (unsigned long) MaxElems : 0; }

public:
    /**
     * TODO these getters are used since we cant access private/protected members/functions
     * in the template specifications
     */
    std::vector<DataType> getData() const { return data; };
    dataStructure getBehavior() { return behavior; };

    /* ---------------------------------------------
     *      	   Constructors and stuff
     * ---------------------------------------------*/
    /**
     * Default constructor and destructor
     */
    LFO() = default;
    ~LFO() = default;

    /**
     * Copy constructor
     * @tparam behavior_ : the behavior that will be adapted
     * @param other : the object that will be copied.
     */
    template<dataStructure behavior_>
    LFO(const LFO<behavior_, DataType, MaxElems> &other) {
        this->data.clear();
        if (this->behavior == behavior_){
            this->data = getData();
        } else {
            this->behavior = behavior_;
            std::vector<DataType> temp = other.getData();
            while (!temp.empty()){
                this->data.insert(data.begin(), temp.front());
                temp.erase(temp.begin());
            }
        }
    }

    /* ---------------------------------------------
     *             	   Methods
     * ---------------------------------------------*/
    /**
     * Adds an element to the container. If the container has reached the max
     * number of elements, the element is not added to the container.
     */
    void push(DataType &elem) {
        if (!this->isFull()) {
            this->data.insert(this->data.end(), elem);
        }
    }

    /**
     *  Removes the first/last element based on the data structure enum
     *  @return false if the container is empty and nothing could be removed,
     *  true otherwise.
     */
    bool Pop() {
        if (!this->isEmpty()) {
            if (behavior == LIFO)
                this->data.erase(this->data.end() - 1);
            else {   // LIFO
                this->data.erase(this->data.begin());
            }
            return true;
        }
        return false;
    }

    /**
    * @return the first element of the list based on the data structure enum
    */
    const DataType &Top() const {
        if (behavior == LIFO) {
            return this->data.back();
        } else {
            return this->data.front();
        }
    }

    /**
     * @return true if there are no elements left in this container, false otherwise
     */
    bool isEmpty() const { return this->data.empty(); }

    /**
     * @return true if the maximum number of elements is reached,  false otherwise
     */
    bool isFull() const { return this->data.size() >= getMaxElems(); }


    /* ---------------------------------------------
     *             	   OPERATORS
     * ---------------------------------------------*/
    /**
     * All elements of one container are added to elements of another container.
     * If more elements are added than specified as maximum, extra elements are discarded.
     */
    LFO &operator+=(const LFO &other) {
        LFO copy = LFO(other);
        while (!this->isFull() && !copy.isEmpty()) {
            DataType temp = copy.Top();
            this->push(temp);
            copy.Pop();
        }
        return *this;
    }

    /**
     * Elements of one container are removed as long as the top of both are equal.
     */
    LFO &operator-=(const LFO &other) {
        LFO copyOther = LFO(other);
        while (!this->isEmpty() and !other.isEmpty() && this->Top() == copyOther.Top()) {
            this->Pop();
            copyOther.Pop();
        }
        return *this;;
    }

    /**
     * Compare and empty both containers by piece by piece cancellation of elements.
     * Equality is satisfied if both containers are the same.
     * @return true if both containers are the same, false otherwise.
     */
    template<dataStructure Behavior_>
    bool operator==(const LFO<Behavior_, DataType, MaxElems> &other) {
        auto *copyOther = new LFO(other);
        bool areEqual = true;
        while (!this->isEmpty() || !copyOther->isEmpty()) {
            if (this->Top() != copyOther->Top()) {
                areEqual = false;
            }
            this->Pop();
            copyOther->Pop();
        }
        delete copyOther;
        return areEqual;
    }

    /**
     * Overrides the = operator, if the data type and Max El. are the same
     */
    template <dataStructure behavior_>
    LFO &operator=(LFO<behavior_, DataType, MaxElems> &lfoEl) {
        this->data.clear();
        if (this->behavior == behavior_){
           this->data = getData();
        } else {
            this->behavior = behavior_;
            std::vector<DataType> temp = lfoEl.getData();
            while (!temp.empty()){
                this->data.insert(data.begin(temp.back()));
                temp.pop_back();
            }
        }
        return *this;
    }
};

#endif //CONTAINER_LFO_H