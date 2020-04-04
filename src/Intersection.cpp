#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <random>

#include "Street.h"
#include "Intersection.h"
#include "Vehicle.h"

/* Implementation of class "WaitingVehicles" */

int WaitingVehicles::getSize()
{
    return _vehiclesWaiting.size();
}

void WaitingVehicles::pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void> &&promise)
{
    _vehiclesWaiting.push_back(vehicle);
    _promisesAssociated.push_back(std::move(promise));
}


void WaitingVehicles::permitEntryToFirstInQueue()
{
    // Student code START =====================================================

    // method called from Intersection::processVehicleQueue()

    // L2.3 : First, get the entries from the front of _promises and _vehicles. 
    // Then, fulfill promise and send signal back that permission to enter has been granted.
    // Finally, remove the front elements from both queues. 

    // I have renamed _vehicles to _vehiclesWaiting
    //        ... and _promises to _promisesAssociated

    // nothing really to do with the vehicle ... just fulfill the promise?! 

    _promisesAssociated.front().set_value();

    // Finally, remove the front elements from both queues. 
    // see http://www.cplusplus.com/reference/vector/vector/erase/ 
    // Given Vector container, it is not a very efficient way to manage data!
    // List would have been more efficient... 

    _vehiclesWaiting.erase(_vehiclesWaiting.begin());
    _promisesAssociated.erase(_promisesAssociated.begin());

    // Student code ENDS ======================================================
}

/* Implementation of class "Intersection" */

Intersection::Intersection()
{
    _type = ObjectType::objectIntersection;
    _isBlocked = false;
}

void Intersection::addStreet(std::shared_ptr<Street> street)
{
    _streets.push_back(street);
}

std::vector<std::shared_ptr<Street>> Intersection::queryStreets(std::shared_ptr<Street> incoming)
{
    // store all outgoing streets in a vector ...
    std::vector<std::shared_ptr<Street>> outgoings;
    for (auto it : _streets)
    {
        if (incoming->getID() != it->getID()) // ... except the street making the inquiry
        {
            outgoings.push_back(it);
        }
    }

    return outgoings;
}

// adds a new vehicle to the queue and returns once the vehicle is allowed to enter
void Intersection::addVehicleToQueue(std::shared_ptr<Vehicle> vehicle)
{
    std::cout << "Intersection #" << _id << "::addVehicleToQueue: thread id = " << std::this_thread::get_id() << std::endl;

    // Student code START =====================================================

    // L2.2 : First, add the new vehicle to the waiting line by creating a promise, a corresponding future and then adding both to _waitingVehicles. 
    // Then, wait until the vehicle has been granted entry. 

    // Example: https://en.cppreference.com/w/cpp/thread/promise 
    //
    // Demonstrate using promise<int> to transmit a result between threads.
    // std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    // std::promise<int> accumulate_promise;
    // std::future<int> accumulate_future = accumulate_promise.get_future();
    // std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
    //                        std::move(accumulate_promise));

    std::promise<void> promiseV;
    std::future<void> futureV = promiseV.get_future();

    // Definition ==>> WaitingVehicles::pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void> &&promise)
    _waitingVehicles.pushBack(vehicle,std::move(promiseV));

    // wait until the vehicle has been granted entry
    futureV.wait();

    // Student code ENDS ======================================================

    std::cout << "Intersection #" << _id << ": Vehicle #" << vehicle->getID() << " is granted entry." << std::endl;
}

void Intersection::vehicleHasLeft(std::shared_ptr<Vehicle> vehicle)
{
    std::cout << "Intersection #" << _id << ": Vehicle #" << vehicle->getID() << " has left." << std::endl;

    // unblock queue processing
    this->setIsBlocked(false);
}

void Intersection::setIsBlocked(bool isBlocked)
{
    _isBlocked = isBlocked;
    std::cout << "Intersection #" << _id << " isBlocked=" << isBlocked << std::endl;
}

// virtual function which is executed in a thread
void Intersection::simulate() // using threads + promises/futures + exceptions
{
    // launch vehicle queue processing in a thread
    threads.emplace_back(std::thread(&Intersection::processVehicleQueue, this));
}

void Intersection::processVehicleQueue()
{
    // print id of the current thread
    //std::cout << "Intersection #" << _id << "::processVehicleQueue: thread id = " << std::this_thread::get_id() << std::endl;

    // continuously process the vehicle queue
    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // only proceed when at least one vehicle is waiting in the queue
        if (_waitingVehicles.getSize() > 0 && !_isBlocked)
        {
            // set intersection to "blocked" to prevent other vehicles from entering
            this->setIsBlocked(true);

            // permit entry to first vehicle in the queue (FIFO)
            _waitingVehicles.permitEntryToFirstInQueue();
        }
    }
}
