//
// Created by cojas on 12/10/2023.
//
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

long cooperSeed;
int cooperIterator;
long COOPER_SEED_DEFAULT_VAL = 1178536356;
double randSeq(int upperBound);

int main(int argc, char *argv[]) {

    long pSeed = time(NULL);
    int specialNum = 3239;
    pSeed *= specialNum;
    pSeed *= pSeed;

    cooperSeed = abs(pSeed);
    cooperIterator = 1;

    int sensitivity = 1212;

    if (argc > 1) {
        int true_answer = std::stoi(argv[1]) * 1.0;
        int epsilon = std::stof(argv[2]);

        string sep = " ";
        for (int i = 0; i < 200; i++) {
            cout << (true_answer + randSeq(sensitivity)) << sep;
        }

    } else {
        std::cout << "Usage: " << argv[0] << " <int_param> <int_param> <vec_param>" << std::endl;
    }

    return 0;
}


double randSeq(int upperBound) {
    int final, subSeed;
    int begin = 0;
    int specialNum = 3239;

    // sets it to a value 1-9 depending on number of times program has been run
    string replacementNum = to_string(cooperIterator % 9 + 1);

    // If iterator is even number set begin to 1 + the even number modded by 7
    if (cooperIterator % 3 != 0) {
        begin += (cooperIterator % 7);
    }

    // Get a substring of size 3 from the seed dependent on number of runs
    string strSubSeed = to_string(cooperSeed).substr(begin,4);
    int range = 3;
    // runs for loop between 10 - 20 times
    for (int i = 0; i < range; ++i) {

        // check zeros in first and last position of seed to help get better numbers multiplying
        if (strSubSeed[0] == '0') {
            strSubSeed.replace(0,1,replacementNum);
        }
        if (strSubSeed[3] == '0') {
            strSubSeed.replace(3,1,replacementNum);
        }


        // turn 4 digit string to an int
        if (strSubSeed == "") {
            strSubSeed += "1";
        }
        subSeed = stoi(strSubSeed);
        //cout << subSeed << endl;

        // cube seed!
        final = abs((subSeed + specialNum) * subSeed * subSeed);

        // if iterator is divisible by 3 its starts in a dif spot (for fun!)
        if (cooperIterator % 3 == 0) {
            begin = (cooperIterator % 7);
        }

        strSubSeed = to_string(final).substr(begin, 4);
    }

    ++cooperIterator;

    cout << "SubSeed: " << subSeed << endl;

    auto randNum = static_cast<double>(subSeed % upperBound);

    cout << "randNum: " << randNum << endl;

    return (randNum / upperBound);
}
// end of Cooper sort functions