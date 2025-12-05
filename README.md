# Ballistics Trajectory Solutions

A multi-language ballistics trajectory system that calculates the angle a shooter needs to take in order to hit a target however meters away, distance is inputted by the user. The system calculates firing angles, generates projectile motion data, validates the solution through logical rules, and produces visualizations of the resulting trajectory. 


## Description 

The software uses a simplified projectile-motion model with a constant gravity and no air resistance assumption. After users choose a cartridge from a preset list and enter a target distance, the program determines the low-angle firing solution, calculates the trajectory points, and outputs them to two files trajectory.csv and solution.pl.

## Getting Started

### Dependencies
- **C++** performs the numerical calculations
- **Prolog** verifies the computed solution using logical rules
- **Python** uses matplotlib to plot the final trajectory
- **Operating Systems**: Windows, Linux, MacOS

### Installing
1. **Clone the repository:**
```
  https://github.com/TheRock2000/CS-396_Cross_language_Ballistics_Trajectory
```
2.  **Navigate to the Project Directory:**
```
   cd CS-396_Cross_language_Ballistics_Trajectory
```

## Authors
- Chris Son (cks@nau.edu)
- Vikram Singh (vs679@nau.edu)
- Rique Yazzie (rty7@nau.edu)

## License
This project is licensed under the MIT License - see the ___ file for details.  
