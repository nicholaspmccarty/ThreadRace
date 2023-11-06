// Nicholas McCarty
// CSE 381
// The Big Race

#include <iostream>
#include <thread>







int main(int argc, char* argv[]) {
    
    if (argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }

     int numCars, numRaces;
     (void) numRaces;
     if (argc == 2) {
        numCars = std::stoi(argv[1]);
        
     } else {
        numCars = std::stoi(argv[1]);
        numRaces = std::stoi(argv[2]);
     }


    
    
}
    