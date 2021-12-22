#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Point
{
    private:
        int x,y;
    public:
        Point(){}

        Point(int cx, int cy)
        {
            x = cx;
            y = cy;
        }

        int getX()
        {
            return x;
        }

        int getY()
        {
            return y;
        }

        void print()
        {
            cout << "(";
            cout << x;
            cout << ",";
            cout << y;
            cout << ")";
        }
};

class Line 
{
    private:
        Point point1, point2;
    public:
        Line(){}

        Line(Point cpoint1, Point cpoint2) 
        {
            point1 = cpoint1;
            point2 = cpoint2;
        }

        void print()
        {
            cout << "(";
            cout << point1.getX();
            cout << ",";
            cout << point1.getY();
            cout << ") -> (";
            cout << point2.getX();
            cout << ",";
            cout << point2.getY();
            cout << ")";
        }

        bool isHorOrVer()
        {
            return point1.getX() == point2.getX() || point1.getY() == point2.getY();
        }

        int calculateHorOrVerSize()
        {
            // Assume it is horizontal or vertical only
            int min, max;

            if (point1.getX() == point2.getX()) {
                if (point1.getY() > point2.getY()){
                    min = point2.getY();
                    max = point1.getY();
                } else
                {
                    min = point1.getY();
                    max = point2.getY();
                }
            } else {
                if (point1.getX() > point2.getX()){
                    min = point2.getX();
                    max = point1.getX();
                } else
                {
                    min = point1.getX();
                    max = point2.getX();
                }
            }

            return max - min + 1;
        }

        Point* calculateHorOrVerPoints(Point* points)
        {
            // Assume it is horizontal or vertical only
            int constant, min, max;

            if (point1.getX() == point2.getX()) {
                constant = point1.getX();
                if (point1.getY() > point2.getY()){
                    min = point2.getY();
                    max = point1.getY();
                } else
                {
                    min = point1.getY();
                    max = point2.getY();
                }

                for (int i=min;i<=max;i++)
                {
                    points[i-min] = Point(constant, i);
                }
                return points;
            } else {
                constant = point1.getY();
                if (point1.getX() > point2.getX()){
                    min = point2.getX();
                    max = point1.getX();
                } else
                {
                    min = point1.getX();
                    max = point2.getX();
                }

                for (int i=min;i<=max;i++)
                {
                    points[i-min] = Point(i, constant);
                }
                return points;
            }
        }

        int calculateDiagonalSize()
        {
            if (point1.getX() > point2.getX()) {
                return point1.getX() - point2.getX() + 1;
            } else {
                return point2.getX() - point1.getX() + 1;
            }
        }

        Point* calculateDiagonalPoints(Point* points)
        {
            int size = calculateDiagonalSize();

            int x = point1.getX(), y = point1.getY();
            int xStep = 1, yStep = 1;
            if (point1.getX() > point2.getX()) {
                xStep = -1;
            }
            if (point1.getY() > point2.getY()) {
                yStep = -1;
            }  

            for (int i=0; i<size; i++)
            {
                points[i] = Point(x,y);
                x += xStep;
                y += yStep;
            }

            return points;
        }
};

class Grid
{
    private:
        int grid[1000][1000];

    public:
        Grid()
        {
            for (int i=0; i<1000; i++)
            {
                for (int j=0; j<1000; j ++)
                {
                    grid[i][j] = 0;
                }
            }
        }

        void addPoints(Point* points, int size) {
            for (int i=0; i<size; i++)
            {
                grid[points[i].getX()][points[i].getY()]++;
            }
        }

        int calculateTwoOrMoreOverlap() {
            int overlaps = 0;
            for (int i=0; i<1000; i++)
            {
                for (int j=0; j<1000; j ++)
                {
                    if (grid[i][j] > 1)
                    {
                        overlaps++;
                    }
                }
            }
            return overlaps;
        }
};

const string INPUT_FILE_NAME = "input.txt";
Line lines[500];

void readData() 
{
    ifstream inFile(INPUT_FILE_NAME.c_str());

    string row;
    int i = 0;
    int point1[2], point2[2];
    while (inFile >> row) 
    {
        if (i%3 != 1)
        {
            stringstream ss(row);
            int j = 0;
            for (int v; ss >> v;)
            {
                if (i%3 == 0)
                {
                    point1[j] = v;
                } else 
                {
                    point2[j] = v;
                }

                j++;
                if (ss.peek() == ',')
                    ss.ignore();
            }
        }

        if (i%3 == 2)
        {
            lines[i/3] = Line(Point(point1[0], point1[1]), Point(point2[0], point2[1]));
        }
        i++;
    }
}

void runPartOne()
{
    Grid grid;

    for (int j=0; j<500; j++)
    {

        if (lines[j].isHorOrVer())
        {
            int size = lines[j].calculateHorOrVerSize();
            Point points[size];
            lines[j].calculateHorOrVerPoints(points);
            grid.addPoints(points, size);
        } 
    }

    cout << "Part 1: " << grid.calculateTwoOrMoreOverlap() << endl;
}

void runPartTwo()
{
    Grid grid;

    for (int j=0; j<500; j++)
    {

        if (lines[j].isHorOrVer())
        {
            int size = lines[j].calculateHorOrVerSize();
            Point points[size];
            lines[j].calculateHorOrVerPoints(points);
            grid.addPoints(points, size);
        } else {
            int size = lines[j].calculateDiagonalSize();
            Point points[size];
            lines[j].calculateDiagonalPoints(points);
            grid.addPoints(points, size);
        }
    }

    cout << "Part 2: " << grid.calculateTwoOrMoreOverlap() << endl;
}

int main()
{
    readData();
    runPartOne();
    runPartTwo();
    return 0;
}