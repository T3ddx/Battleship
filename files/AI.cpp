#include "../headers/AI.h"
#include <vector>
#include <utility>
#include <thread>
#include <stdlib.h>
#include "../headers/Point.h"
#include "../headers/Board.h"
#include "../headers/Ship.h"
#include <time.h>

using namespace std;

AI::AI(int boardLen, int numShips) : aiBoard(boardLen), lastHit1(-1,-1), lastHit2(-1,-1), lastHitTemp(-1, -1)
{
    boardSize = boardLen;
    aiMakeShips(numShips);
}

void AI::aiMakeShips(int numShips)
{
    srand(time(0));
    int size = 2;
    for(int i = 0; i < numShips; i++){
        makeShip(size, rand()%2);
        size++;
        if(size > 4){
            size = 2;
        }
    }
}

void AI::makeShip(int size, int vertOrHor){
    srand(time(0));
    Point temp(-1, -1);
    int x = -1;
    int y = -1;
    bool run = false;
    do{
        run = false;
        x = rand()%boardSize;
        y = rand()%boardSize;
        temp.setX(x);
        temp.setY(y);
        while(contains(temp)){
            x = rand()%boardSize;
            y = rand()%boardSize;
            temp.setX(x);
            temp.setY(y);
        }
        if(vertOrHor == 0){
            try
            {
                vector<Point> p = makeAdjacentPoints(temp.getX(), temp.getY(), size, 0);
                p.push_back(temp);
                Ship sh(size,p);
                addShipToPoint(sh);
                aiBoard.addShip(sh);
            }
            catch(invalid_argument&e)
            {
                run = true;
            }
        } else if(vertOrHor == 1){
            try
            {
                vector<Point> p = makeAdjacentPoints(temp.getY(), temp.getX(), size, 1);
                p.push_back(temp);
                Ship sh(size,p);
                addShipToPoint(sh);
                aiBoard.addShip(sh);
            }
            catch(invalid_argument&e)
            {
                run = true;
            }
        }
    } while(run);

}

vector<Point> AI::makeAdjacentPoints(int line, int startingPoint, int size,int direction){
    vector<Point> restOfPoints;
    if(direction == 0){
        int y = startingPoint;
        int count = 0;
        while(y+1 < boardSize && aiBoard.getPoint(line, y+1) != 1 && count < size - 1){
            y++;
            count++;
            restOfPoints.push_back(Point(line, y));
        }
        y = startingPoint;
        while(y-1 >= 0 && aiBoard.getPoint(line, y-1) != 1 && count < size - 1){
            y--;
            count++;
            restOfPoints.push_back(Point(line, y));
        }
        if(count != size - 1){
            throw invalid_argument("Not enough space");
        }
    } else if(direction == 1){
        int x = startingPoint;
        int count = 0;
        while(x+1 < boardSize && aiBoard.getPoint(x+1, line) != 1 && count < size - 1){
            x++;
            count++;
            restOfPoints.push_back(Point(x, line));
        }
        x = startingPoint;
        while(x-1 >= 0 && aiBoard.getPoint(x-1, line) != 1 && count < size - 1){
            x--;
            count++;
            restOfPoints.push_back(Point(x, line));
        }
        if(count != size -1){
            throw invalid_argument("Not enough space");
        }
    }
    return restOfPoints;
}

void AI::aiGuess(Board &b)
{
    //system("clear");
    if(lastHit1.equals(Point(-1,-1))){
        srand(time(0));
        bool finished = false;
        do{
            finished = false;
            int x = 0;
            int y = 0;
            if(boardSize % 2 == 0){
                x = smallestQuad(b, boardSize).first + rand()%boardSize/2;
                y = smallestQuad(b, boardSize).second + rand()%boardSize/2;
            } else {
                if(smallestQuad(b, boardSize).first != 0 && smallestQuad(b, boardSize).second != 0){
                    x = smallestQuad(b, boardSize).first + rand()%(boardSize/2 + 1);
                    y = smallestQuad(b, boardSize).second + rand()%(boardSize/2 + 1);
                } else if(smallestQuad(b, boardSize).first == 0 && smallestQuad(b, boardSize).second != 0){
                    x = smallestQuad(b, boardSize).first + rand()%(boardSize/2);
                    y = smallestQuad(b, boardSize).second + rand()%(boardSize/2 + 1);
                } else if(smallestQuad(b, boardSize).first != 0 && smallestQuad(b, boardSize).second == 0){
                    x = smallestQuad(b, boardSize).first + rand()%(boardSize/2 + 1);
                    y = smallestQuad(b, boardSize).second + rand()%(boardSize/2);
                } else{
                    x = smallestQuad(b, boardSize).first + rand()%boardSize/2;
                    y = smallestQuad(b, boardSize).second + rand()%boardSize/2;
                }
            }
            try{
                Point* randGuess = new Point(x,y);
                if(b.guess((*randGuess)) == 1){
                    lastHit1 = Point(randGuess->getX(), randGuess->getY());
                    cout << "\nAI guessed: " + to_string(randGuess->getY()) + ", " + to_string(randGuess->getX());
                    cout << "\nUser Board:\n";
                    b.printBoardWShips();
                    if(b.checkSunk()){
                        cout << "\nAI sunk a ship!!!\n";
                        lastHit1 = Point(-1, -1);
                        lastHit2 = Point(-1, -1);
                    }
                    if(!b.checkLost()){
                        this_thread::sleep_for(chrono::seconds(1));
                        aiGuess(b);
                    }
                } else{
                    cout << "\nAI guessed: " + to_string(randGuess->getY()) + ", " + to_string(randGuess->getX()) + "\n";
                    cout << "\nUser Board:\n";
                    b.printBoardWShips();
                }
            } catch(invalid_argument&e){
                finished = true;
            }
        } while(finished);
    } else{
        if(lastHit2.equals(Point(-1,-1))){
            vector<Point> x;
            b.addElementsAround(lastHit1, x);
            int i = rand()%x.size();
                try{
                    if(b.guess(x[i]) == 1){
                        lastHit2 = Point(x[i].getX(), x[i].getY());
                        cout << "\nAI guessed: " + to_string(x[i].getY()) + ", " + to_string(x[i].getX());
                        cout << "\nUser Board:\n";
                        b.printBoardWShips();
                        if(b.checkSunk()){
                            cout << "\nAI sunk a ship!!!\n";
                            if(lastHitTemp.equals(Point(-1, -1))){
                                lastHit1 = Point(-1, -1);
                                lastHit2 = Point(-1, -1);
                            } else {
                                lastHit1 = Point(lastHitTemp.getX(), lastHitTemp.getY());
                                lastHit2 = Point(-1, -1);
                            }
                            
                        }
                        if(!b.checkLost()){
                            this_thread::sleep_for(chrono::seconds(1));
                            aiGuess(b);
                        }
                    } else{
                        cout << "\nAI guessed: " + to_string(x[i].getY()) + ", " + to_string(x[i].getX()) + "\n";
                        cout << "\nUser Board:\n";
                        b.printBoardWShips();
                    }
                } catch(invalid_argument&e){
                    cout << "This should never happen lol.";
                }
        } else{
            if(lastHit1.getX() == lastHit2.getX()){
                vector<Point> x;
                b.add2Elements(lastHit1, lastHit2, x, 0);
                if(x.size() == 0){
                    lastHitTemp = Point(lastHit2.getX(), lastHit2.getY());
                    lastHit2 = Point(-1, -1);
                    aiGuess(b);
                } else{
                        int i = rand()%x.size();
                    try{
                        if(b.guess(x[i]) == 1){
                            findEdges(lastHit1, lastHit2, x[i], 0);
                            cout << "\nAI guessed: " + to_string(x[i].getY()) + ", " + to_string(x[i].getX());
                            cout << "\nUser Board:\n";
                            b.printBoardWShips();
                            if(b.checkSunk()){
                                cout << "\nAI sunk a ship!!!\n";
                                lastHit1 = Point(-1, -1);
                                lastHit2 = Point(-1, -1);
                            }
                            if(!b.checkLost()){
                                this_thread::sleep_for(chrono::seconds(1));
                                aiGuess(b);
                            } else {
                                cout << "Sorry. The AI won.\n";
                            }
                        } else {
                            cout << "\nAI guessed: " + to_string(x[i].getY()) + ", " + to_string(x[i].getX()) + "\n";
                            cout << "\nUser Board:\n";
                            b.printBoardWShips();
                        }
                    } catch(invalid_argument&e){
                        cout << "This should never happen lol.";
                    }
                }
            } else{
                vector<Point> x;
                b.add2Elements(lastHit1, lastHit2, x, 1);
                if(x.size() == 0){
                    lastHitTemp = Point(lastHit2.getX(), lastHit2.getY());
                    lastHit2 = Point(-1, -1);
                    this_thread::sleep_for(chrono::seconds(1));
                    aiGuess(b);
                } else {
                    int i = rand()%x.size();
                    try{
                        if(b.guess(x[i]) == 1){
                            findEdges(lastHit1, lastHit2, x[i], 1);
                            cout << "\nAI guessed: " + to_string(x[i].getY()) + ", " + to_string(x[i].getX());
                            cout << "\nUser Board:\n";
                            b.printBoardWShips();
                            if(b.checkSunk()){
                                cout << "\nAI sunk a ship!!!\n";
                                lastHit1 = Point(-1, -1);
                                lastHit2 = Point(-1, -1);
                            }
                            if(!b.checkLost()){
                                this_thread::sleep_for(chrono::seconds(1));
                                aiGuess(b);
                            }
                        } else{
                            cout << "\nAI guessed: " + to_string(x[i].getY()) + ", " + to_string(x[i].getX()) + "\n";
                            cout << "\nUser Board:\n";
                            b.printBoardWShips();
                        }
                    } catch(invalid_argument&e){
                        cout << "This should never happen lol.";
                    }
                }
            }
        }
    }
}

void AI::printAIBoard()
{
    aiBoard.printBoard();
}

void AI::addShipToPoint(Ship s){
    for(int i = 0; i < s.getShip().size(); i++){
        points.push_back(s.getShip(i));
    }
}

bool AI::contains(Point p){
    for(int i = 0; i < points.size();i++){
        if(points[i].equals(p)){
            return true;
        }
    }
    return false;
}

Board AI::getBoard(){
    return aiBoard;
}

int AI::guessOnAIBoard(Point guess){
    return aiBoard.guess(guess);
}

bool AI::aiCheckSunk(){
    return aiBoard.checkSunk();
}

void AI::findEdges(Point &lh1, Point &lh2, Point &x, int direction){
    if(direction == 0){
        Point greater(-1, -1);
        Point smaller(-1, -1);
        if(lh1.getY() > lh2.getY()){
            Point greater = lh1;
            Point smaller = lh2;
        } else {
            Point greater = lh1;
            Point smaller = lh2;
        }
        if(x.getY() < smaller.getY()){
            smaller.setY(x.getY());
        } else if(x.getY() > greater.getY()){
            greater.setY(x.getY());
        }
    } else {
        Point greater(-1, -1);
        Point smaller(-1, -1);
        if(lh1.getX() > lh2.getX()){
            Point greater = lh1;
            Point smaller = lh2;
        } else {
            Point greater = lh1;
            Point smaller = lh2;
        }
        if(x.getX() < smaller.getX()){
            smaller.setX(x.getX());
        } else if(x.getX() > greater.getX()){
            greater.setX(x.getX());
        }
    }
}

pair<int,int> AI::smallestQuad(Board b, int len){
    int startPointX = 0;
    int startPointY = 0;
    int retX = 0;
    int retY = 0;
    int min;
    int count = 0;
    for(int i = startPointX; i < len/2; i++){
        for(int j = startPointY; j < len/2; j++){
            if(b.getPoint(i, j) == 2 || b.getPoint(i,j) == 3){
                count++;
            }
        }
    }
    min = count;
    count = 0;
    startPointX = len/2;
    for(int i = startPointX; i < len; i++){
        for(int j = startPointY; j < len/2; j++){
            if(b.getPoint(i, j) == 2 || b.getPoint(i,j) == 3){
                count++;
            }
        }
    }
    if(count < min){
        retX = len/2;
        retY = 0;
        min = count;
    }
    count = 0;
    startPointX = 0;
    startPointY = len/2;
    for(int i = startPointX; i < len/2; i++){
        for(int j = startPointY; j < len; j++){
            if(b.getPoint(i, j) == 2 || b.getPoint(i,j) == 3){
                count++;
            }
        }
    }
    if(count < min){
        retX = 0;
        retY = len/2;
        min = count;
    }
    count = 0;
    startPointX = len/2;
    for(int i = startPointX; i < len; i++){
        for(int j = startPointY; j < len; j++){
            if(b.getPoint(i, j) == 2 || b.getPoint(i,j) == 3){
                count++;
            }
        }
    }
    if(count < min){
        retX = len/2;
        retY = len/2;
        min = count;
    }
    return pair<int,int>(retX,retY);
}