#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

std::string boardstart[3] = { "---", "---", "---" };
std::string board[3];
int turn;
char winner;

void reset() {
	memcpy(board, boardstart, sizeof boardstart);
}

void logWinner() {
	std::ofstream results;
	results.open("output.txt", std::ios::app);
	results << "Winner: " << winner << "\n";
	results.close();
}
std::string getCol(int col) {
	return std::string(new char[] {board[0][col], board[1][col], board[2][col], '\0'});
}

std::string getDiagX() {
	return std::string(new char[] {board[0][0], board[1][1], board[2][2], '\0'});
}

std::string getDiagY() {
	return std::string(new char[] {board[0][2], board[1][1], board[2][0], '\0'});
}

bool isWinner() {
	for(int i = 0; i < 3; i++) {
		if(!board[i].compare("XXX") || !board[i].compare("OOO")) {
			winner = board[i][1]; 
			return true;
		}
		if(!getCol(i).compare("XXX") || !getCol(i).compare("OOO")) {
			winner = board[0][i]; 
			return true;
		}
	}
	if(!getDiagX().compare("XXX") || !getDiagX().compare("OOO") || !getDiagY().compare("XXX") || !getDiagY().compare("OOO")) {
		winner = board[0][0];
		return true;
	}
	for(int i = 0; i < 3; i++) {
		int x = board[i].find('-');
		if(board[i].find('-') != board[i].npos) return false;
	}
	winner = 'D';
	return true;
}


void makeRandMove(char token) {
	bool madeMove = false;
	while(!madeMove) {
		int moveCol = rand() % 3;
		int moveRow = rand() % 3;
		if(board[moveRow][moveCol] == '-') {
			board[moveRow][moveCol] = token;
			madeMove = true;
		}
	}
}
void makeHorizMove() {
	
}

bool controlMove = false;
void makeControlMove() {
	makeHorizMove();
	/*makeVertMove();
	makeDiagMove();*/
	makeRandMove('O');
}

void makeLearnerMove() {
	makeRandMove('X');
}

void playGame() {
	while(!isWinner()) {
		if(turn == 0) {
			makeControlMove();
		}
		else {
			makeLearnerMove();
		}
		turn = (turn + 1) % 2;
	}
}

void simulate(int iterations) {
	for(int i = 0; i < iterations; i++) {
		reset();
		turn = rand() % 2;
		playGame();
		logWinner();
	}
}


int main(int argc, char **argv) {
	int iterations = 0;
	std::ofstream f;

	std::string x = std::string(new char[] {'x', 'x', 'x', '\0'});

	f.open("output.txt", std::fstream::out | std::fstream::trunc);
	std::cout << "Please enter the number of games to simulate: \n";
	std::cin >> iterations;

	simulate(iterations);

	std::cout << "Simulation Complete\n";
	std::cout << "View 'output.txt' to view results";
	std::cin >> iterations;
}