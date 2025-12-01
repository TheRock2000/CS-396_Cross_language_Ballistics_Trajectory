#ifndef CARTIDGES_H
#define CARTIDGES_H

#include <string>
#include <vector>

struct Cartridge{
    std::string brand;
    std::string line;
    std::string caliber; // in mm
    double muzzleVelocity; // in f/s
};

std::vector<Cartridge> getCartridges();

#endif