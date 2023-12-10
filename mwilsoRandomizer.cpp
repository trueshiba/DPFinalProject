#include <iostream>
#include <chrono>
#include <string>

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
    return 1.0 / stoi(random_num.substr(0, 9));
}
