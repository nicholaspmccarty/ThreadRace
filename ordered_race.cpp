#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>
#include <algorithm>

// A structure to represent the number of participants and races in the racing simulation.
struct Racer {
    int numParticipants;
    int numRaces;
};

// Global Variable race count to keep tracking of how many races
int raceCount = 0;
int restartNumber = 0;
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
 * @param race The race configuration, including the number of participants and races. Ensures order ane makes sure it is correct.
 */
void doRace(const struct Racer race) {
    std::vector<std::thread> threads;
    std::vector<int> raceRanks(static_cast<std::vector<int>::size_type>(race.numParticipants), 0);
    // Initialize raceRanks with initial values
    std::mutex rankMutex;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> raceTime(1, 10);
    bool shouldRestart;
    // Simulate races
    for (int raceNumber = 0; raceNumber < race.numRaces; raceNumber++) {
        for (int racer = 0; racer < race.numParticipants; racer++) {
             if (shouldRestart) {
                racer = restartNumber;
                shouldRestart = false;

            }
            threads.emplace_back([racer, &raceRanks, &rankMutex, &gen, &raceTime, &race, &shouldRestart, raceNumber]() { 
            int time = raceTime(gen);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::vector<int>::size_type racer_index = static_cast<std::vector<int>::size_type>(racer);
            rankMutex.lock();
            if (racer_index > 0 && raceRanks[racer_index] < raceRanks[racer_index - 1]) {
                raceRanks[racer_index] = raceRanks[racer_index - 1];
            } else {
                    shouldRestart = true;
                    restartNumber = raceNumber;
            }
            rankMutex.unlock();

            if (racer == (race.numParticipants - 1)) {
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
    