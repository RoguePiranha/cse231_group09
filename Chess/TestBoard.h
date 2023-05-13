#pragma once

#include "board.h"
#include "piece.h"
#include "space.h"
#include "point.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "move.h"

using namespace std;

class TestBoard
{
public:
	void Run()
	{
		TestClear();
		TestCastleK();
		TestCastleQ();
		TestEnPassant();
		TestMoveToOpen();
		TestPromotion();
		TestReset();
		cout << "\033[32m" << "Board Test Passed." << "\033[0m" << endl;
	}

private:
	void TestClear()
	{
		// SETUP
		bool pass = true;
		int location = 0;
		Board b;
		b.reset();
		b.clear();
		// EXERCISE
		for (int i = 0; i < 64; i++)
		{
			int row = i / 8;
			int col = i % 8;
			if (b.board[i] != make_unique<Space>(Space(col, row, false)))
			{
				pass = false;
				location = i;
				break;
			}
		}
		// VERIFY
		if (!pass)
		{
			cout << b.board[location] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
	} // TEARDOWN

	void TestReset()
	{
		// SETUP
		Board b;
		b.reset();
		bool pass = true;
		int location = 0;
		// EXERCISE
		for (int i = 0; i < 64; i++)
		{
			int row = i / 8;
			int col = i % 8;
			switch (i)
			{
			case 'p':
				b.board[i] != make_unique<Pawn>(Pawn(col, row, i < 16));
				pass = false;
				location = i;
				break;
			case 'r':
				b.board[i] != make_unique<Rook>(Rook(col, row, i < 16));
				pass = false;
				location = i;
				break;
			case 'n':
				b.board[i] != make_unique<Knight>(Knight(col, row, i < 16));
				pass = false;
				location = i;
				break;
			case 'b':
				b.board[i] != make_unique<Bishop>(Bishop(col, row, i < 16));
				pass = false;
				location = i;
				break;
			case 'q':
				b.board[i] != make_unique<Queen>(Queen(col, row, i < 16));
				pass = false;
				location = i;
				break;
			case 'k':
				b.board[i] != make_unique<King>(King(col, row, i < 16));
				pass = false;
				location = i;
				break;
			default:
				b.board[i] != make_unique<Space>(Space(col, row, false));
				pass = false;
				location = i;
				break;
			}
			if (!pass)
				break;
		}
		// VERIFY
		if (!pass)
		{
			cout << b.board[location] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
	}// TEARDOWN

	int TestEnPassant()
	{
		// SETUP
		Board b;
		Move m;
		char setup[64] = {
			'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
			'p', 'p', 'p', ' ', 'p', 'p', 'p', 'p',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', 'P', 'p', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			'P', 'P', ' ', 'P', 'P', 'P', 'P', 'P',
			'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
		b.reset(setup);
		m.source = Position(3, 4);
		m.dest = Position(4, 5);
		// EXERCISE
		b.move(m);
		// VERIFY
		if (b.board[19] != make_unique<Pawn>(Pawn(4, 5, true)))
		{
			cout << b.board[19] << endl;
			cout << "Test Failed";
		}
		else if (b.board[26] != make_unique<Space>(Space(4, 5, false)))
		{
			cout << b.board[26] << endl;
			cout << "Test Failed";
		}
		else if (b.board[27] == make_unique<Space>(Space(4, 5, false)))
		{
			cout << b.board[27] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;

		return 0;
	}// TEARDOWN

	void TestPromotion()
	{
		// SETUP
		Board b;
		Move m;
		char setup[64] = {
			'r', 'n', ' ', 'q', 'k', 'b', 'n', 'r',
			'p', 'p', 'P', ' ', 'p', 'p', 'p', 'p',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			'P', 'P', ' ', 'P', 'P', 'P', 'P', 'P',
			'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
		b.reset(setup);
		m.source = Position(3, 2);
		m.dest = Position(3, 1);
		// EXERCISE
		b.move(m);
		// VERIFY
		if (b.board[2] != make_unique<Queen>(Queen(3, 1, true)))
		{
			cout << b.board[2] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
	}

	void TestCastleK()
	{
		// SETUP
		Board b;
		Move m;
		char setup[64] = {
			'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
			'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
			'R', 'N', 'B', 'Q', 'K', ' ', ' ', 'R'};
		b.reset(setup);
		m.source = Position(5, 8);
		m.dest = Position(7, 8);
		// EXERCISE
		b.move(m);
		// VERIFY
		if (b.board[62] != make_unique<Rook>(Rook(6, 8, true)))
		{
			cout << b.board[62] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
	}// TEARDOWN

	void TestCastleQ()
	{
		// SETUP
		Board b;
		Move m;
		char setup[64] = {
			'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
			'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
			'R', ' ', ' ', ' ', 'K', 'B', 'N', 'R'};
		b.reset(setup);
		m.source = Position(5, 8);
		m.dest = Position(3, 8);
		// EXERCISE
		b.move(m);
		// VERIFY
		if (b.board[60] != make_unique<Rook>(Rook(4, 8, true)))
		{
			cout << b.board[60] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
	}// TEARDOWN

	// Test moving piece to an open spot
	void TestMoveToOpen()
	{
		// SETUP
		Board b;
		Move m;
		b.reset();
		m.source = Position(1, 7);
		m.dest = Position(1, 6);
		// EXERCISE
		b.move(m);
		// VERIFY
		if (b.board[40] != make_unique<Pawn>(Pawn(1, 6, true)))
		{
			cout << b.board[40] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
	}// TEARDOWN
};