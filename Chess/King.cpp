/**************************************************
 * KING SOURCE FILE
 **************************************************/

#include "uiDraw.h"
#include "king.h"
#include "move.h"
#include "position.h"
#include "piece.h"

#include <list>
#include <cassert>

using namespace std;

/**************************************************
 * KING :: GET MOVES
 * Get all possible moves for the King
 **************************************************/
list<Move> King::getMoves(const Board& board) const
{
   list<Move> moves;

   // Normal moves
   Delta deltas[8]{
      { -1,  1 }, { 0,  1 }, { 1,  1 },
      { -1,  0 },            { 1,  0 },
      { -1, -1 }, { 0, -1 }, { 1, -1 }
   };

   for (auto& delta : deltas)
   {
      Position checkPos = position + delta;
      if (checkPos.isValid())
      {
         const Piece& piece = board.get(checkPos);
         if (piece == ' ' || piece.isWhite() != white)
         {
            Move move(position, checkPos, white);
            if (piece != ' ')
               move.setCapture(piece.getLetter());

            moves.push_back(move);
         }
      }
   }

   // Castling
   struct Castle
   {
      Position kingDest;
      Position corner;
      Delta offset;
      bool kingSide;
   };

   Castle castles[2]{
      {
         position + Delta{ 2, 0 },
         position + Delta{ 3, 0 },
         Delta{ 1, 0 },
         true
      },
      {
         position + Delta{ -2, 0 },
         position + Delta{ -4, 0 },
         Delta{ -1, 0 },
         false
      }
   };

   for (auto& castle : castles)
   {
      // King hasn't moved
      if (nMoves != 0)
         continue;

      assert(position.getCol() == 4);
      assert(position.getRow() == (white ? 0 : 7));
      assert(castle.corner.isValid());

      // Rook hasn't moved
      const Piece& rook = board.get(castle.corner);
      if (rook != 'r' || rook.getNMoves() != 0)
         continue;

      // All spaces in between are empty
      bool clear = true;
      Position checkPos = position + castle.offset;
      while (checkPos != castle.corner)
      {
         if (board.get(checkPos) != ' ')
            clear = false;

         checkPos += castle.offset;
      }

      if (clear)
      {
         Move move(position, castle.kingDest, white);
         castle.kingSide ? move.setCastleK() : move.setCastleQ();
         moves.push_back(move);
      }
   }

   return moves;
}

/**************************************************
 * KING :: DRAW
 **************************************************/
void King::draw(ogstream& gout) const
{
   gout.drawKing(position.getLocation(), !white);
}
