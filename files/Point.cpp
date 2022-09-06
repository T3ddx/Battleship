#include <iostream>
#include <vector>
#include "../headers/Point.h"
using std::vector;

Point::Point(int x, int y){
    this->x = x;
    this->y = y;
}

int Point::getX(){
    return x;
}

int Point::getY(){
    return y;
}

void Point::setX(int replace){
    x = replace;
}

void Point::setY(int replace){
    y = replace;
}

bool Point::equals(Point p){
    if(p.getX() == x && p.getY() == y){
        return true;
    }
     return false;
}

bool Point::checkAdj(vector<Point> p){
    bool xB = true;
    bool yB = true;
    int x = p[0].getX();
    int y = p[0].getY();
    for(int i = 0; i < p.size(); i++){
        if(p[i].getX() != x){
            xB = false;
        }
    }
    for(int i = 0; i < p.size(); i++){
        if(p[i].getY() != y){
            yB = false;
        }
    }
    if(xB){
        xB = checkAdjPoints(p, 0);
    }
    if(yB){
        yB = checkAdjPoints(p, 1);
    }
    return xB || yB;
}

bool Point::checkAdjPoints(vector<Point> p, int direction){
    vector<Point> x = sort(p, direction);
    if(direction == 0){
        for(int i = 0; i < x.size()-1; i++){
            if(x[i].getY() != x[i+1].getY()-1){
                return false;
            }
        }
    } else{
        for(int i = 0; i < x.size()-1; i++){
            if(x[i].getX() != x[i+1].getX()-1){
                return false;
            }
        }
    }
    return true;
}

vector<Point> Point::sort(vector<Point> p, int direction){
    int min;
    int index;
    if(direction == 0){
        for(int i = 0; i < p.size(); i++){
            min = p[i].getY();
            index = i;
            for(int j = i+1; j < p.size(); j++){
                if(min > p[j].getY()){
                    min = p[j].getY();
                    index = j;
                }
            }
            int temp = p[i].getY();
            p[i].setY(min);
            p[index].setY(temp);
        }
    } else {
        for(int i = 0; i < p.size(); i++){
            min = p[i].getX();
            index = i;
            for(int j = i+1; j < p.size(); j++){
                if(min > p[j].getX()){
                    min = p[j].getX();
                    index = j;
                }
            }
            int temp = p[i].getX();
            p[i].setX(min);
            p[index].setX(temp);
        }
    }
    return p;
}