#include <stdio.h>
#include <stdlib.h>
#include <iostream>

char board[3][3] = {{ 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }};

void reset();
void logWinner();
void playGame(int);


void simulate(int iterations){
	
	for (int i=0; i< iterations; i++){
		int startingPlayer = rand() % 2;
		playGame(startingPlayer);
		logWinner();
		reset();
	}
}

int main(int argc, char **argv)
{
	int iterations  = 0;
	std::cout << "Please enter the number of games to simulate: \n"
	cin >> iterations ;
	
	simulate(iterations);
	
	cout << "Simulation Complete";
	cout << "View 'output.txt' to view results";
}