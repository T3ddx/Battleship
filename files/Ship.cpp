#include <iostream>
#include <vector>
#include <utility>
#include "../headers/Ship.h"

using namespace std;

Ship::Ship(int l, vector<Point> points){
    length = l;
    for(int i = 0; i < length; i++){
        ship.push_back(pair<Point, bool>(points[i], true));
        }
    }

vector< pair<Point, bool> > Ship::getShip(){
    return ship;
}

Point Ship::getShip(int i){
    return ship[i].first;
}

void Ship::changeShipStatus(Point p){
    for(int i = 0; i < ship.size(); i++){
        if(ship[i].first.equals(p)){
            ship[i].second = false;
        }
    }
}

int Ship::getLength(){
        return length;
}

bool Ship::inShip(Point p){
    for(int i = 0; i < length; i++){
        if(ship[i].first.equals(p)){
            return true;
        }
    }
    return false;
}

bool Ship::getShipBool(int i){
    return ship[i].second;
}