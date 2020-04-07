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

#include <algorithm>
#include <iostream>
#include <chrono>
#include "TrafficObject.h"

// init static variable
int TrafficObject::_idCnt = 0;

std::mutex TrafficObject::_mutexCout;  // _mtx and _mutex => horrible names! ensures confusion
                                       // replaced _mtx with _mutexCout

void TrafficObject::setPosition(double x, double y)
{
    _posX = x;
    _posY = y;
}

void TrafficObject::getPosition(double &x, double &y)
{
    x = _posX;
    y = _posY;
}

TrafficObject::TrafficObject()
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
}

TrafficObject::~TrafficObject()
{
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}
