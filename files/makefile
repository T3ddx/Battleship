battleship: AI.o Board.o main.o Point.o Ship.o
	clang++ AI.o Board.o main.o Point.o Ship.o -o battleship

Point.o: Point.cpp
	clang++ -c Point.cpp

Ship.o: Ship.cpp
	clang++ -c Ship.cpp

Board.o: Board.cpp
	clang++ -c Board.cpp

AI.o: AI.cpp
	clang++ -c AI.cpp

main.o: main.cpp
	clang++ -c main.cpp

clean:
	rm *.o battleship