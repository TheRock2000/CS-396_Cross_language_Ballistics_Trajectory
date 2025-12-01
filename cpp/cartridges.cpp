#include "cartridges.h"

std::vector<Cartridge> getCartridges(){
    return {
        {"Winchester", "Target & Practice", "7.62x39", 2355.0},
        {"Hornady", "Traditional/FMJ", "5.56x45", 3240.0},
        {"SigSauer", "Elite Ball", "7.62x51", 2900.0}
    };
}