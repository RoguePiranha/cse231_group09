/**************************************************
 * ROOK HEADER FILE
 **************************************************/
#pragma once

#include "uiDraw.h"
#include "move.h"
#include "piece.h"
#include "board.h"

#include <memory>
#include <list>

using namespace::std;
class TestRook;
class TestKing;

/**************************************************
 * ROOK
 * A Rook chess piece
 **************************************************/
class Rook : public Piece
{
public:
   friend TestRook;
   friend TestKing;

   Rook() : Piece() {}
   Rook(int col, int row, bool white) : Piece(col, row, white) {}
   char getLetter() const { return 'r'; }
   std::list<Move> getMoves(const Board& board) const;
   virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Rook>(*this); };
   void draw(ogstream& gout) const;
};
