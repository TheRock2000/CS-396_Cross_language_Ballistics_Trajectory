#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>

struct Point{
    double x;
    double y;
    double time;
};

bool solveLowAngle(double v0, double range, double g, double &angleRad);
std::vector<Point> calculateTrajectory(double v0, double angleRad, double g, double steps);


#endif