#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

// FP.3 Define a class „MessageQueue“ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// Also, there should be an std::condition_variable as well as an std::mutex as private members. 

// FP3.1: DONE: Define a class „MessageQueue“ which has the public methods send and receive. 
// FP3.2: DONE: Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// FP3.3: TODO: the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// FP3.4: TODO: there should be an std::condition_variable as well as an std::mutex as private members. 

template <class T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);

private:
    // TODO : there should be an std::condition_variable as well as an std::mutex as private members. 
    // dequeue better than vector for push FIFO!! see ... 
    // TODO : the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase () 
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

enum TrafficLightPhase {red, green};

class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight();

    // TODO : NC NO NEED ?? ~TrafficLight();

    // getters / setters
    TrafficLightPhase getCurrentPhase();

    // typical behaviour methods
    void waitForGreen();
    void simulate();

private:
    // typical behaviour methods
    void cycleThroughPhases();

    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.

    // FP4b.1: TODO: create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // FP4b.2: TODO: and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    //               send in conjunction with move semantics.

    std::condition_variable _condition;
    std::mutex _mutex;

    TrafficLightPhase _currentPhase;    // TrafficLightPhase::red/green
};

#endif