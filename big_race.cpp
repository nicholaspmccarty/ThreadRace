// Nicholas McCarty
// CSE 381
// The Big Race

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

struct Racer {
    int numParticipants;
    int numRaces;
};


void doRace(const struct Racer race) {
    std::vector<std::thread> threads;
    std::vector<int> raceRanks;
    std::mutex rankMutex;

    for (size_t raceNumber = 0; raceNumber < race.numRaces; raceNumber++) {
        std::cout << "Race Number: " << raceNumber << std::endl;

        for (size_t racer = 0; racer <= race.numParticipants; racer++) {
            threads.emplace_back([racer, &raceRanks, &rankMutex, raceNumber]() {

            });
        }
    }
    
}






int main(int argc, char* argv[]) {
    if (argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }
    // Local Racer Structure - helps group data into a single unit. 
    Racer race;
     int numCars;
     numCars = std::stoi(argv[1]);
     // Default value for numRaces == 1
     int numRaces = (argc == 3) ? std::stoi(argv[2]) : 1;
     race = {numCars, numRaces};
    std::cout << "Number of Participants: " << race.numParticipants << std::endl;
    std::cout << "Number of Races: " << race.numRaces << std::endl;
     doRace(race);


    
    
}
    