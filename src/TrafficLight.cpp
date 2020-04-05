#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 

    // FP5a.1: TODO: The method receive should use std::unique_lock<std::mutex> and 
    // FP5a.2: TODO: _condition.wait() to wait for and receive new messages 
    // FP5a.3: TODO: and pull them from the queue using move semantics. 
    // FP5a.4: TODO: The received object should then be returned by the receive function. 

    // std::unique_lock<std::mutex>
    // _condition.wait() 
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.

    // FP4a.1: TODO: The method send should use the mechanisms std::lock_guard<std::mutex> 
    // FP4a.2: TODO: as well as _condition.notify_one() to add a new message to the queue 
    // FP4a.3: TODO: and afterwards send a notification.

    // std::lock_guard<std::mutex> 
    // _condition.notify_one()
}

/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.

    // FP5b.1: TODO: add the implementation of the method waitForGreen, 
    // FP5b.2: TODO: in which an infinite while-loop runs and 
    // FP5b.3: TODO: repeatedly calls the receive function on the message queue. 
    // FP5b.4: TODO: Once it receives TrafficLightPhase::green, the method returns.

}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when 
    //         the public method „simulate“ is called. To do this, use the thread queue in the base class. 

    // FP2b.1: DONE: the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. 
    // FP2b.2: DONE: use the thread queue in the base class (TrafficObject) to do this 

    // launch drive function in a thread
    // NC Note: threads is a protected variable in TrafficObject base class, just like in Vehicle
    //          We are calling the cycleThroughPhases() private member method on "this" TrafficLight 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));    
}

// Generate a positive integer number between minOut and maxOut, cast to a double
// Based on code example: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
double randomTimeInMS(int minOut, int maxOut){
    if ((minOut > 0) && (maxOut > 0) && (minOut<10000) && (maxOut<10000) && (minOut<maxOut))
    {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(minOut, maxOut);
        return (double)dis(gen);
    }
    // if input is invalid, return 5 seconds => 5000 ms 
    return 5000.0;
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4-6s. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 

    // FP2a.1: TODO: Implement the function with an infinite loop that measures the time between two loop cycles 
    // FP2a.2: TODO: and toggles the current phase of the traffic light between red and green 
    // FP2a.3: TODO: and sends an update method to the message queue using move semantics. 
    // FP2a.4: TODO: The cycle duration should be a random value between 4-6s. 
    // FP2a.5: TODO: the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 

    // NC Notes
    // -> The Vehicle also runs an infinite loop. We will base this on code from Vehicle. 
    // -> Compare states (STEPs/BLOCKs) with that of the Vehicle::drive() loop

    // initalize variables
    // should we start the light green or red??
    double cycleDuration = randomTimeInMS(4000,6000);; // duration of a single simulation cycle in ms
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    // STEP/BLOCK 1: init stop watch
    lastUpdate = std::chrono::system_clock::now();
    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // STEP/BLOCK 2:  compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeSinceLastUpdate >= cycleDuration)
        {
            // STEP/BLOCK 3: toggle between red and green 



            // STEP/BLOCK 4: send update message to queue, that is to inform the intersection
            //               that the light is now green or red and thus cars can be allowed, or not!



            // STEP/BLOCK 5: reset stop watch for next cycle
            lastUpdate = std::chrono::system_clock::now();
            
            // assign a new random value between 4s and 6s for next cycle duration 
            cycleDuration = randomTimeInMS(4000,6000);
        }
    } // eof simulation loop
}