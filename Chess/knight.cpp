/**************************************************
 * KNIGHT SOURCE FILE
 **************************************************/

#include "uiDraw.h"
#include "knight.h"
#include "move.h"
#include "position.h"
#include "piece.h"

#include <list>

using namespace std;

/**************************************************
 * KNIGHT :: GET MOVES
 * Get all possible moves for the Knight
 **************************************************/
list<Move> Knight::getMoves(const Board& board) const
{
   list<Move> moves;
   Delta deltas[8]{
             { -1,  2 }, { 1,  2 },
      { -2,  1 },              { 2,  1 },
      { -2, -1 },              { 2, -1 },
             { -1, -2 }, { 1, -2 }
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
   return moves;
}

/**************************************************
 * KNIGHT :: DRAW
 **************************************************/
void Knight::draw(ogstream& gout) const
{
   gout.drawKnight(position.getLocation(), !white);
}
