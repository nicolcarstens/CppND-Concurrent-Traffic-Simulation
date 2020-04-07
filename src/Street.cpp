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

#include <iostream>
#include "Vehicle.h"
#include "Intersection.h"
#include "Street.h"

Street::Street()
{
    _type = ObjectType::objectStreet;
    _length = 1000.0; // in m
}

void Street::setInIntersection(std::shared_ptr<Intersection> in)
{
    _interIn = in;
    in->addStreet(get_shared_this()); // add this street to list of streets connected to the intersection
}

void Street::setOutIntersection(std::shared_ptr<Intersection> out)
{
    _interOut = out;
    out->addStreet(get_shared_this()); // add this street to list of streets connected to the intersection
}
