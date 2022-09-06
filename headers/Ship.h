#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>
#include <utility>
#include "../headers/Point.h"
using namespace std;

class Ship {
    private:
        vector< pair<Point, bool> > ship;
        int length;
    public:
        Ship(int l, vector<Point> points);

        vector< pair<Point, bool> > getShip();

        Point getShip(int i);

        void changeShipStatus(Point p);
        
        int getLength();

        bool inShip(Point p);

        bool getShipBool(int i);
};

#endif