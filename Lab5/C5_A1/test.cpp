// Jonas Van Der Donckt

#include <iostream>
#include "LFO.h"
#include "StringLIFO.h"
#include <cassert>

/* ---------------------------------------------
 *             	   Defines
 * ---------------------------------------------*/
#define ASSERT_TRUE(func)       (assert(func ==true))
#define ASSERT_FALSE(func)      (assert(func == false))
#define ASSERT_VAL(func, val)   (assert(func == val))

/**
 * used for converting to a certain datatype
 */
template<typename dataType>
dataType toElement(int i) { return static_cast<dataType>(i);; }

/**
 * used for converting to a certain datatype
 */
template <>
std::string toElement<std::string>(int i){  return std::to_string(i); }

// TODO: my tests are ugly i know
template<class dataType>
void test_size() {
    LFO<LIFO, dataType, 6> test1Stack;
    for (int i = 0; i < 10; ++i) {
        auto temp = toElement<dataType>(i);
        test1Stack.push(temp);
    }    //todo check the difference with static and dynamic casts
    for (int j = 5; j >= 0; --j) {
        auto temp = toElement<dataType>(j);
        ASSERT_VAL(test1Stack.Top(), temp);
        ASSERT_TRUE(test1Stack.Pop());
    }
    ASSERT_FALSE(test1Stack.Pop());

    LFO<FIFO, dataType, 6> test1Queue;
    for (int i = 0; i < 10; ++i) {
        auto temp = toElement<dataType>(i);
        test1Queue.push(temp); }
    for (int j = 0; j < 6; ++j) {
        auto temp = toElement<dataType>(j);
        ASSERT_VAL(test1Queue.Top(),temp);
        ASSERT_TRUE(test1Queue.Pop());
    }
    ASSERT_FALSE(test1Queue.Pop());    // todo check this.


    //testing with size 0
    LFO<LIFO, dataType, 0> test2Stack;
    for (int i = 0; i < 10; ++i) {
        auto temp = toElement<dataType>(i);
        test2Stack.push(temp); }
    for (int j = 10; j >= 0; --j) { ASSERT_FALSE(test2Stack.Pop()); }

    LFO<FIFO, dataType, 0> test2Queue;
    for (int i = 0; i < 10; ++i) {
        auto temp =  toElement<dataType>(i);
        test2Queue.push(temp); }
    for (int j = 10; j >= 0; --j) { ASSERT_FALSE(test2Queue.Pop()); }

    // testing with size -1
    LFO<FIFO, dataType, -1> test3Stack;
    for (int i = 0; i < 10; ++i) {
        auto temp =  toElement<dataType>(i);
        test3Stack.push(temp);
    }
    for (int j = 0; j < 10; ++j) { ASSERT_FALSE(test3Stack.Pop()); }
    //delete test3Stack;

    LFO<FIFO, dataType, -1> test3Queue;
    for (int i = 0; i < 10; ++i) {
        auto temp = toElement<dataType>(i);
        test3Queue.push(temp);
    }
    for (int k = 0; k < 10; ++k){ ASSERT_FALSE(test3Queue.Pop()); }
}

template<class dataType>
void test_operators(){
    /* ---------------------------------------------
    *             	        ==
    * ---------------------------------------------*/
    LFO<LIFO, dataType, 10> test_stack1;
    LFO<LIFO, dataType, 10> test_stack2;    //todo invalid free pointer.
    for (int i = 0; i <10; ++i) {
        auto temp = toElement<dataType>(i);
        test_stack1.push(temp);
        test_stack2.push(temp);
    }
    ASSERT_TRUE(test_stack1==test_stack2); // todo als dit in commenctaar staat krijg ik een double free of corruption
    ASSERT_TRUE(test_stack1.isEmpty());
    //ASSERT_TRUE(test_stack2.isEmpty());     //todo how to empty both containers

    LFO<FIFO, dataType, 10> test_queue1;
    LFO<FIFO, dataType, 10> test_queue2;
    for (int i = 0; i <10; ++i) {
        auto temp = toElement<dataType>(i);
        test_queue1.push(temp);
        test_queue2.push(temp);
    }
    ASSERT_TRUE(test_queue1==test_queue2);
    ASSERT_TRUE(test_queue1.isEmpty());
    //ASSERT_TRUE(test_queue2.isEmpty());


    /* ---------------------------------------------
    *             	        +=
    * ---------------------------------------------*/
    LFO<FIFO,dataType, 10> test_queue3;
    LFO<FIFO,dataType, 10> test_queue4;
    for (int j = 0; j < 6; ++j) {
        auto temp = toElement<dataType>(j);
        test_queue3.push(temp);
    }
    for(int j = 6; j < 20; j++){
        auto temp = toElement<dataType>(j);
        test_queue4.push(temp);
    }
    test_queue3+=test_queue4;
    for (int j = 0; j <= 9; ++j) {
        ASSERT_VAL(test_queue3.Top(), toElement<dataType>(j));
        test_queue3.Pop();
    }
    ASSERT_TRUE(test_queue3.isEmpty());

    LFO<LIFO,dataType, 10> test_stack3;
    LFO<LIFO,dataType, 10> test_Stack4;
    for (int j = 0; j < 5; ++j) {
        auto temp = toElement<dataType>(j);
        test_stack3.push(temp);
    }
    for(int j = 9; j >= 5; j--){
        auto temp = toElement<dataType>(j);
        test_Stack4.push(temp);
    }
    test_stack3+=test_Stack4;
    for (int j = 9; j >= 0; --j) {
       ASSERT_VAL(test_stack3.Top(), toElement<dataType>(j));
        test_stack3.Pop();
    }
    ASSERT_TRUE(test_stack3.isEmpty());

    /* ---------------------------------------------
    *             	        -=
    * ---------------------------------------------*/
    LFO<FIFO,dataType, 10> test_queue5;
    LFO<FIFO,dataType, 10> test_queue6;
    for (int j = 0; j < 6; ++j) {
        auto temp = toElement<dataType>(j);
        test_queue3.push(temp);
    }
    for(int j = 6; j < 20; j++){
        auto temp = toElement<dataType>(j);
        test_queue4.push(temp);
    }
    test_queue3+=test_queue4;
    for (int j = 0; j <= 9; ++j) {
        ASSERT_VAL(test_queue3.Top(), toElement<dataType>(j));
        test_queue3.Pop();
    }
    ASSERT_TRUE(test_queue3.isEmpty());

    LFO<LIFO,dataType, 10> test_stack5;
    LFO<LIFO,dataType, 10> test_Stack6;
    for (int j = 0; j < 5; ++j) {
        auto temp = toElement<dataType>(j);
        test_stack3.push(temp);
    }
    for(int j = 9; j >= 5; j--){
        auto temp = toElement<dataType>(j);
        test_Stack4.push(temp);
    }
    test_stack3+=test_Stack4;
    for (int j = 9; j >= 0; --j) {
        ASSERT_VAL(test_stack3.Top(), toElement<dataType>(j));
        test_stack3.Pop();
    }
    ASSERT_TRUE(test_stack3.isEmpty());
}

void test_Specializations(){
    StringLIFO<6> strLifo;
    for (int i = 0; i < 6; ++i) {
        std::string temp = std::to_string(i);
        strLifo.push(temp);
    }
    ASSERT_VAL(strLifo.Top(), "543210");
    strLifo.Pop();
    ASSERT_TRUE(strLifo.isEmpty());

    StringFIFO<6> strFifo;
    for (int i = 0; i < 6; ++i) {
        std::string temp = std::to_string(i);
        strFifo.push(temp);
    }
    ASSERT_VAL(strFifo.Top(), "012345");
    strFifo.Pop();
    ASSERT_TRUE(strFifo.isEmpty());
}

void test_palindrome(std::string palStr, bool isPalinDroom){
    StringLIFO<100> strLifo1, strLifo2, strLifo3, strLifo4;
    StringFIFO<100> strFifo1, strFifo2, strFifo3, strFifo4;
    for (int i = 0; i < palStr.length(); ++i) {
        std::string temp = palStr.substr(i, 1);
        strLifo1.push(temp);
        strLifo2.push(temp);
        strLifo3.push(temp);
        strLifo4.push(temp);
        strFifo1.push(temp);
        strFifo2.push(temp);
        strFifo3.push(temp);
        strFifo4.push(temp);
    }
    /* ---------------------------------------------
    *             	  Palindrome
    * ---------------------------------------------*/
    if (isPalinDroom){
        ASSERT_TRUE(strLifo1.Palindrome(strFifo1));
        ASSERT_FALSE(strLifo1.Palindrome(strLifo1));
        ASSERT_TRUE(strFifo1.Palindrome(strLifo1));
        ASSERT_FALSE(strFifo1.Palindrome(strFifo2));
    } else {
        ASSERT_FALSE(strLifo1.Palindrome(strFifo1));
        ASSERT_FALSE(strLifo1.Palindrome(strLifo2));
        ASSERT_FALSE(strFifo1.Palindrome(strLifo1));
        ASSERT_FALSE(strFifo1.Palindrome(strFifo2));
    }


    /* ---------------------------------------------
    *             	   Palindrome2
    * ---------------------------------------------*/
    if (isPalinDroom){
        ASSERT_TRUE(strFifo1.Palindrome2(strLifo1));
        ASSERT_TRUE(strFifo2.Palindrome2(strFifo3));
        ASSERT_TRUE(strLifo2.Palindrome2(strFifo4));
        ASSERT_TRUE(strLifo3.Palindrome2(strLifo4));
    } else {
        ASSERT_FALSE(strFifo1.Palindrome2(strLifo1));
        ASSERT_FALSE(strFifo2.Palindrome2(strFifo3));
        ASSERT_FALSE(strLifo2.Palindrome2(strFifo4));
        ASSERT_FALSE(strLifo3.Palindrome2(strLifo4));
    }
    ASSERT_TRUE(strFifo1.isEmpty());
    ASSERT_TRUE(strFifo2.isEmpty());
    ASSERT_TRUE(strLifo2.isEmpty());
    ASSERT_TRUE(strLifo3.isEmpty());
}

int main() {
    test_size<int>();
    test_size<float>();
    test_size<std::string>();

    test_operators<int>();
    test_operators<float>();
    test_operators<std::string>();

    test_Specializations();

    test_palindrome("ayy the code works", false);
    test_palindrome("lepel", true);
    test_palindrome("sore was I ere I saw eros", true);
    return 0;
}