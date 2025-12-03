#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>

//we will use this struct to hold trajectory points and time
struct Point{
    double x;
    double y;
    double time;
};

//function to solve for low angle given initial velocity, range, and gravity.
bool solveLowAngle(double v0, double range, double g, double &angleRad);
//function to calculate trajectory points
std::vector<Point> calculateTrajectory(double v0, double angleRad, double g, double steps);


#endif