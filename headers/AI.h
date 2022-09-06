#ifndef AI_H
#define AI_H

#include <vector>
#include <utility>
#include <stdlib.h>
#include "Point.h"
#include "Board.h"
#include "Ship.h"
#include <time.h>

using namespace std;

class AI{
    private:
        vector< pair<Point, bool> > guess;
        Point lastHit1;
        Point lastHit2;
        Point lastHitTemp;
        vector<Ship> ships;
        vector<Point> points;
        int boardSize;
        Board aiBoard;

    public:
    AI(int boardLen, int numShips);

    void aiMakeShips(int numShips);

    void makeShip(int size, int vertOrHor);

    vector<Point> makeAdjacentPoints(int line, int startingPoint, int size,int direction);

    void aiGuess(Board &b);

    void addShipToPoint(Ship s);

    void printAIBoard();

    bool contains(Point p);

    Board getBoard();
    
    bool aiCheckSunk();

    int guessOnAIBoard(Point guess);

    void findEdges(Point &lh1, Point &lh2, Point &x, int direction);

    static pair<int, int> smallestQuad(Board b, int len);
};

#endif