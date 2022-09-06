#ifndef POINT_H
#define POINT_H

#include <vector>
using std::vector;

class Point{
    private:
        int x;
        int y;
    public:
        Point(int x, int y);

        int getX();

        int getY();

        void setX(int replace);

        void setY(int replace);

        bool equals(Point p);

        static bool checkAdj(std::vector<Point> p);

        static bool checkAdjPoints(std::vector<Point> p, int direction);

        static vector<Point> sort(vector<Point> p, int direction);
};

#endif