#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Board {
    private:
        int board[5][5];
        int marked[5][5];
        int lastNumber;
        bool completed;
    public:
        Board(){}

        Board(int cboard[5][5]) {
            copy(&cboard[0][0], &cboard[0][0]+25, &board[0][0]);
            lastNumber = 0;
            completed = false;
            for (int i=0;i<5;i++)
            {
                for (int j=0;j<5;j++)
                {
                    marked[i][j] = 0;
                }
            }
        }

        void mark(int number) {
            lastNumber = number;
            for (int i=0;i<5;i++)
            {
                for (int j=0;j<5;j++)
                {
                    if (board[i][j] == number)
                    {
                        marked[i][j] = 1;
                    }
                }
            }
        }

        bool checkIfCompletedOnce() {
            if (!completed && checkIfCompleted()) 
            {
                completed = true;
                return true;
            }
            return false;
        }


        bool checkIfCompleted() {
            for (int i=0;i<5;i++)
            {
                int c = 0;
                for (int j=0;j<5;j++)
                {
                    c += marked[i][j];
                }
                if (c == 5)
                {
                    return true;
                }
            }

            for (int i=0;i<5;i++)
            {
                int c = 0;
                for (int j=0;j<5;j++)
                {
                    c += marked[j][i];
                }
                if (c == 5)
                {
                    return true;
                }
            }

            return false;
        }

        void printBoard() {
            for (int i=0;i<5;i++)
            {
                for (int j=0;j<5;j++)
                {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
        }

        void printMarked() {
            for (int i=0;i<5;i++)
            {
                for (int j=0;j<5;j++)
                {
                    cout << marked[i][j] << " ";
                }
                cout << endl;
            }
        }

        int calculateScore() {
            int unmarkedSum = 0;
            for (int i=0;i<5;i++)
            {
                for (int j=0;j<5;j++)
                {
                    if (marked[i][j] == 0)
                    {
                        unmarkedSum += board[i][j];
                    }
                }
            }
            return lastNumber * unmarkedSum;
        }

};

const string INPUT_FILE_NAME = "input.txt";
int numbers[100];
Board boards[100];

void readData() {
    ifstream inFile(INPUT_FILE_NAME.c_str());

    string numberRow;
    inFile >> numberRow;

    stringstream ss(numberRow);
    int j = 0;
    for (int i; ss >> i;) 
    {
        numbers[j] = i;
        j++;    
        if (ss.peek() == ',')
            ss.ignore();
    }

    int a,b,c,d,e,i=0;
    int tmpBoard[5][5];
    while (inFile >> a >> b >> c >> d >> e)
    {   
        tmpBoard[i%5][0] = a;
        tmpBoard[i%5][1] = b;
        tmpBoard[i%5][2] = c;
        tmpBoard[i%5][3] = d;
        tmpBoard[i%5][4] = e;
        
        if (i%5==4)
        {
            boards[i/5] = Board(tmpBoard);
        }
        i++;
    }

}


void runPartOne() 
{
    Board board;
    for (int i=0;i<100;i++)
    {
        for (int j=0;j<100;j++)
        {
            boards[j].mark(numbers[i]);
            if (boards[j].checkIfCompleted())
            {
                board = boards[j];
                goto endloop;
            }
        }
    }

endloop:
    cout << "Part one: " << board.calculateScore() << endl;
}

void runPartTwo() 
{
    Board board;
    int finishedBoards = 0;

    for (int i=0;i<100;i++)
    {
        for (int j=0;j<100;j++)
        {
            boards[j].mark(numbers[i]);
            if (boards[j].checkIfCompletedOnce())
            {
                finishedBoards++;
            }
            if (finishedBoards == 100)
            {
                board = boards[j];
                goto endloop;
            }
        }
    }

endloop:
    cout << "Part two: " << board.calculateScore() << endl;
}

int main()
{
    readData();
    runPartOne();
    readData();
    runPartTwo();
    return 0;
}