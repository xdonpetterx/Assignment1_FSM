#pragma once
#include <random>

int RandomInteger(int fromNumber, int toNumber){
    // Create a random number generator
    std::random_device randomDevice;
    std::mt19937 nrGenerator(randomDevice());
    std::uniform_int_distribution<int> distribution(fromNumber, toNumber);

    // Generate a random number between 0 and 1
    int random_integer_number = distribution(nrGenerator);

    return random_integer_number;
}