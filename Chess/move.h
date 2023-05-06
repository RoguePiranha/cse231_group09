/**************************************************
 * MOVE HEADER FILE
 **************************************************/
#pragma once

#include "position.h"

#include <iostream>
#include <string>

class TestBoard;
 /**************************************************
  * MOVE
  * Represents the different types of moves in chess
  **************************************************/
class Move
{
public:
   Move() :
      piece(' '),
      capture(' '),
      enpassant(false),
      castleK(false),
      castleQ(false),
      isWhite(false) {}
   Move(Position source, Position dest, bool isWhite) :
      source(source),
      dest(dest),
      piece(' '),
      capture(' '),
      enpassant(false),
      castleK(false),
      castleQ(false),
      isWhite(isWhite) {}
   std::string getText() const;
   Position getSrc() const { return source; }
   Position getDest() const { return dest; }
   char getPromotion() const { return piece; }
   char getCapture() const { return capture; }
   bool getEnPassant() const { return enpassant; }
   bool getCastleK() const { return castleK; }
   bool getCastleQ() const { return castleQ; }
   bool isWhiteMove() const { return isWhite; }
   void setPromotion(char piece) { this->piece = piece; }
   void setCapture(char capture) { this->capture = capture; }
   void setEnPassant() { enpassant = true; }
   void setCastleK() { castleK = true; }
   void setCastleQ() { castleQ = true; }
   void setWhiteMove(bool isWhite) { this->isWhite = isWhite; }
   friend TestBoard;
private:
   Position source;
   Position dest;
   char piece;
   char capture;
   bool enpassant;
   bool castleK;
   bool castleQ;
   bool isWhite;
};

std::ostream& operator<<(std::ostream& out, const Move& move);
