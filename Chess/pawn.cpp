/**************************************************
 * PAWN SOURCE FILE
 **************************************************/

#include "uiDraw.h"
#include "pawn.h"
#include "move.h"
#include "board.h"
#include "position.h"
#include "piece.h"

#include <list>

using namespace std;

/**************************************************
 * PAWN :: GET MOVES
 * Get all possible moves for the Pawn
 **************************************************/
list<Move> Pawn::getMoves(const Board& board) const
{
   list<Move> moves;
   int lastRow = white ? 7 : 0;

   // Normal move
   Position oneAhead = position + Delta{ 0, white ? 1 : -1 };
   if (oneAhead.isValid() && board.get(oneAhead).getLetter() == ' ')
   {
      Move move(position, oneAhead, white);
      if (oneAhead.getRow() == lastRow)
         move.setPromotion('Q');
      moves.push_back(move);
   }

   // Move two spaces
   if (nMoves == 0)
   {
      Position twoAhead = position + Delta{ 0, white ? 2 : -2 };
      if (twoAhead.isValid()
         && board.get(oneAhead).getLetter() == ' '
         && board.get(twoAhead).getLetter() == ' '
         )
         moves.push_back(Move(position, twoAhead, white));
   }

   // Diagonal capture
   Position diagonals[2]{
      oneAhead + Delta{  1, 0 },
      oneAhead + Delta{ -1, 0 }
   };
   for (const auto& diagonal : diagonals)
   {
      if (diagonal.isValid())
      {
         const Piece& opponent = board.get(diagonal);
         if (opponent.getLetter() != ' ' && opponent.isWhite() != white)
         {
            Move move(position, diagonal, white);
            move.setCapture(opponent.getLetter());

            // Capture w/ promotion
            if (diagonal.getRow() == lastRow)
               move.setPromotion('Q');
            moves.push_back(move);
         }
      }
   }

   // En Passant
   struct EnPassant
   {
      Position pawnPos;
      Position attackPos;
   };

   int enpassantRow = white ? 4 : 3;
   if (position.getRow() == enpassantRow)
   {
      EnPassant sides[2]{
         {position + Delta{  1, 0 }, oneAhead + Delta{  1, 0 }},
         {position + Delta{ -1, 0 }, oneAhead + Delta{ -1, 0 }}
      };
      for (const auto& side : sides)
      {
         if (side.pawnPos.isValid())
         {
            const Piece& opponent = board.get(side.pawnPos);
            if (opponent.getLetter() == 'p'
               && opponent.isWhite() != white
               && opponent.justMoved(board)
               )
            {
               Move move(position, side.attackPos, white);
               move.setEnPassant();
               moves.push_back(move);
            }
         }
      }
   }

   return moves;
}

/**************************************************
 * PAWN :: DRAW
 **************************************************/
void Pawn::draw(ogstream& gout) const
{
   gout.drawPawn(position.getLocation(), !white);
}
