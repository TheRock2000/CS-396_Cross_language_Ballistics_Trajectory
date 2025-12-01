#ifndef TRAJECTORY_H
#define TRAJECTORY_H

struct Point {
    double x;
    double y;
};

Point tracjectoryPoint(double velocity, double angle, double time, double gravity);

#endif