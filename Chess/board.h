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
#include "json.hpp"

using namespace std;
using json = nlohmann::json;
enum Winner;
class TestBoard;

/**************************************************
 * BOARD
 * The chess board
 **************************************************/
class Board
{
public:
	friend TestBoard;
   Board() : currentMove(0) { reset(); }
   int getCurrentMove() const { return currentMove; }
   //void display(const Position& hover, const Position& selected) const {}
   const Piece& get(const Position& pos) const;
   void reset();
   void reset(char setup[64]);
   void clear();
   void move(const Move& move);
   void setCurrentMove(int currentMove) { this->currentMove = currentMove; }
   // For testing
   void assign(const Piece& piece) { board[piece.getPosition().getLocation()] = piece.clone(); }
   void draw(Interface* pUI, Winner winner) const;
   void save(const Board &board);
   void load(Board &board);
   json getBoardState() const;
   void setBoardState(const json& j);

private:
   array<unique_ptr<Piece>, 64> board;
   int currentMove;

   void moveTo(Position pos1, Position pos2);
};
