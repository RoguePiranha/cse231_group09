/**************************************************
 * GAME SOURCE FILE
 **************************************************/

#include "uiInteract.h"
#include "position.h"
#include "game.h"
#include "piece.h"
#include "move.h"

#include <set>

using namespace std;

/**************************************************
 * GAME :: ADVANCE
 * If the game is ongoing,
 **************************************************/
void Game::advance(Interface* pUI)
{
   if (winner != NONE) return;

   int prevPos = pUI->getPreviousPosition();
   int selectPos = pUI->getSelectPosition();
   if (prevPos >= 0 && prevPos < 64)
   {
      // For each possible move, check whether the selected space
      // matches the destination space
      const Piece& previousPiece = board.get(prevPos);
      auto possibleMoves = previousPiece.getMoves(board);
      for (const auto& move : possibleMoves)
      {
         if (move.getDest() == Position(selectPos))
         {
            // If the king is captured, declare the winner
            const Piece& capture = board.get(selectPos);
            if (capture == 'k')
               winner = capture.isWhite() ? BLACK : WHITE;

            // Perform the move and switch turns
            board.move(move);
            whiteTurn = !whiteTurn;
            pUI->clearSelectPosition();
            return;
         }
      }
   }

   // Prevent selecting spaces or pieces of the wrong color
   if (selectPos >= 0 && selectPos < 64)
   {
      const Piece& selectedPiece = board.get(selectPos);
      if (selectedPiece == ' ' || selectedPiece.isWhite() != whiteTurn)
      {
         pUI->clearSelectPosition();
      }
   }
};

/**************************************************
 * GAME :: DRAW
 * Just tell the board to draw itself
 **************************************************/
void Game::draw(Interface* pUI)
{
   board.draw(pUI, winner);
};
