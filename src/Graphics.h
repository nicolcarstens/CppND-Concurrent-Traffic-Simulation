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

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include "TrafficObject.h"

class Graphics
{
public:
    // constructor / desctructor

    // getters / setters
    void setBgFilename(std::string filename) { _bgFilename = filename; }
    void setTrafficObjects(std::vector<std::shared_ptr<TrafficObject>> &trafficObjects) { _trafficObjects = trafficObjects; };

    // typical behaviour methods
    void simulate();

private:
    // typical behaviour methods
    void loadBackgroundImg();
    void drawTrafficObjects();

    // member variables
    std::vector<std::shared_ptr<TrafficObject>> _trafficObjects;
    std::string _bgFilename;
    std::string _windowName;
    std::vector<cv::Mat> _images;
};

#endif