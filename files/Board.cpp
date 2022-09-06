#include <iostream>
#include <vector>
#include "../headers/Board.h"
#include <utility>
using std::vector;
using std::string;
using std::cout;


Board::Board(int l){
    length = l;
    for(int i = 0; i < l; i++){
        vector< int > tempVector;
        for(int j = 0; j < l; j++){
            tempVector.push_back(0);
        }
        board.push_back(tempVector);
    }
}

void Board::addShip(Ship s){
    ships.push_back(s);
    for(int i = 0; i < s.getLength();i++){
        board[s.getShip(i).getX()][s.getShip(i).getY()] = 1;
    }
} 

void Board::printBoard(){
    cout << "  ";
    for(int i = 0; i < length; i++){
        cout << to_string(i) + " ";
    }
    cout << "\n";
    for(int i = 0; i < length; i++){
        cout << to_string(i) + " ";
        for(int j = 0; j < length; j++){
            if(board[i][j] == 2){
                cout << "#" << " ";
            } else if(board[i][j] == 3){
                cout << "x" << " ";
            } else {
               cout << "-" << " "; 
            }
        }
        cout << "\n";
    }
}

void Board::printBoardWShips(){
    cout << "  ";
    for(int i = 0; i < length; i++){
        cout << to_string(i) + " ";
    }
    cout << "\n";
    for(int i = 0; i < length; i++){
        cout << to_string(i) + " ";
        for(int j = 0; j < length; j++){
            if(board[i][j] == 0){
                cout << "-" << " ";
            } else if (board[i][j] == 1){
                cout << "o" << " ";
            } else if(board[i][j] == 2){
                cout << "#" << " ";
            } else if(board[i][j] == 3){
                cout << "x" << " ";
            }
        }
        cout << "\n";
    }
}

int Board::guess(Point p){
    if(board[p.getX()][p.getY()] == 0){
        board[p.getX()][p.getY()] = 3;
        return 0;
    }else if(board[p.getX()][p.getY()] == 1){
        for(int i = 0; i < ships.size(); i++){
            if(ships[i].inShip(p)){
                ships[i].changeShipStatus(p);
                break;
            }
        }
        board[p.getX()][p.getY()] = 2;
        return 1;
    } else {
        throw invalid_argument("Already selected point");
    }
}

int Board::getPoint(int x, int y){
    return board[x][y];
}

vector<Ship> Board::getShips(){
    return ships;
}

bool Board::checkSunk(){
    bool shipStatus = false;
    bool sunkShip = false;
    for(int i = 0; i < ships.size(); i++){
        shipStatus = false;
        for(int j = 0; j < ships[i].getLength();j++){
            if(ships[i].getShipBool(j)){
                shipStatus = true;
                break;
            }
        }
        if(!shipStatus){
            sunkShip = true;
            ships.erase(ships.begin()+i);
            break;
        }
    }
    return sunkShip;
}

bool Board::checkLost(){
    return ships.empty();
}

bool Board::in(Point p){
    for(int i = 0; i < ships.size(); i++){
        for(int j = 0; j < ships[i].getLength();j++){
            if(ships[i].getShip(j).equals(p)){
                return true;
            }
        }
    }
    return false;
}

void Board::addElementsAround(Point p, vector<Point> &x){
    if(p.getX() + 1 < length && (board[p.getX() + 1][p.getY()] != 2 && board[p.getX() + 1][p.getY()] != 3)){
        x.push_back(Point(p.getX()+1, p.getY()));
    }
    if(p.getX() - 1 >= 0 && (board[p.getX() - 1][p.getY()] != 2 && board[p.getX() - 1][p.getY()] != 3)){
        x.push_back(Point(p.getX()-1, p.getY()));
    }
    if(p.getY() - 1 >= 0 && (board[p.getX()][p.getY() - 1] != 2 && board[p.getX()][p.getY() - 1] != 3)){
        x.push_back(Point(p.getX(), p.getY()-1));
    }
    if(p.getY() + 1 < length && (board[p.getX()][p.getY() + 1] != 2 && board[p.getX()][p.getY() + 1] != 3)){
        x.push_back(Point(p.getX(), p.getY()+1));
    }
}

void Board::add2Elements(Point p1, Point p2, vector<Point> &x, int direction){
    if(direction == 0){
        Point greater(-1, -1);
        Point smaller(-1, -1);
        if(p1.getY() > p2.getY()){
            greater = Point(p1.getX(), p1.getY());
            smaller = Point(p2.getX(), p2.getY());
        } else {
            greater = Point(p2.getX(), p2.getY());
            smaller = Point(p1.getX(), p1.getY());
        }
        if(greater.getY() + 1 < length && (board[greater.getX()][greater.getY()+1] != 2 && board[greater.getX()][greater.getY()+1] != 3)){
            x.push_back(Point(greater.getX(), greater.getY()+1));
        }
        if(smaller.getY() - 1 >= 0 && (board[smaller.getX()][smaller.getY()-1] != 2 && board[smaller.getX()][smaller.getY()-1] != 3)){
            x.push_back(Point(smaller.getX(), smaller.getY()-1));
        }
    } else {
        Point greater(-1, -1);
        Point smaller(-1, -1);
        if(p1.getX() > p2.getX()){
            greater = Point(p1.getX(), p1.getY());
            smaller = Point(p2.getX(), p2.getY());
        } else {
            greater = Point(p2.getX(), p2.getY());
            smaller = Point(p1.getX(), p1.getY());
        }
        if(greater.getX() + 1 < length && (board[greater.getX() + 1][greater.getY()] != 2 && board[greater.getX()+1][greater.getY()] != 3)){
            x.push_back(Point(greater.getX()+1, greater.getY()));
        }
        if(smaller.getX() - 1 >= 0 && (board[smaller.getX() - 1][smaller.getY()] != 2 && board[smaller.getX() - 1][smaller.getY()] != 3)){
            x.push_back(Point(smaller.getX() - 1, smaller.getY()));
        }
    }
}

void Board::changeBoard(int i, int j){
    board[i][j] = 2;
}