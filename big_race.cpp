// Nicholas McCarty
// CSE 381
// The Big Race

#include <iostream>
#include <thread>

struct Racer {
    int numParticipants;
    int numRaces;
};


void doRace(struct Racer) {
    // The default value for numRaces is 1
}






int main(int argc, char* argv[]) {
    
    if (argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }
    Racer race;
     int numCars;
     numCars = std::stoi(argv[1]);
     int numRaces = (argc == 3) ? std::stoi(argv[2]) : 1;
     race = {numCars, numRaces};

     doRace(race);


    
    
}
    