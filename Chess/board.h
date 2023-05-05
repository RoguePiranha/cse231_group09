/**************************************************
 * BOARD HEADER FILE
 **************************************************/
#pragma once

#include "uiInteract.h"
#include "uiDraw.h"
#include "piece.h"
#include "position.h"
#include "move.h"

#include <memory>
#include <array>

enum Winner;

/**************************************************
 * BOARD
 * The chess board
 **************************************************/
class Board
{
public:
   Board() : currentMove(0) { reset(); }
   int getCurrentMove() const { return currentMove; }
   void display(const Position& hover, const Position& selected) const {}
   const Piece& get(const Position& pos) const;
   void reset();
   void clear();
   void move(const Move& move);
   void setCurrentMove(int currentMove) { this->currentMove = currentMove; }
   void assign(const Piece& piece) { board[piece.getPosition().getLocation()] = piece.clone(); }
   void draw(Interface* pUI, Winner winner) const;

private:
   std::array<std::unique_ptr<Piece>, 64> board;
   int currentMove;

   void moveTo(Position pos1, Position pos2);
};
