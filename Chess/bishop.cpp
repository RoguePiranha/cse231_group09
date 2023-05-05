/**************************************************
 * BISHOP SOURCE FILE
 **************************************************/

#include "uiDraw.h"
#include "bishop.h"
#include "move.h"
#include "position.h"
#include "piece.h"

#include <list>

using namespace std;

/**************************************************
 * BISHOP :: GET MOVES
 * Get all possible moves for the Bishop
 **************************************************/
std::list<Move> Bishop::getMoves(const Board& board) const
{
   std::list<Move> moves;
   Delta deltas[4]{ {1,1}, {1,-1}, {-1,-1}, {-1,1} };
   for (auto& delta : deltas)
   {
      auto slideMoves = getSlideMoves(board, delta);
      moves.splice(moves.end(), slideMoves);
   }
   return moves;
}

/**************************************************
 * BISHOP :: DRAW
 **************************************************/
void Bishop::draw(ogstream& gout) const
{
   gout.drawBishop(position.getLocation(), !white);
}
