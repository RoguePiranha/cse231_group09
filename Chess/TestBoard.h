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
	void TestClear()
	{
		bool pass;
		int location;
		Board b;
		b.reset();
		b.clear();
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
		if (!pass)
		{
			cout << b.board[location] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
		
	}

	void TestReset()
	{
		Board b;
		b.reset();
		bool pass;
		int location;
		
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
		if (!pass)
		{
			cout << b.board[location] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
	}

	int TestEnPassant()
	{
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
		'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'
		};
		b.reset(setup);
		m.source = Position(3, 4);
		m.dest = Position(4, 5);
		b.move(m);
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
	}

	void TestPromotion()
	{
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
		'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'
		};
		b.reset(setup);
		m.source = Position(3, 2);
		m.dest = Position(3, 1);
		b.move(m);
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
		'R', 'N', 'B', 'Q', 'K', ' ', ' ', 'R'
		};
		b.reset(setup);
		m.source = Position(5, 8);
		m.dest = Position(7, 8);
		b.move(m);
		if (b.board[2] != make_unique<Rook>(Rook(6, 8, true)))
		{
			cout << b.board[2] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
		
		return 0;
	}

	void TestCastleQ()
	{
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
		'R', ' ', ' ', ' ', 'K', 'B', 'N', 'R'
		};
		
		return 0;
	}

	// Test moving piece to an open spot
	void TestMoveToOpen()
	{
		Board b;
		Move m;
		b.reset();
		m.source = Position(1, 7);
		m.dest = Position(1, 6);
		b.move(m);
		if (b.board[40] != make_unique<Pawn>(Pawn(1, 6, true)))
		{
			cout << b.board[40] << endl;
			cout << "Test Failed";
		}
		else
			cout << "Test Passed" << endl;
	}

};