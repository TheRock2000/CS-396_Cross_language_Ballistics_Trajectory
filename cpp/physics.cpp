#include "physics.h"
#include <cmath>

//our constant
const double PI = 3.14159265358979323846;

//function to solve for low angle given initial velocity, range, and gravity.
//Output to angleRad by reference. Returns true if solution exists, false otherwise.
//v0 - muzzle velocity
//range - horizontal distance to target
//g - acceleration due to gravity
//angleRad - output angle in radians
//
//
//      Using the formula: range = (v0^2 * sin(2*theta)) / g
//      Rearranged to solve for theta: 0 = .5 * arcsin((g * range) / (v0^2))
//
//
bool solveLowAngle(double v0, double range, double g, double &angleRad){
    
    //sin(2θ)
    double sin2theta = (g * range) / (v0 * v0);

    if(sin2theta > 1.0 || sin2theta < 0.0){
        return false; //No solution
    }

    
    double twoTheta = asin(sin2theta);  //2θ in radians
    angleRad = twoTheta / 2.0;          //θ in radians
    return true; //Solution found
}

//function to calculate trajectory points
//v0 - initial velocity
//angleRad - launch angle in radians
//g - acceleration due to gravity
//steps - number of points to calculate
std::vector<Point> calculateTrajectory(double v0, double angleRad, double g, double steps){
    
    //Vector to hold trajectory points
    std::vector<Point> trajectoryPoints;
    //trajectoryPoints.reserve(steps + 1);

    //Calculate horizontal and vertical velocity components
    double horizontalVelocity = v0 * cos(angleRad);
    double verticalVelocity = v0 * sin(angleRad);

    //Calculate total flight time
    double timeOfFlight = (2 * verticalVelocity) / g;

    //Time increment per step
    double timeIncrement = timeOfFlight / steps;
    
    //Calculate trajectory points at each time step
    for(int stepIndex = 0; stepIndex <= steps; stepIndex++){
        
        //update time
        double currentTime = stepIndex * timeIncrement;
        //Calculate x and y positions
        double xPosition = horizontalVelocity * currentTime;
        double yPosition = (verticalVelocity * currentTime) - (0.5 * g * currentTime * currentTime);

        if(yPosition < 0) yPosition = 0; //default 0, projectile has hit ground

        trajectoryPoints.push_back({xPosition, yPosition, currentTime});    //push point to vector
    }

    //return the vector of trajectory points
    return trajectoryPoints;
}
