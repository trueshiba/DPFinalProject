//
// Created by Alison Gilpatrick
//
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace std::chrono;

float agilRand(int sensitivity);

int main() {
    int sensitivity = 1000;

    std::cout << agilRand(sensitivity) << std::endl;

    return 0;
}

// Randomize an index for the vector
float agilRand(int sensitivity) {
    // Generate a random number
    int r1 = rand() / float(sensitivity);
    cout << "r1: " << r1 << endl;

    // Generate another random number by modding milliseconds by r1
    milliseconds ms = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
    );
    int r2 = ms.count() % r1;
    cout << "r2: " << r2 << endl;

    // Return the average of the two (# between 0 and 1)
    float randNum = float(r1 - r2) / float(r1);

    return randNum;
}


