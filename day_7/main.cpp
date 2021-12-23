#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const string INPUT_FILE_NAME = "input.txt";
int positions[1000];

void readData() 
{
    ifstream inFile(INPUT_FILE_NAME.c_str());

    string row;
    inFile >> row;

    stringstream ss(row);
    int j = 0;
    for (int i; ss >> i;) 
    {
        positions[j] = i;
        j++;    
        if (ss.peek() == ',')
            ss.ignore();
    }
}

void runPartOne()
{
    int min = positions[0], max = positions[0];
    for (int i = 0; i<1000; i++)
    {
        if (positions[i] < min)
        {
            min = positions[i];
        }

        if (positions[i] > max)
        {
            max = positions[i];
        }
    }

    int lowestCost = 100000000;
    for (int i=min; i<=max; i++)
    {
        int cost = 0;
        for (int j=0; j<1000; j++)
        {
            int c = positions[j] - i;
            if (c > 0)
            {
                cost += c;
            } else
            {
                cost -= c;
            }
        }

        if (cost < lowestCost)
        {
            lowestCost = cost;
        }

    }
    cout << "Part 1: " << lowestCost << endl;
}

void runPartTwo()
{
    int min = positions[0], max = positions[0];
    for (int i = 0; i<1000; i++)
    {
        if (positions[i] < min)
        {
            min = positions[i];
        }

        if (positions[i] > max)
        {
            max = positions[i];
        }
    }

    int lowestCost = 100000000;
    for (int i=min; i<=max; i++)
    {
        int cost = 0;
        for (int j=0; j<1000; j++)
        {
            int c = positions[j] - i;
            if (c < 0)
            {
                c = -c;
            }
            cost += ((c + 1) * c / 2);
        }

        if (cost < lowestCost)
        {
            lowestCost = cost;
        }

    }

    cout << "Part 2: " << lowestCost << endl;
}


int main()
{
    readData();
    runPartOne();
    runPartTwo();
    return 0;
}