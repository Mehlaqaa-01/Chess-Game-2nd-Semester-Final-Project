/* chess.cpp file */


#include<iostream>
#include<cmath>
#include"Chess.h"
using namespace std;
                               /* Piece class */
Piece::Piece(char c) {
	color = c;
}
char Piece::getColor() {
	return color;
}
Piece::~Piece() {

}
                             /* Pawn Class */
Pawn::Pawn(char c):Piece(c) {

}
bool Pawn::isValidMove(int sx, int sy, int dx, int dy, Piece* board[8][8]) {
	/* forward move */
	int dir = (color == 'W') ? -1 : 1;
	if (sy == dy && dx == sx + dir && board[dx][dy] == nullptr) {
		return true;
	}
	/* start move */
	if (sy == dy && dx == sx) {
		return false;
	}
	if (color == 'W' && sx == 6 || color == 'B' && sx == 1) {
		if (board[sx + 2 * dir][sy] == nullptr && dx == sx + 2 * dir) {
			return true;

		}
	}
	/* Capture Move */
	if (abs(dy - sy) == 1 && dx == sx + dir && board[dx][dy] != nullptr && board[dx][dy]->getColor() != color) {
		return true;
	}
	return false;
}
char Pawn::getSymbol() {
	return(color == 'W' ? 'P' : 'p');
}
                                /* Rook Class */
Rook::Rook(char c) :Piece(c) {

}
bool Rook::isValidMove(int sx, int sy, int dx, int dy, Piece* board[8][8]) {
	if (dx == sx && dy == sy) {
		return false;
	}

	int X = (dx - sx) ? (dx - sx) / abs(dx - sx) : 0;
	int Y = (dy - sy) ? (dy - sy) / abs(dy - sy) : 0;
	int x = sx + X;
	int y = sy + Y;
	while (dx != x || dy != y) {
		if (board[x][y] != nullptr) {
			return false;
		}
		x += X;
		y += Y;
	}
	return true;
}
char Rook::getSymbol() {
	return(color == 'W' ? 'R' : 'r');
}
                              /* Knight Class */
Knight::Knight(char c):Piece(c) {

}
bool Knight::isValidMove(int sx, int sy, int dx, int dy, Piece* board[8][8]) {
	if (sx == dx && sy == dy) {
		return false;
	}
	int X = abs(dx - sx);
	int Y = abs(dy - sy);
	return (X == 1 && Y == 2) || (X == 2 && Y == 1);

}
char Knight::getSymbol() {
	return (color == 'W') ? 'N' : 'n';
}
                            /* Bishop Class */
Bishop::Bishop(char c) :Piece(c) {

}
bool Bishop::isValidMove(int sx, int sy, int dx, int dy, Piece* board[8][8]) {
	if (sx == dx && sy == dy) return false;
	if (abs(dx - sx) != abs(dy - sy)) return false;


	int X = (dx - sx) ? (dx - sx )/ abs(dx - sx) : 0;
	int Y = (dy - sy) ? (dy - sy) / abs(dy - sy) : 0;
	int x = sx + X;
	int y = sy + Y;
	while (x != dx) {
		if (board[x][y] != nullptr) {
			return false;
		}
		x += X;
		y += Y;
	}
	return true;
} 
char Bishop::getSymbol() {
	return (color == 'W') ? 'B' : 'b';
}
                           /* Queen Class */
Queen::Queen(char c) :Piece(c) {

}
bool Queen::isValidMove(int sx, int sy, int dx, int dy, Piece* board[8][8]) {
	if (sx == dx && sy == dy) {
		return false;
	}
	if (sx == dx || sy == dy) {
		Rook r(color);
		return r.isValidMove(sx, sy, dx, dy, board);
	}
	if (abs(dx - sx) == abs(dy - sy)) {
		Bishop b(color);
		return b.isValidMove(sx, sy, dx, dy, board);
	}
	return false;
}
char Queen::getSymbol() {
	return (color == 'W') ? 'Q' : 'q';
}
                         /* King Class */
King::King(char c) :Piece(c) {

}
bool King::isValidMove(int sx, int sy, int dx, int dy, Piece* board[8][8]) {
	if (sx == dx && sy == dy) return false;
	return abs(dx - sx) <= 1 && abs(dy - sy) <= 1;
}
char King:: getSymbol() { 
	return (color == 'W') ? 'K' : 'k'; 
}
                        /* Board Class */
Board::Board() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			grid[i][j] = nullptr;
		}
	}
}
void Board::setUp() {
	for (int i = 0; i < 8; i++) {
		grid[1][i] = new Pawn('B');
		grid[6][i] = new Pawn('W');
	}
	grid[0][7] = grid[0][0] = new Rook('B');
	grid[7][0] = grid[7][7] = new Rook('W');

	grid[0][1] = grid[0][6] = new Knight('B');
	grid[7][1] = grid[7][6] = new Knight('W');

	grid[0][2] = grid[0][5] = new Bishop('B');
	grid[7][2] = grid[7][5] = new Bishop('W');

	grid[0][3] = new Queen('B');
	grid[7][3] = new Queen('W');

	grid[0][4] = new King('B');
	grid[7][4] = new King('W');
}

void Board::display() {
	cout << "\n  0 1 2 3 4 5 6 7\n";
	for (int i = 0; i < 8; i++) {
		cout << i << " ";
		for (int j = 0; j < 8; j++) {
			if (grid[i][j]) {
				cout << grid[i][j]->getSymbol()<<" ";
			}
			else {
				cout << ". ";
			}
		}
		cout << endl;
	}
}
/*  Move function in board class */
bool Board::move(char turn, bool& kingcaptured) {

	int sx, sy, dx, dy;

	kingcaptured = false;

	cout << "\nenter source row and column: ";
	cin >> sx >> sy;

	cout << "enter destination row and column: ";
	cin >> dx >> dy;

	// bounds check
	if (sx < 0 || sx > 7 || sy < 0 || sy > 7 ||
		dx < 0 || dx > 7 || dy < 0 || dy > 7) {

		cout << "invalid coordinates!\n";
		return false;
	}

	// no piece at source
	if (grid[sx][sy] == nullptr) {

		cout << "no piece at source!\n";
		return false;
	}

	// wrong turn check
	if (grid[sx][sy]->getColor() != turn) {

		cout << "wrong turn!\n";
		return false;
	}

	// cannot capture own piece
	if (grid[dx][dy] != nullptr &&
		grid[dx][dy]->getColor() == grid[sx][sy]->getColor()) {

		cout << "cannot capture your own piece!\n";
		return false;
	}

	// movement validation (polymorphism)
	if (!grid[sx][sy]->isValidMove(sx, sy, dx, dy, grid)) {

		cout << "invalid move!\n";
		return false;
	}

	// king capture check
	if (grid[dx][dy] != nullptr) {

		if (grid[dx][dy]->getSymbol() == 'k' ||
			grid[dx][dy]->getSymbol() == 'K') {

			kingcaptured = true;
		}

		delete grid[dx][dy];
	}

	// move piece
	grid[dx][dy] = grid[sx][sy];
	grid[sx][sy] = nullptr;

	return true;
}

/* Game Class */

Game::Game() {
	turn = 'W';
	board.setUp();
	play();
}

void Game::play() {

	bool kingcaptured = false;

	while (true) {

		board.display();

		cout << "\nCurrent Turn: ";

		if (turn == 'W')
			cout << "White\n";
		else
			cout << "Black\n";

		if (board.move(turn, kingcaptured)) {

			if (kingcaptured) {

				board.display();

				cout << "\nGame Over! ";

				if (turn == 'W')
					cout << "White";
				else
					cout << "Black";

				cout << " wins!\n";

				break;
			}

			// change turn
			turn = (turn == 'W') ? 'B' : 'W';
		}
	}
}