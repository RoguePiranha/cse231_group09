/**************************************************
 * BISHOP HEADER FILE
 **************************************************/
#pragma once

#include "uiDraw.h"
#include "move.h"
#include "piece.h"
#include "board.h"

#include <memory>
#include <list>

class TestBishop;

/**************************************************
 * BISHOP
 * A Bishop chess piece
 **************************************************/
class Bishop : public Piece
{
public:
   friend TestBishop;

   Bishop() : Piece() {}
   Bishop(int col, int row, bool white) : Piece(col, row, white) {}
   char getLetter() const { return 'p'; }
   std::list<Move> getMoves(const Board& board) const;
   virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Bishop>(*this); };
   void draw(ogstream& gout) const;
};
