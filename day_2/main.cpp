#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string INPUT_FILE_NAME = "input.txt";

void runPartOne() {
    ifstream inFile(INPUT_FILE_NAME.c_str());

    string command;
    int value;

    int depthValue = 0;
    int horizontalValue = 0;

    while (inFile >> command >> value)
    {
        if (command == "forward") {
            horizontalValue += value;
        } else if (command == "down") {
            depthValue += value;
        } else if (command == "up") {
            depthValue -= value;
        }
    }

    cout << "Depth: " << depthValue;
    cout << ", Horizontal: " << horizontalValue;
    cout << ", Product: " << depthValue*horizontalValue << endl;
}

void runPartTwo() {
    ifstream inFile(INPUT_FILE_NAME.c_str());

    string command;
    int value;

    int depthValue = 0;
    int horizontalValue = 0;
    int aimValue = 0;

    while (inFile >> command >> value)
    {
        if (command == "forward") {
            horizontalValue += value;
            depthValue += (aimValue * value);
        } else if (command == "down") {
            aimValue += value;
        } else if (command == "up") {
            aimValue -= value;
        }
    }

    cout << "Depth: " << depthValue;
    cout << ", Horizontal: " << horizontalValue;
    cout << ", Product: " << depthValue*horizontalValue << endl;
}

int main()
{
    runPartOne();
    runPartTwo();
    return 0;
}