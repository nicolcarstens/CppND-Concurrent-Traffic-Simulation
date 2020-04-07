/******************************************************************************
*
*  Udacity Nanodegree in C++
*  Concurrent Traffic Simulation - Project 4 
*
*  Work done by Nicol Carstens, March/April 2020
*  Baseline code provided by udacity.com
*
*  Status: ready to submit (7 April 2020)
*
*  Copyright: Nicol Carstens & Udacity 2020
*
******************************************************************************/

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include loop
class Vehicle;

enum class TrafficLightPhase {red = 1, green};

// FP.3 Define a class „MessageQueue“ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// Also, there should be an std::condition_variable as well as an std::mutex as private members. 

// FP3.1: DONE: Define a class „MessageQueue“ which has the public methods send and receive. 
// FP3.2: DONE: Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// FP3.3: DONE: the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// FP3.4: DONE: there should be an std::condition_variable as well as an std::mutex as private members. 

template <class TrafficLightPhase>
class MessageQueue
{
public:
    TrafficLightPhase receive();
    void send(TrafficLightPhase &&msg);

private:
    std::condition_variable _condition;   // generally i hate it when there are multiple declarations with different scope
    std::mutex _mutexMsgQ;                // for variables named _mutex or _condition or lock ... Will allow _condition 
                                          // since the name was used in the instruction, but _mutex already used in 
                                          // in class Intersection, so make this on _mutexMsgQ to avoid confusion 

    // dequeue better than vector for push FIFO!! 
    // see https://en.cppreference.com/w/cpp/container/deque
    // NB: But there is a problem with the project design. It is a STUPID idea to keep track of all of the changes of the 
    //     traffic lights?!? And it causes a problem of a growing queue that serves no purpuse. This becomes silly. 
    std::deque<TrafficLightPhase> _queue;
};

// FP.1 : Define a class „TrafficLight“ which is a child class of TrafficObject. 
// The class shall have the public methods „void waitForGreen()“ and „void simulate()“ 
// as well as „TrafficLightPhase getCurrentPhase()“, where TrafficLightPhase is an enum that 
// can be either „red“ or „green“. Also, add the private method „void cycleThroughPhases()“. 
// Furthermore, there shall be the private member _currentPhase which can take „red“ or „green“ as its value. 

// Pro tip: Search for "FP1" or "FP3" and note if tasks are "DONE" or "TODO" ;-) 

// FP1.1: DONE: Define a class „TrafficLight“ which is a child class of TrafficObject. 
// FP1.2: DONE: The class shall have the public methods „void waitForGreen()“ and „void simulate()“ 
// FP1.3: DONE: as well as „TrafficLightPhase getCurrentPhase()“, 
// FP1.4: DONE: where TrafficLightPhase is an enum that can be either „red“ or „green“
// FP1.5: DONE: add the private method „void cycleThroughPhases()“. 
// FP1.6: DONE: there shall be the private member _currentPhase which can take „red“ or „green“ as its value.

class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    //
    // ... but if you define destructor ... then Rule of 3 ... and then Rule of 5?!
    // 
    // class_name ( const class_name & ) = delete; 	
    // https://en.cppreference.com/w/cpp/language/copy_constructor
    // 
    // class_name ( class_name && ) = delete;
    // https://en.cppreference.com/w/cpp/language/move_constructor
    // 
    // class_name & class_name :: operator= ( class_name && ) = delete;
    // https://en.cppreference.com/w/cpp/language/move_assignment
    //
    // class_name & class_name :: operator= ( const class_name & ) = delete; 	
    // https://en.cppreference.com/w/cpp/language/copy_assignment    


    TrafficLight();                 // 0: vanilla constructor => we write! 

    ~ TrafficLight () = default;    // 1: destructor => default fine! No no significant resources 
                                    //    to release unlike, for example, ~TrafficObject()
 
    TrafficLight ( const TrafficLight & ) = delete;               // 2: copy constructor 
    TrafficLight ( TrafficLight && ) = delete;                    // 3: move constructor 

    TrafficLight &  operator= ( const TrafficLight & ) = delete;  // 4: copy assignment 
    TrafficLight &  operator= ( TrafficLight && ) = delete;       // 5: move assignment 

    // getters / setters
    TrafficLightPhase getCurrentPhase() const;
    void setCurrentPhase(const TrafficLightPhase & newPhase);

    // typical behaviour methods
    void waitForGreen();
    void simulate();

private:
    // typical behaviour methods
    void cycleThroughPhases();

    TrafficLightPhase _currentPhase;      // TrafficLightPhase::red/green
                                          // No protective mutex required?

    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.

    // FP4b.1: DONE: create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // FP4b.2: DONE: and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    //               send in conjunction with move semantics.

    std::shared_ptr<MessageQueue<TrafficLightPhase>> _msgQueue;
};

#endif