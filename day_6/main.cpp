#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const string INPUT_FILE_NAME = "input.txt";
int numbers[300];

void readData() 
{
    ifstream inFile(INPUT_FILE_NAME.c_str());

    string row;
    inFile >> row;

    stringstream ss(row);
    int j = 0;
    for (int i; ss >> i;) 
    {
        numbers[j] = i;
        j++;    
        if (ss.peek() == ',')
            ss.ignore();
    }
}

void runPartOne()
{
    int count[7] = {0};
    int firstGenerationCount[9] = {0};

    for (int i=0; i<300; i++)
    {
        count[numbers[i]]++;
    }


    for (int i=0; i<80; i++)
    {   
        int tempCount[7] = {0};
        int tempFirstGenerationCount[9] = {0};
        for (int j=0; j<9; j++)
        {
            if (j >= 7) {
                tempFirstGenerationCount[j-1] = firstGenerationCount[j];
            } else if (j >= 1) {
                tempFirstGenerationCount[j-1] = firstGenerationCount[j];
                tempCount[j-1] = count[j];
            } else {
                tempFirstGenerationCount[8] = count[0] + firstGenerationCount[0];
                tempCount[6] = count[0] + firstGenerationCount[0];
            }
        }
        copy(begin(tempCount), end(tempCount), begin(count));
        copy(begin(tempFirstGenerationCount), end(tempFirstGenerationCount), begin(firstGenerationCount));
    } 

    int totalCount = 0;
    for (int i=0; i<7; i++) {
        totalCount += count[i];
    }
    for (int i=0; i<9; i++) {
        totalCount += firstGenerationCount[i];
    }

    cout << "Part 1: " << totalCount << endl;
}

void runPartTwo()
{
    long count[7] = {0};
    long firstGenerationCount[9] = {0};

    for (int i=0; i<300; i++)
    {
        count[numbers[i]]++;
    }


    for (int i=0; i<256; i++)
    {   
        long tempCount[7] = {0};
        long tempFirstGenerationCount[9] = {0};
        for (int j=0; j<9; j++)
        {
            if (j >= 7) {
                tempFirstGenerationCount[j-1] = firstGenerationCount[j];
            } else if (j >= 1) {
                tempFirstGenerationCount[j-1] = firstGenerationCount[j];
                tempCount[j-1] = count[j];
            } else {
                tempFirstGenerationCount[8] = count[0] + firstGenerationCount[0];
                tempCount[6] = count[0] + firstGenerationCount[0];
            }
        }
        copy(begin(tempCount), end(tempCount), begin(count));
        copy(begin(tempFirstGenerationCount), end(tempFirstGenerationCount), begin(firstGenerationCount));
    } 

    long totalCount = 0;
    for (int i=0; i<7; i++) {
        totalCount += count[i];
    }
    for (int i=0; i<9; i++) {
        totalCount += firstGenerationCount[i];
    }

    cout << "Part 2: " << totalCount << endl;
}


int main()
{
    readData();
    runPartOne();
    runPartTwo();
    return 0;
}