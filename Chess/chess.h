#pragma once
#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for draw*
#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
using namespace std;
class Chess
{
private:
	bool castle = true;

	/***************************************************
	 * PAWN PROMOTION
	 * Checks to see if a pawn has qualified for a promotion
	 ***************************************************/
	bool pawnPromotion(char* board, int positionFrom, int positionTo) {}

	/***************************************************
	 * CASTLING
	 * Checks if the conditions for castling have been met
	 ***************************************************/
	bool castling(char* board, int positionFrom, int positionTo) {}
public:
	/***********************************************
	* Row Column
	* Simple row/column pair
	************************************************/
	struct RC
	{
		int row;
		int col;
	};


	/****************************************************
	* IS NOT WHITE
	* Is the current location valid and the piece is either
	* black (uppercase) or space
	***************************************************/
	inline bool isNotWhite(const char* board, int row, int col) {}

	/****************************************************
	 * IS  WHITE
	 * Is the current location valid and the piece is white
	 ***************************************************/
	inline bool isWhite(const char* board, int row, int col) {}

	/****************************************************
	 * IS NOT BLACK
	 * Is the current location valid and the piece is either
	 * white (lowercase) or space
	 ***************************************************/
	inline bool isNotBlack(const char* board, int row, int col) {}

	/****************************************************
	 * IS  BLACK
	 * Is the current location valid and the piece is black
	 ***************************************************/
	inline bool isBlack(const char* board, int row, int col) {}

	/*********************************************************
	 * GET POSSIBLE MOVES
	 * Determine all the possible moves for a given chess piece
	 *********************************************************/
	set <int> getPossibleMoves(const char* board, int location) {}

	/***************************************************
	 * DRAW
	 * Draw the current state of the game
	 ***************************************************/
	void draw(const char* board, const Interface& ui, const set <int>& possible) {}

	/*********************************************
	 * MOVE
	 * Execute one movement. Return TRUE if successful
	 *********************************************/
	bool move(char* board, int positionFrom, int positionTo) {}

	/*************************************
	 * All the interesting work happens here, when
	 * I get called back from OpenGL to draw a frame.
	 * When I am finished drawing, then the graphics
	 * engine will wait until the proper amount of
	 * time has passed and put the drawing on the screen.
	 **************************************/
	void callBack(Interface* pUI, void* p) {}

	/********************************************************
	 * PARSE
	 * Determine the nature of the move based on the input.
	 * This is the only function understanding Smith notation
	 *******************************************************/
	void parse(const string& textMove, int& positionFrom, int& positionTo) {}

	/********************************************************
	* READ FILE
	* Read a file where moves are encoded in Smith notation
	*******************************************************/
	void readFile(const char* fileName, char* board) {}
};