/**************************************************
 * TEST ROOK HEADER FILE
 **************************************************/
#pragma once

#include "rook.h"
#include "pawn.h"
#include "board.h"

#include <cassert>
#include <set>
#include <string>

using namespace std;

/**************************************************
 * TEST ROOK
 * Unit tests for the Rook class
 **************************************************/
class TestRook
{
public:
   void run()
   {
      getMoves_free();
      getMoves_blocked();
      getMoves_capture();
   }

private:

   void getMoves_free()
   {
      // setup
      Board board;
      board.clear();

      Rook rook;
      rook.white = true;
      rook.position = Position(4, 4); // e5
      board.assign(rook);

      assert(rook.position == Position(4, 4));

      // exercise
      auto moves = rook.getMoves(board);

      // verify
      set<string> expectedMoves{ "e5e8","e5e7","e5e6","e5a5","e5b5","e5c5","e5d5","e5f5","e5g5","e5h5","e5e4","e5e3","e5e2","e5e1" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);

   }  // cleanup


   void getMoves_blocked()
   {
      // setup
      Board board;
      board.clear();

      Rook rook;
      rook.white = true;
      rook.position = Position(4, 4); // e5
      board.assign(rook);

      Pawn pawn1(4, 5, true);  // "e5e6"
      board.assign(pawn1);
      Pawn pawn2(3, 4, true);  // "e5d5"
      board.assign(pawn2);
      Pawn pawn3(5, 4, true);  // "e5f5"
      board.assign(pawn3);
      Pawn pawn4(4, 3, true);  // "e5e4"
      board.assign(pawn4);

      // exercise
      auto moves = rook.getMoves(board);

      // verify
      set<string> expectedMoves{};
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);

      // cleanup
   }


   void getMoves_capture()
   {
      // setup
      Board board;
      board.clear();

      Rook rook;
      rook.white = true;
      rook.position = Position(4, 4); // e5
      board.assign(rook);

      Pawn pawn1(4, 5, false);  // "e5e6"
      board.assign(pawn1);
      Pawn pawn2(3, 4, false);  // "e5d5"
      board.assign(pawn2);
      Pawn pawn3(5, 4, false);  // "e5f5"
      board.assign(pawn3);
      Pawn pawn4(4, 3, false);  // "e5e4"
      board.assign(pawn4);

      // exercise
      auto moves = rook.getMoves(board);

      // verify
      set<string> expectedMoves{ "e5e6p", "e5d5p", "e5f5p", "e5e4p" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);

      // cleanup
   }
};
