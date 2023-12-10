//
// Created by Alison Gilpatrick
//
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace std::chrono;

float agilRand(int sensitivity);


int main(int argc, char *argv[]) {
    // Parse command-line arguments and call your function

    if (argc > 1) {
        int true_answer = std::stoi(argv[1]) * 1.0;
        int sensitivity = std::stof(argv[2]);

        string sep = " ";
        for (int i = 0; i < 200; i++) {
            cout << (true_answer + agilRand(sensitivity)) << sep;
        }

    } else {
        std::cout << "Usage: " << argv[0] << " <int_param> <int_param> <vec_param>" << std::endl;
    }

    return 0;
}

// Randomize an index for the vector
float agilRand(int sensitivity) {

    srand((time(NULL)));

    // Generate a random number
    int r1 = rand() / float(sensitivity);

    // Generate another random number by modding milliseconds by r1
    milliseconds ms = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
    );
    int r2 = ms.count() % r1;

    // Return the average of the two (# between 0 and 1)
    float randNum = float(r1 - r2) / float(r1);

    return randNum;
}


