/**************************************************
 * QUEEN HEADER FILE
 **************************************************/
#pragma once

#include "uiDraw.h"
#include "move.h"
#include "piece.h"
#include "board.h"

#include <memory>
#include <list>

class TestQueen;

/**************************************************
 * QUEEN
 * A Queen chess piece
 **************************************************/
class Queen : public Piece
{
public:
   friend TestQueen;

   Queen() : Piece() {}
   Queen(int col, int row, bool white) : Piece(col, row, white) {}
   Queen(Position position, bool white) : Piece(position, white) {}
   char getLetter() const { return 'q'; }
   std::list<Move> getMoves(const Board& board) const;
   virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Queen>(*this); };
   void draw(ogstream& gout) const;
};
