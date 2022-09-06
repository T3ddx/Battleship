#ifndef BOARD_H
#define BOARD_H

#include <utility>
#include <vector>
#include "../headers/Ship.h"
#include "../headers/Point.h"
using std::vector;


class Board{
    private:
        int length;
        vector< vector< int > > board;
        vector<Ship> ships;
    public:
        Board(int l);

        void addShip(Ship s);

        void printBoard();

        void printBoardWShips();

        int guess(Point p);

        int getPoint(int x, int y);
        
        vector<Ship> getShips();

        bool checkSunk();

        bool checkLost();

        bool in(Point p);

        void addElementsAround(Point p, vector<Point> &x);

        void add2Elements(Point p1, Point p2, vector<Point> &x, int direction);

        //testing purposes only
        void changeBoard(int i, int j);
};

#endif