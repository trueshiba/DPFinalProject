#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>     /* srand, rand */



using namespace std;
using namespace chrono;

double mish_randomizer(int num, int length) {
    // Variables
    int key = 0;

    // Get the first key for randomization :D
    while (key % 10 == 0) {
        auto now = time_point_cast<microseconds>(system_clock::now());
        key = now.time_since_epoch().count() % 1000;
    }

    // Generate random number
    string random_num = "";
    int saved_key = 0;

    while (random_num.length() < length) {
        key = key * key;

        if (key % 10000 == saved_key) {
            key = ((key % 10000) * num) % 10000;
        } else {
            if (key > 1000000) {
                key = key / 100;
                key = key % 1000;
            } else {
                key = key / 10;
                key = key % 1000;
            }
        }

        // Get a new key
        while (key % 10 == 0) {
            auto now = time_point_cast<microseconds>(system_clock::now());
            key = now.time_since_epoch().count() % 10000;
        }

        saved_key = key;
        random_num.append(to_string(key));
    }
    int offset = rand() % 2;
    return(pow(10.0, length-offset) / stoi(random_num.substr(0, length)));
}

int main(int argc, char *argv[]) {
    // Parse command-line arguments and call your function
    vector<int> inputVector;

    if (argc > 1) {
        int true_answer = std::stoi(argv[1]) * 1.0;
        int epsilon = std::stof(argv[2]);

        string sep = " ";
        for (int i = 0; i < 200; i++) {
            cout << (true_answer + mish_randomizer(epsilon, 9)) << sep;
        }

    } else {
        std::cout << "Usage: " << argv[0] << " <int_param> <int_param> <vec_param>" << std::endl;
    }

    return 0;
}
