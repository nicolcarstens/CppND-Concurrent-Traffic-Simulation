#include <iostream>
#include <chrono>
#include "TrafficObject.h"

// init static variable
int TrafficObject::_idCnt = 0;

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
    // Task L1.1 : Set up a thread barrier that ensures that all the thread objects in the member vector _threads are joined.

    // For syntax see: 
    // https://stackoverflow.com/questions/409348/iteration-over-stdvector-unsigned-vs-signed-index-variable

    for (auto &t : _threads){
        t.join();
    };
}
