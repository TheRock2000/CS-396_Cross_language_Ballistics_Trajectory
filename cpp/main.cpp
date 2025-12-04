#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "cartridges.h"
#include "physics.h"

//gravity constant, in m/s²
const double GRAVITY = 9.76398; 
const std::string TRAJECTORY_DATA_PATH = "../data/trajectory.csv";
const std::string SOLUTION_PL_PATH = "../prolog/solution.pl";


// helper function to write trajectory points to CSV
void writeCSV(const std::vector<Point> &points, const std::string &path){

    //open file
    std::ofstream out(path);

    //check if file opened successfully
    if(!out){
        std::cerr << "Error: Could not open" << path << " for writing.\n"; 
        return;
    }

    //write to file
    out << "x,y,time\n";                                   //write header
    out << std::fixed << std::setprecision(6);             //set precision for floating point numbers
    for (const auto &p : points){                          //write each point            
        out << p.x << "," << p.y << "," << p.time << "\n"; //write point and time data
    }

    //file will be closed automatically when out goes out of scope
}

//helper function to write Prolog solution file
void writeSolutoinPL(const Cartridge &cartridge, double range, double angleRad, const std::string &path){

    //open file
    std::ofstream out(path);

    //check if file opened successfully
    if(!out){
        std::cerr << "Error: Could not open" << path << " for writing.\n";
        return;
    }

    // convert angle to degrees from radians
    double angleDeg = angleRad * (180.0 / M_PI);
    
    //write to file solution data: cartridge caliber, muzzle velocity, range, angle in degrees
    out << "solution(\n"
    << "  cartridge('" << cartridge.caliber << "'),\n"
    << "  v0(" << std::fixed << std::setprecision(6) << cartridge.muzzleVelocity << "),\n"
    << "  range(" << range << "),\n"
    << "  angle_deg(" << angleDeg << "),\n"
    << "  status(ok_physics)\n"
    << ").\n";
    
    //file will be closed automatically when out goes out of scope
}

//helper function to write Prolog solution file of a failed physics check
void writeSolutionPL_NoPhysics(const Cartridge &cartridge, 
                                double range, 
                                const std::string &path){

    //open file
    std::ofstream out(path);

    //check if file opened successfully
    if(!out){
        std::cerr << "Error: Could not open" << path << " for writing.\n";
        return;
    }
    
    //write to file solution data: cartridge caliber, muzzle velocity, range, none as angle
    out << "solution(\n"
    << "  cartridge('" << cartridge.caliber << "'),\n"
    << "  v0(" << std::fixed << std::setprecision(6) << cartridge.muzzleVelocity << "),\n"
    << "  range(" << range << "),\n"
    << "  angle_deg(none),\n"
    << "  status(no_physics_solution)\n"
    << ").\n";
    
    //file will be closed automatically when out goes out of scope
}

int main(){
    //get available cartridges
    auto cartridges = getCartridges();
    

    //User input Menu
    //1. display available cartridges
    std::cout << "Select a cartridge:\n";
    for(std::size_t i = 0; i < cartridges.size(); ++i){
        std::cout << "  " << (i + 1) << ") " << cartridges[i].caliber
                  << "  (v0 = " << cartridges[i].muzzleVelocity << " m/s)\n";
    }

    //2. select cartridge
    std::size_t choice;
    std::cout << "Enter choice number: ";
    std::cin >> choice;

    if(choice == 0 || choice > cartridges.size()){
        std::cerr << "Invalid choice.\n";
        return 1;
    }

    const Cartridge &c = cartridges[choice - 1];

    //3. input target range
    double range;
    std::cout << "Enter target distance in meters (horizontal): ";
    std::cin >> range;

    if(range <= 0){
        std::cerr << "Range must be positive.\n";
        return 1;
    }

    //solve for low-angle firing solution
    double angleRad;

    //call physics function to solve for angle, save result in angleRad using pointers
    //produces csv file if solution found and is physically valid
    if(!solveLowAngle(c.muzzleVelocity, range, GRAVITY, angleRad)){
        std::cerr << "No physically valid low-angle solution for this cartridge and range.\n";
        std::cerr << "Run Prolog to validate the solution.\n";
        //still write a solution.pl indicating failure
        writeSolutionPL_NoPhysics(c, range, SOLUTION_PL_PATH);
        return 0;   //end main
    }
    else{
        //convert angle to degrees for display
        double angleDeg = angleRad * 180.0 / M_PI;
        std::cout << "Firing solution (no drag): angle = " << angleDeg << " degrees.\n";

        // Compute and write trajectory, steps in 200 increments
        auto points = calculateTrajectory(c.muzzleVelocity, angleRad, GRAVITY, 200);

        //write CSV file to path
        writeCSV(points, TRAJECTORY_DATA_PATH);

        // Write Prolog solution file
        writeSolutoinPL(c, range, angleRad, SOLUTION_PL_PATH);
        std::cout << "Trajectory written to ../data/trajectory.csv\n";
        std::cout << "Solution written to ../prolog/solution.pl\n";
        std::cout << "Now run Prolog to validate the solution.\n";

        return 0; //end main
    }
}
