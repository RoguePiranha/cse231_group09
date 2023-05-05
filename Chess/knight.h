/**************************************************
 * KNIGHT HEADER FILE
 **************************************************/
#pragma once

#include "uiDraw.h"
#include "move.h"
#include "piece.h"
#include "board.h"

#include <memory>
#include <list>

class TestKnight;

/**************************************************
 * KNIGHT
 * A Knight chess piece
 **************************************************/
class Knight : public Piece
{
public:
   friend TestKnight;

   Knight() : Piece() {}
   Knight(int col, int row, bool white) : Piece(col, row, white) {}
   char getLetter() const { return 'n'; }
   std::list<Move> getMoves(const Board& board) const;
   virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Knight>(*this); };
   void draw(ogstream& gout) const;
};
