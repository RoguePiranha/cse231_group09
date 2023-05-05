/**************************************************
 * QUEEN SOURCE FILE
 **************************************************/

#include "uiDraw.h"
#include "queen.h"
#include "move.h"
#include "position.h"
#include "piece.h"

#include <list>

using namespace std;

/**************************************************
 * QUEEN :: GET MOVES
 * Get all possible moves for the Queen
 **************************************************/
list<Move> Queen::getMoves(const Board& board) const
{
   list<Move> moves;
   Delta deltas[8]{
      { -1,  1 }, { 0,  1 }, { 1,  1 },
      { -1,  0 },            { 1,  0 },
      { -1, -1 }, { 0, -1 }, { 1, -1 }
   };
   for (auto& delta : deltas)
   {
      auto slideMoves = getSlideMoves(board, delta);
      moves.splice(moves.end(), slideMoves);
   }
   return moves;
}

/**************************************************
 * QUEEN :: DRAW
 **************************************************/
void Queen::draw(ogstream& gout) const
{
   gout.drawQueen(position.getLocation(), !white);
}
