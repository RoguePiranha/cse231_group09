/**************************************************
 * SPACE HEADER FILE
 **************************************************/

#include "uiDraw.h"
#include "move.h"
#include "piece.h"
#include "board.h"

#include <memory>
#include <list>

/**************************************************
 * SPACE
 * An empty space on the chess board, behaving as a piece
 **************************************************/
class Space : public Piece
{
public:
   Space() : Piece() {}
   Space(int col, int row, bool white) : Piece(col, row, white) {}
   char getLetter() const { return ' '; }
   std::list<Move> getMoves(const Board& board) const { return std::list<Move>(); };
   virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Space>(*this); };
   void draw(ogstream& gout) const {};
};
