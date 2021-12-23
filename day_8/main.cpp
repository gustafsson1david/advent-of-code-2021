#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

const string INPUT_FILE_NAME = "input.txt";

string digits[200][4];
string testDigits[200][10];

int overlap(string s1, string s2) 
{

    int overlap = 0;
    for (int i=0; i<s1.length(); i++)
    {
       for (int j=0; j<s2.length(); j++)
        {
            if (s1[i] == s2[j])
            {
                overlap++;
            }
        } 
    }
    return overlap;
}

void readData() 
{
    ifstream inFile(INPUT_FILE_NAME.c_str());

    int readDigits = -1;
    int readTestDigits = 0;
    for (int i=0; i<(15*200); i++)
    {
        string s;
        inFile >> s;

        if (readDigits >= 4)
        {
            readDigits = -1;
        }

        if (readDigits != -1)
        {
            digits[i/15][readDigits] = s;
            readDigits++;
        }

        if (s == "|")
        {
            readDigits = 0;
            readTestDigits = 0;
        } else if (readDigits == -1)
        {
            testDigits[i/15][readTestDigits] = s;
            readTestDigits++;
        }
    }
}

void runPartOne()
{
    int count = 0;

    for (int i=0; i<200; i++)
    {
        for (int j=0; j<4; j++)
        {   
            int l = digits[i][j].length();
            if ((l == 2) | (l == 7) | (l == 3) | (l == 4))
            {
                count++;
            }
        }
    }
    cout << "Part 1: " << count << endl;
}

void runPartTwo()
{
    int sum = 0;
    for (int i=0; i<200; i++)
    {
        string numbers[10];
        for (int j=0; j<10; j++)
        {
            int l = testDigits[i][j].length();
            if (l == 2)
            {
                numbers[1] = testDigits[i][j];
            } else if (l == 3)
            {
                numbers[7] = testDigits[i][j];
            } else if (l == 4)
            {
                numbers[4] = testDigits[i][j];
            } else if (l == 7)
            {
                numbers[8] = testDigits[i][j];
            }
        }

        for (int j=0; j<10; j++)
        {
            int l = testDigits[i][j].length();
            if (l == 6)
            {
                if (overlap(numbers[1], testDigits[i][j]) == 1) 
                {
                    numbers[6] = testDigits[i][j];
                } else if (overlap(numbers[4], testDigits[i][j]) == 4)
                {
                    numbers[9] = testDigits[i][j];
                } else
                {
                   numbers[0] = testDigits[i][j];
                }
            }

            if (l == 5)
            {
                if (overlap(numbers[1], testDigits[i][j]) == 2) 
                {
                    numbers[3] = testDigits[i][j];
                } else if (overlap(numbers[4], testDigits[i][j]) == 3)
                {
                    numbers[5] = testDigits[i][j];
                } else
                {
                   numbers[2] = testDigits[i][j];
                }
            }

        }



        int n = 0;
        for (int j=0; j<4; j++)
        {
            for (int k=0; k<10; k++)
            {
                if (digits[i][j].length() == numbers[k].length() & digits[i][j].length() == overlap(digits[i][j], numbers[k]))
                {
                    n += (pow(10, 3-j) * k);
                }
            }
        }

        sum += n;
    }
    cout << "Part 2: " << sum << endl;
}


int main()
{
    readData();
    runPartOne();
    runPartTwo();
    return 0;
}