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
#include <numeric> 




// A structure to represent the number of participants and races in the racing simulation.
struct Racer {
    int numParticipants;
    int numRaces;
};

// Global Variable race count to keep tracking of how many races
int raceCount = 0;
bool checkRightSpot(std::vector<int>::size_type racer_index, std::vector<int>& raceRanks, int time);
int restartNumber;
Racer temp;

/**
 * Displays the winners of a race, sorted by their race times.
 *
 * This function fills a vector with indices of racers, sorts it based on their race times,
 * and prints the winners for the current race. The race number is incremented after each call.
 *
 * @param raceRanks A vector of race times for each racer.
 */
void displayWinners(const std::vector<int>& raceRanks) {
    std::vector<int> sortedRacers(raceRanks.size());
    std::iota(sortedRacers.begin(), sortedRacers.end(), 0);
     std::cout << "Race " << raceCount << ": ";
    for (const auto &racer : sortedRacers) {
        std::cout << racer << ", ";
    }
    std::cout << std::endl;
    raceCount++;
}

/**
 * Simulates a series of races with multithreading, updating race rankings and displaying winners.
 * @param race The race configuration, including the number of participants and races.
 */
void doRace(const struct Racer race) {
    std::vector<std::thread> threads;
    std::vector<int> raceRanks(static_cast<std::vector<int>::size_type>(race.numParticipants), 0);
     // Initialize raceRanks with initial values
    std::mutex rankMutex;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> raceTime(1, 10); 
    // Nested for loop to simulate races
    for (int raceNumber = 0; raceNumber < race.numRaces; raceNumber++) {
        // Racer goes until < numParticipants
        bool shouldRestart = false;
        
        for (int racer = 0; racer < race.numParticipants; racer++) {
            if (shouldRestart) {
                racer = 0;
                shouldRestart = false;

            }
            threads.emplace_back([racer, &raceRanks, &rankMutex, raceNumber, &gen, &raceTime, race, &shouldRestart]() {
                int time = raceTime(gen);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::vector<int>::size_type racer_index = static_cast<std::vector<int>::size_type>(racer);
                
                rankMutex.lock();
                if (checkRightSpot(racer_index, raceRanks,time)) {
                    raceRanks[racer_index] = racer_index;
                } else {
                    shouldRestart = true;
                    restartNumber = raceNumber;
                }
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

bool checkRightSpot(std::vector<int>::size_type racer_index, std::vector<int>& raceRanks, int time) {
      
       for (int j = racer_index; j < raceRanks.size(); j++) {
        if (time < raceRanks.at(j)) {
            return true;
        }
       }
       return true;
}






// Main method processes input from the target, and then we do cool things with it.
int main(int argc, char* argv[]) {
    raceCount = 0;
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
    