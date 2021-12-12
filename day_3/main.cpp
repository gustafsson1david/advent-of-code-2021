#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

const string INPUT_FILE_NAME = "input.txt";

void runPartOne() {
    ifstream inFile(INPUT_FILE_NAME.c_str());

    string bits;
    int bitsCount[12] = {0};

    while (inFile >> bits)
    {
        for (int i=0; i<12; i++)
        {
            if (bits[i] == '0') {
                bitsCount[i]--;
            } else {
                bitsCount[i]++;
            }
        }
    }

    string gammaBits= "000000000000";
    string epsilonBits = "000000000000";
    long gamma = 0, epsilon = 0;


    for (int i=0; i<12; i++)
    {
        if (bitsCount[i] < 0) {
            gammaBits[i] = '0';
            epsilonBits[i] = '1';
            epsilon += pow(2, (11-i));
        } else {
            gammaBits[i] = '1';
            gamma += pow(2, (11-i));
            epsilonBits[i] = '0';
        }
    }

    cout << "Gamma | Bits: " << gammaBits << ", Value: " << gamma << endl;
    cout << "Epsilon | Bits: " << epsilonBits << ", Value: " << epsilon << endl;
    cout << "Product: " << gamma*epsilon << endl;
}

void runPartTwo() {
    ifstream inFile(INPUT_FILE_NAME.c_str());

    string inputs[1000];
    for (int i=0; i < 1000; i++)
    {
        inFile >> inputs[i];
    }

    string maxBits[1000];
    copy(begin(inputs), end(inputs), begin(maxBits));
    int maxBitsCount = 1000;

    for (int i=0; (i<12 && maxBitsCount!=1); i++) 
    {
        string zeroBitsTemp[1000];
        string oneBitsTemp[1000];
        int zeroBitsCount = 0;
        int oneBitsCount = 0;

        for (int j=0;j<maxBitsCount; j++)
        {
            if (maxBits[j][i] == '0')
            {
                zeroBitsTemp[zeroBitsCount] = maxBits[j];
                zeroBitsCount++;
            } else {
                oneBitsTemp[oneBitsCount] = maxBits[j];
                oneBitsCount++;
            }
        }

        if (oneBitsCount >= zeroBitsCount) {
            copy(begin(oneBitsTemp), end(oneBitsTemp), begin(maxBits));
            maxBitsCount = oneBitsCount;
        } else {
            copy(begin(zeroBitsTemp), end(zeroBitsTemp), begin(maxBits));
            maxBitsCount = zeroBitsCount;
        }
    }

    string minBits[1000];
    copy(begin(inputs), end(inputs), begin(minBits));
    int minBitsCount = 1000;

    for (int i=0; (i<12 && minBitsCount!=1); i++) 
    {
        string zeroBitsTemp[1000];
        string oneBitsTemp[1000];
        int zeroBitsCount = 0;
        int oneBitsCount = 0;

        for (int j=0;j<minBitsCount; j++)
        {
            if (minBits[j][i] == '0')
            {
                zeroBitsTemp[zeroBitsCount] = minBits[j];
                zeroBitsCount++;
            } else {
                oneBitsTemp[oneBitsCount] = minBits[j];
                oneBitsCount++;
            }
        }

        if (oneBitsCount < zeroBitsCount) {
            copy(begin(oneBitsTemp), end(oneBitsTemp), begin(minBits));
            minBitsCount = oneBitsCount;
        } else {
            copy(begin(zeroBitsTemp), end(zeroBitsTemp), begin(minBits));
            minBitsCount = zeroBitsCount;
        }
    }

    string oxygenBits = minBits[0];
    string co2Bits = maxBits[0];
    long oxygen = 0, co2=0;
    
    for (int i=0; i<12; i++)
    {
        if (oxygenBits[i] == '1') {
            oxygen += pow(2, (11-i));
        }
        if (co2Bits[i] == '1') {
            co2 += pow(2, (11-i));
        }
    }

    cout << "Oxygen | Bits: " << oxygenBits << ", Value: " << oxygen << endl;
    cout << "CO2 | Bits: " << co2Bits << ", Value: " << co2 << endl;
    cout << "Product: " << oxygen*co2 << endl;
}

int main()
{
    runPartOne();
    runPartTwo();
    return 0;
}