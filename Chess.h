/*chess.h file*/


#pragma once
#include<string>
class Piece {
protected :
	char color;
public:
	Piece(char);
	virtual bool isValidMove(int,int,int,int,Piece*[8][8])=0;
	virtual char getColor();
	virtual char getSymbol()=0;
	virtual ~Piece();
	
};
class Pawn:public Piece {
public:
	Pawn(char);
	bool isValidMove(int, int, int, int, Piece* [8][8]);
	char getSymbol();
};
class Rook :public Piece {
public:
	Rook(char);
	bool isValidMove(int, int, int, int, Piece* [8][8]);
	char getSymbol();

};
class Knight :public Piece {
public:
	Knight(char);
	bool isValidMove(int, int, int, int, Piece* [8][8]);
	char getSymbol();
};
class Bishop :public Piece {
public:
	Bishop(char);
	bool isValidMove(int, int, int, int, Piece* [8][8]);
	char getSymbol();
};
class King :public Piece {
public:
	King(char);
	bool isValidMove(int, int, int, int, Piece* [8][8]);
	char getSymbol();
};
class Queen :public Piece {
public:
	Queen(char);
	bool isValidMove(int, int, int, int, Piece* [8][8]);
	char getSymbol();
};
class Board {
private:
	Piece* grid[8][8];
public:
	Board();
	bool move(char,bool&);
	void setUp();
	void display();
};
class Game {
private:
	Board board;
	char turn;

public:
	Game();
	void play();

};