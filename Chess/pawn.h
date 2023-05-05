/**************************************************
 * PAWN HEADER FILE
 **************************************************/
#pragma once

#include "uiDraw.h"
#include "move.h"
#include "piece.h"
#include "board.h"

#include <memory>
#include <list>

class TestPawn;

/**************************************************
 * PAWN
 * A Pawn chess piece
 **************************************************/
class Pawn : public Piece
{
public:
   friend TestPawn;

   Pawn() : Piece() {}
   Pawn(int col, int row, bool white) : Piece(col, row, white) {}
   char getLetter() const { return 'p'; }
   std::list<Move> getMoves(const Board& board) const;
   virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Pawn>(*this); };
   void draw(ogstream& gout) const;
};
