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
bool solveLowAngle(double v0, double range, double g, double &angleRad){
    double sin2theta = (g * range) / (v0 * v0);

    if(sin2theta > 1.0 || sin2theta < 0.0){
        return false; //No solution
    }

    double twoTheta = asin(sin2theta);
    angleRad = twoTheta / 2.0;
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

    double horizontalVelocity = v0 * cos(angleRad);
    double verticalVelocity = v0 * sin(angleRad);

    //Calculate total flight time
    double timeOfFlight = (2 * verticalVelocity) / g;

    //Time increment per step
    double timeIncrement = timeOfFlight / steps;
    
    for(int stepIndex = 0; stepIndex <= steps; stepIndex++){
        
        double currentTime = stepIndex * timeIncrement;
        double xPosition = horizontalVelocity * currentTime;
        double yPosition = (verticalVelocity * currentTime) - (0.5 * g * currentTime * currentTime);

        if(yPosition < 0) yPosition = 0; //Clamp to ground level

        trajectoryPoints.push_back({xPosition, yPosition, currentTime});
    }

    return trajectoryPoints;
}
