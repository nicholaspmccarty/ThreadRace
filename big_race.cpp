// Nicholas McCarty
// CSE 381
// The Big Race

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>
#include <algorithm>
#include <map>
#include <bits/stdc++.h> 

struct Racer {
    int numParticipants;
    int numRaces;
};

void displayWinners(const std::vector<int> raceRanks) {
    std::unordered_map<int, int> hashMap;
    std::vector<int> ordered; 
    
    for (uint16_t a = 0; a < raceRanks.size(); a++) {
       hashMap[a] = raceRanks[a];
    }
    for (const auto &j : hashMap) {
        std::cout << "Index: " << j.first << " Time: " << j.second << std::endl;
    }

    std::cout << "" << std::endl;


}


void doRace(const struct Racer race) {
    std::vector<std::thread> threads;
    std::vector<int> raceRanks(race.numParticipants, 0); // Initialize raceRanks with initial values
    std::mutex rankMutex;
    auto count = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> raceTime(1, 10); 
    // Nested for loop to simulate races
    for (int raceNumber = 0; raceNumber < race.numRaces; raceNumber++) {
        std::cout << "Race Number: " << raceNumber + 1 << std::endl;
        // Racer goes until < numParticipants
        for (int racer = 0; racer < race.numParticipants; racer++) {
            std::cout << "Racer " << racer << ", Rank " << raceRanks[racer] << ", Race Number " << raceNumber << std::endl;
            threads.emplace_back([racer, &raceRanks, &rankMutex, raceNumber, &gen, &raceTime, race]() {
                int time = raceTime(gen);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                rankMutex.lock();
                raceRanks[racer] = time;
                rankMutex.unlock();
                if (racer == (race.numParticipants-1)) {
                    displayWinners(raceRanks);
                }
            });
        }
    }



    // Wait for all threads to finish
    for (std::thread& thread : threads) {
        thread.join();
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
    