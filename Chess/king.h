/**************************************************
 * KING HEADER FILE
 **************************************************/
#pragma once

#include "uiDraw.h"
#include "move.h"
#include "piece.h"
#include "board.h"

#include <memory>
#include <list>

class TestKing;

/**************************************************
 * KING
 * A King chess piece
 **************************************************/
class King : public Piece
{
public:
   friend TestKing;

   King() : Piece() {}
   King(int col, int row, bool white) : Piece(col, row, white) {}
   char getLetter() const { return 'k'; }
   std::list<Move> getMoves(const Board& board) const;
   virtual std::unique_ptr<Piece> clone() const { return std::make_unique<King>(*this); };
   void draw(ogstream& gout) const;
};
