/**************************************************
 * MOVE SOURCE FILE
 **************************************************/

#include "uiDraw.h"
#include "move.h"

#include <iostream>
#include <string>

using namespace std;

/**************************************************
 * MOVE :: GET TEXT
 * Get the Smith-Notation for the move
 **************************************************/
string Move::getText() const
{
   string text = "";
   text += (char)('a' + source.getCol());
   text += (char)('1' + source.getRow());

   text += (char)('a' + dest.getCol());
   text += (char)('1' + dest.getRow());

   if ('a' <= capture && capture < 'z')
      text += capture;

   if ('A' <= piece && piece <= 'Z')
      text += piece;

   if (enpassant)
      text += 'E';

   if (castleK)
      text += 'c';

   if (castleQ)
      text += 'C';

   return text;
}

/**************************************************
 * OPERATOR << MOVE
 **************************************************/
ostream& operator<<(ostream& out, const Move& move)
{
   out << move.getText();
   return out;
}
