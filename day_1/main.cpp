#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string INPUT_FILE_NAME = "input.txt";
const int INPUT_SIZE = 2000;
int inputs[INPUT_SIZE];

void readData() {
    ifstream inFile(INPUT_FILE_NAME.c_str());

    if (inFile.is_open())  
    {
        for (int i = 0; i < INPUT_SIZE; i++) 
        {
            inFile >> inputs[i];
        }

        inFile.close(); // CLose input file
    }
    else { //Error message
        cerr << "Can't find input file " << INPUT_FILE_NAME << endl;
    }
}

int findAmountOfIncreases() 
{
    int count = 0;

    for (int i = 1; i < INPUT_SIZE; i++) 
    {
        if (inputs[i] > inputs[i-1])
        {
            count++;
        }
    }

    return count;
}

int findAmountOfSlidingWindowIncreases() 
{
    int count = 0;

    for (int i = 2; i < INPUT_SIZE-1; i++) 
    {
        int window1 = inputs[i-2] + inputs[i-1] + inputs[i];
        int window2 = inputs[i-1] + inputs[i] + inputs[i+1];
        if (window2 > window1)
        {
            count++;
        }
    }

    return count;
}

int main()
{
    readData();
    cout << findAmountOfIncreases() << endl;
    cout << findAmountOfSlidingWindowIncreases() << endl;
    return 0;
}