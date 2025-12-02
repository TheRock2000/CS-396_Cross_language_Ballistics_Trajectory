#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "cartridges.h"
#include "physics.h"

const double GRAVITY = 9.76398; //in m/s^2

void writeCSV(const std::vector<Point> &points, const std::string &path){

    std::ofstream out(path);
    if(!out){
        std::cerr << "Error: Could not open" << path << " for writing.\n";
        return;
    }

    out << "x,y,time\n";
    out << std::fixed << std::setprecision(6);
    for (const auto &p : points){
        out << p.x << "," << p.y << "," << p.time << "\n";
    }
}

void writeSolutoinPL(const Cartridge &cartridge, double range, double angleRad, const std::string &path){
    std::ofstream out(path);
    if(!out){
        std::cerr << "Error: Could not open" << path << " for writing.\n";
        return;
    }

    double angleDeg = angleRad * (180.0 / M_PI);
    out << "solution(\n"
        << "  cartridge('" << cartridge.caliber << "'),\n"
        << "  v0(" << std::fixed << std::setprecision(6) << cartridge.muzzleVelocity << "),\n"
        << "  range(" << range << "),\n"
        << "  angle_deg(" << angleDeg << ")\n"
        << ").\n";
    }

int main(){
    auto cartridges = getCartridges();

    std::cout << "Select a cartridge:\n";
    for (std::size_t i = 0; i < cartridges.size(); ++i) {
        std::cout << "  " << (i + 1) << ") " << cartridges[i].caliber
                  << "  (v0 = " << cartridges[i].muzzleVelocity << " m/s)\n";
    }

    std::size_t choice;
    std::cout << "Enter choice number: ";
    std::cin >> choice;

    if (choice == 0 || choice > cartridges.size()) {
        std::cerr << "Invalid choice.\n";
        return 1;
    }

    const Cartridge &c = cartridges[choice - 1];

    double range;
    std::cout << "Enter target distance in meters (horizontal): ";
    std::cin >> range;

    if (range <= 0) {
        std::cerr << "Range must be positive.\n";
        return 1;
    }

    double angleRad;
    if (!solveLowAngle(c.muzzleVelocity, range, GRAVITY, angleRad)) {
        std::cerr << "No physically valid low-angle solution for this cartridge and range.\n";
        // Optionally still write a solution.pl indicating failure, but we’ll just exit.
        return 1;
    }

    double angleDeg = angleRad * 180.0 / M_PI;
    std::cout << "Firing solution (no drag): angle = " << angleDeg << " degrees.\n";

    // Compute and write trajectory
    auto points = calculateTrajectory(c.muzzleVelocity, angleRad, GRAVITY, 200);
    writeCSV(points, "../data/trajectory.csv");

    // Write Prolog solution file
    writeSolutoinPL(c, range, angleRad, "../prolog/solution.pl");
    std::cout << "Trajectory written to ../data/trajectory.csv\n";
    std::cout << "Solution written to ../prolog/solution.pl\n";
    std::cout << "Now run Prolog to validate the solution.\n";

    return 0; //end main
}
