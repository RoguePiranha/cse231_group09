/**************************************************
 * POSITION SOURCE FILE
 **************************************************/

#include "position.h"

using namespace std;

/**************************************************
 * POSITION :: SET
 * Set the position with a row and column
 **************************************************/
void Position::set(int col, int row)
{
   if (row < 0 || row > 7 || col < 0 || col > 7)
      location = -1;
   else
      location = col + row * 8;
}

/**************************************************
 * POSITION :: OPERATOR + DELTA
 **************************************************/
Position operator+(const Position& lhs, const Delta& rhs)
{
   Position newPos(lhs);
   newPos.adjustCol(rhs.col);
   newPos.adjustRow(rhs.row);
   return newPos;
}

/**************************************************
 * POSITION :: OPERATOR += DELTA
 **************************************************/
Position& Position::operator+=(const Delta& rhs)
{
   adjustCol(rhs.col);
   adjustRow(rhs.row);
   return *this;
}
