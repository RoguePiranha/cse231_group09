/**************************************************
 * PIECE SOURCE FILE
 **************************************************/

#include "piece.h"
#include "board.h"

#include <list>

using namespace std;

/**************************************************
 * PIECE :: JUST MOVED
 * Determine if a piece moved during the last turn
 **************************************************/
bool Piece::justMoved(const Board& board) const
{
   return board.getCurrentMove() - lastMove == 1;
}

/**************************************************
 * PIECE :: GET SLIDE MOVES
 * Get a list of moves from sliding in a given direction
 **************************************************/
list<Move> Piece::getSlideMoves(const Board& board, const Delta& delta) const
{
   list<Move> moves;
   Position checkPos(position);
   bool blocked = false;
   while (!blocked)
   {
      checkPos += delta;
      if (checkPos.isValid())
      {
         const Piece& piece = board.get(checkPos);
         if (piece == ' ' || piece.isWhite() != white)
         {
            Move move(position, checkPos, white);
            if (piece != ' ')
            {
               move.setCapture(piece.getLetter());
               blocked = true;
            }
            moves.push_back(move);
         }
         else
            blocked = true;
      }
      else
         blocked = true;
   }
   return moves;
}

/**************************************************
 * OPERATOR == PIECE, CHAR
 **************************************************/
bool operator==(const Piece& lhs, char rhs)
{
   return lhs.getLetter() == rhs;
}

/**************************************************
 * OPERATOR != PIECE, CHAR
 **************************************************/
bool operator!=(const Piece& lhs, char rhs)
{
   return !(lhs == rhs);
}
