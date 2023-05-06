/**************************************************
 * BOARD SCOURCE FILE
 **************************************************/

#include "uiInteract.h"
#include "board.h"
#include "space.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "game.h"

#include <cassert>
#include <memory>

using namespace std;

/**************************************************
 * BOARD :: GET
 * Get a piece from the board
 **************************************************/
const Piece& Board::get(const Position& pos) const
{
   if (!pos.isValid())
      throw "Cannot get piece from invalid position";

   return *board[pos.getLocation()];
}

/**************************************************
 * BOARD :: RESET
 * Set up the chess board with all the pieces
 **************************************************/
void Board::reset()
{
   char setup[64] = {
      'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
      'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
      'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'
   };
   for (int i = 0; i < 64; i++)
   {
      int row = i / 8;
      int col = i % 8;
      switch (setup[i])
      {
      case 'p':
         board[i] = make_unique<Pawn>(Pawn(col, row, i < 16));
         break;
      case 'r':
         board[i] = make_unique<Rook>(Rook(col, row, i < 16));
         break;
      case 'n':
         board[i] = make_unique<Knight>(Knight(col, row, i < 16));
         break;
      case 'b':
         board[i] = make_unique<Bishop>(Bishop(col, row, i < 16));
         break;
      case 'q':
         board[i] = make_unique<Queen>(Queen(col, row, i < 16));
         break;
      case 'k':
         board[i] = make_unique<King>(King(col, row, i < 16));
         break;
      default:
         board[i] = make_unique<Space>(Space(col, row, false));
         break;
      }
   }
}

void Board::reset(char setup[64])
{
    for (int i = 0; i < 64; i++)
    {
        int row = i / 8;
        int col = i % 8;
        switch (setup[i])
        {
        case 'p':
            board[i] = make_unique<Pawn>(Pawn(col, row, false));
            break;
        case 'P':
            board[i] = make_unique<Pawn>(Pawn(col, row, true));
            break;
        case 'r':
            board[i] = make_unique<Rook>(Rook(col, row, false));
            break;
        case 'R':
            board[i] = make_unique<Rook>(Rook(col, row, true));
            break;
        case 'n':
            board[i] = make_unique<Knight>(Knight(col, row, false));
            break;
        case 'N':
            board[i] = make_unique<Knight>(Knight(col, row, true));
            break;
        case 'b':
            board[i] = make_unique<Bishop>(Bishop(col, row, false));
            break;
        case 'B':
            board[i] = make_unique<Bishop>(Bishop(col, row, true));
            break;
        case 'q':
            board[i] = make_unique<Queen>(Queen(col, row, false));
            break;
        case 'Q':
            board[i] = make_unique<Queen>(Queen(col, row, true));
            break;
        case 'k':
            board[i] = make_unique<King>(King(col, row, false));
            break;
        case 'K':
            board[i] = make_unique<King>(King(col, row, true));
            break;
        default:
            board[i] = make_unique<Space>(Space(col, row, false));
            break;
        }
    }
}

/**************************************************
 * BOARD :: CLEAR
 * Fill the board with spaces
 **************************************************/
void Board::clear()
{
   for (int i = 0; i < 64; i++)
   {
      int row = i / 8;
      int col = i % 8;
      board[i] = make_unique<Space>(Space(row, col, i < 16));
   }
}

/**************************************************
 * BOARD :: MOVE
 * Apply a move to the board
 **************************************************/
void Board::move(const Move& move)
{
   Position src = move.getSrc();
   Position dest = move.getDest();
   if (!src.isValid() || !dest.isValid())
      throw "One of the positions is invalid";

   if (get(src) == ' ')
      throw "Cannot perform a move on a space";

   moveTo(src, dest);

   // Check for En Passant
   if (move.getEnPassant())
   {
      Position sides[2]{
         src + Delta{ -1, 0 },
         src + Delta{  1, 0 }
      };
      bool didEnpassant = false;
      for (const Position& side : sides)
      {
         if (side.isValid())
         {
            const Piece& piece = get(side);
            if (piece == 'p' 
               && piece.justMoved(*this)
               && piece.isWhite() != move.isWhiteMove())
            {
               board[side.getLocation()] = make_unique<Space>(Space());
               didEnpassant = true;
            }
         }
      }

      if (!didEnpassant)
         throw "There was not a pawn to En Passant";
   }

   // Check promotion to Queen
   if (move.getPromotion() == 'Q')
   {
      Queen queen(dest, move.isWhiteMove());
      board[dest.getLocation()] = make_unique<Queen>(queen);
   }

   // Check king-side castle
   if (move.getCastleK())
   {
      Position corner = src + Delta{ 3, 0 };
      Position castlePosition = src + Delta{ 1, 0 };
      if (!corner.isValid() || get(corner) != 'r')
         throw "Cannot castle, rook is in wrong position";

      moveTo(corner, castlePosition);
   }

   // Check queen-side castle
   if (move.getCastleQ())
   {
      Position corner = src + Delta{ -4, 0 };
      Position castlePosition = src + Delta{ -1, 0 };
      if (!corner.isValid() || get(corner) != 'r')
         throw "Cannot castle, rook is in wrong position";

      moveTo(corner, castlePosition);
   }

   board[dest.getLocation()]->setMove(currentMove);
   currentMove += 1;
}

/**************************************************
 * BOARD :: MOVE TO
 * Move a piece from source to destination
 **************************************************/
void Board::moveTo(Position src, Position dest)
{
   board[dest.getLocation()] = get(src).clone();
   board[dest.getLocation()]->setPosition(dest);
   board[src.getLocation()] = make_unique<Space>(Space());
}

/**************************************************
 * BOARD :: DRAW
 * Draw the board and pieces, as well as click and hover positions
 * if the game is ongoing
 **************************************************/
void Board::draw(Interface* pUI, Winner winner) const
{
   ogstream gout;

   gout.drawBoard();

   if (winner == NONE)
   {
      // Draw any selections
      gout.drawHover(pUI->getHoverPosition());
      gout.drawSelected(pUI->getSelectPosition());
      if (pUI->getSelectPosition() >= 0 && pUI->getSelectPosition() < 64)
      {
         // Draw the possible moves
         list<Move> possible = board[pUI->getSelectPosition()]->getMoves(*this);
         for (auto move : possible)
            gout.drawPossible(move.getDest().getLocation());
      }
   }
   else
   {
      gout.setPosition(80, 124);
      gout << (winner == BLACK ? "Black Wins!" : "White Wins!");
   }

   for (auto& piece : board)
      piece->draw(gout);
}
