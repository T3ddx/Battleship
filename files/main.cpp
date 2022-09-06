#include <iostream>
#include <vector>
#include "../headers/Point.h"
#include "../headers/Ship.h"
#include "../headers/Board.h"
#include "../headers/AI.h"

using namespace std;

static bool contains(vector<Point> points, Point p){
    for(int i = 0; i < points.size();i++){
        if(points[i].equals(p)){
            return true;
        }
    }
    return false;
}

static void printTest(vector<Point> p){
    for(int i = 0; i < p.size(); i++){
        cout << "Point : " + to_string(p[i].getX()) << ", " + to_string(p[i].getY()) + "\n";
    }
}

int main(){
    
    //creates user board
    //gets board length
    system("clear");
    cout << "Length of board (4-10): ";
    int lenBoard;
    cin >> lenBoard;
    while(!cin || lenBoard < 4 || lenBoard > 10){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Sorry not a valid input, try again: ";
        cin >> lenBoard;
    }
    system("clear");
    Board b(lenBoard);

    //gets number of ships to use
    cout << "Enter number of ships (2-" + to_string(lenBoard - 2) + "): ";
    int numShips;
    cin >> numShips;
    while(!cin || numShips < 2 || numShips > lenBoard - 2){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Sorry not a valid input, try again: ";
        cin >> numShips;
    }
    system("clear");

    //gets ship points
    int sizeOfShip = 2;
    int count = 0;
    bool passed1 = true;
    bool passed2 = false;
    int x;
    int y;
    vector<Point> ship;
    //goes through for each ship
    for(int i = 0; i < numShips; i++){

        //checks if the points are adjacent
        do{
            if(!passed1){
                cout << "One or more points were not adjacent. Try again:\n";
                ship.clear();
            }

            //gets the points from the user
            while(count < sizeOfShip){
                Point temp(-1,-1);

                //checks if points have not been selected
                do{

                    if(passed2 || contains(ship, temp)){
                        cout << "Point was already picked. Try again.\n";
                    }
                    cout << "Enter an x coordinate: ";
                    cin >> x;
                    while(!cin || x < 0 || x > lenBoard-1){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid. Enter an x coordinate: ";
                        cin >> x;
                    }
                    cout << "Enter a y coordinate: ";
                    cin >> y;
                    while(!cin || y < 0 || y > lenBoard-1){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid. Enter an y coordinate: ";
                        cin >> y;
                    }
                    temp.setX(y);
                    temp.setY(x);
                    passed2 = b.in(temp);
                }while(passed2 || contains(ship, temp));

                ship.push_back(temp);
                count++;
            }
            count = 0;
            passed1 = Point::checkAdj(ship);

        } while(!passed1);
        system("clear");
        cout << "Finished Ship\n";
        b.addShip(Ship(sizeOfShip, ship));
        b.printBoardWShips();
        sizeOfShip ++;
        if(sizeOfShip > 4){
            sizeOfShip = 2;
        }
        ship.clear();
    }
    system("clear");
    
    //creates AI board
    //prints user board and AI board
    AI ai(lenBoard,numShips);
    cout << "AI Board:\n";
    ai.printAIBoard();
    cout << "\nUser Board:\n";
    b.printBoardWShips();

    
    //starts the actual game (guessing part)
    bool run = false;
    // add in b.checkLost()
    while(true){
        //system("clear");
        //player guessing
        do{
            try{
                cout << "\nGuess a point:\n";
                run = false;
                int xGuess;
                int yGuess;
                cout << "\nEnter an x coordinate to guess: ";
                cin >> xGuess;
                while(!cin || xGuess < 0 || xGuess >= lenBoard){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Not a valid coordinate. Try again:\n";
                    cin >> xGuess;
                }
                cout << "\nEnter an y coordinate to guess: ";;
                cin >> yGuess;
                while(!cin || yGuess < 0 || yGuess >= lenBoard){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Not a valid coordinate. Try again:\n";
                    cin >> yGuess;
                }
                system("clear");
                Point guess(yGuess, xGuess);
                if(ai.guessOnAIBoard(guess) == 1){
                    run = true;
                    cout << "\nYou hit a point!\n";
                }
            } catch(invalid_argument&e){
                cout << "\nPoint was already selected. Try again.\n";
                run = true;
            }
            if(ai.aiCheckSunk()){
                cout << "\nYou sunk a ship!\n";
                if(ai.getBoard().checkLost()){
                    run = false;
                }
            }
            cout << "\nAI Board:\n";
            ai.printAIBoard();
            //system("clear");
        }while(run);
        
        //checks if you beat AI
        if(ai.getBoard().checkLost()){
            cout << "\nCongrats! You Won!";
            break;
        }

        //AI guessing
        ai.aiGuess(b);
        if(b.checkLost()){
            cout << "\nSorry. The AI won!";
            break;
        }
    }
    
    /*
    srand(time(0));
    //testing AI guess
    Board test(5);
    test.changeBoard(0,0);
    test.changeBoard(2,1);
    test.changeBoard(0,3);
    test.printBoard();
    cout << "starting x: " + to_string(AI::smallestQuad(test, 5).first) + "starting y: " + to_string(AI::smallestQuad(test, 5).second); 
    cout << "\nstarting points: " + to_string(AI::smallestQuad(test, 5).first + rand()%(5/2 + 1));
    cout << "\nstarting points: " + to_string(AI::smallestQuad(test, 5).first + rand()%(5/2 + 1));
    cout << "\nstarting points: " + to_string(AI::smallestQuad(test, 5).first + rand()%(5/2 + 1));
    cout << "\nstarting points: " + to_string(AI::smallestQuad(test, 5).first + rand()%(5/2 + 1));
    cout << "\nstarting points: " + to_string(AI::smallestQuad(test, 5).first + rand()%(5/2 + 1));
    */

    //testers
    /*
    AI test(10, 4);
    test.printAIBoard();
    */
    /*vector<Point> p;
    p.push_back(Point(1, 3));
    p.push_back(Point(1, 0));
    p.push_back(Point(1, 1));
    bool t1 = Point::checkAdjPoints(p, 0);
    cout << to_string(t1) + "\n";*/
    return 0;
}