/**************************************************
 * TEST QUEEN HEADER FILE
 **************************************************/
#pragma once

#include "pawn.h"
#include "queen.h"
#include "board.h"

#include <cassert>
#include <set>
#include <string>

using namespace std;

/**************************************************
 * TEST QUEEN
 * Unit tests for the Queen class
 **************************************************/
class TestQueen
{
public:
   void run()
   {
      getMoves_capture();
      getMoves_blocked();
      getMoves_bottomLeft();
   }

private:
   void getMoves_capture()
   {
      // setup
      Board board;
      board.clear();

      Queen queen;
      queen.white = true;
      queen.position = Position(4, 5); // e6
      board.assign(queen);

      Pawn pawn1(3, 6, false);
      board.assign(pawn1);
      Pawn pawn2(4, 6, false);
      board.assign(pawn2);
      Pawn pawn3(5, 6, false);
      board.assign(pawn3);
      Pawn pawn4(3, 5, false);
      board.assign(pawn4);
      Pawn pawn5(5, 5, false);
      board.assign(pawn5);
      Pawn pawn6(3, 4, false);
      board.assign(pawn6);
      Pawn pawn7(4, 4, false);
      board.assign(pawn7);
      Pawn pawn8(5, 4, false);
      board.assign(pawn8);

      // exercise
      auto moves = queen.getMoves(board);

      // verify
      set<string> expectedMoves{ "e6d7p", "e6e7p", "e6f7p", "e6d6p", "e6f6p", "e6d5p", "e6e5p", "e6f5p" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);
      assert(queen.position == Position(4, 5));

   }  // cleanup

   void getMoves_blocked()
   {
      // setup
      Board board;
      board.clear();

      Queen queen;
      queen.white = true;
      queen.position = Position(4, 5); // e6
      board.assign(queen);

      Pawn pawn1(3, 6, true);
      board.assign(pawn1);
      Pawn pawn2(4, 6, true);
      board.assign(pawn2);
      Pawn pawn3(5, 6, true);
      board.assign(pawn3);
      Pawn pawn4(3, 5, true);
      board.assign(pawn4);
      Pawn pawn5(5, 5, true);
      board.assign(pawn5);
      Pawn pawn6(3, 4, true);
      board.assign(pawn6);
      Pawn pawn7(4, 4, true);
      board.assign(pawn7);
      Pawn pawn8(5, 4, true);
      board.assign(pawn8);

      // exercise
      auto moves = queen.getMoves(board);

      // verify
      set<string> expectedMoves{ };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);
      assert(queen.position == Position(4, 5));

   }  // cleanup

   void getMoves_bottomLeft()
   {
      // setup
      Board board;
      board.clear();

      Queen queen;
      queen.white = true;
      queen.position = Position(0, 0); // e6
      board.assign(queen);

      // exercise
      auto moves = queen.getMoves(board);

      // verify
      set<string> expectedMoves{
         "a1a2", "a1a3", "a1a4", "a1a5", "a1a6", "a1a7", "a1a8",
         "a1b1", "a1c1", "a1d1", "a1e1", "a1f1", "a1g1", "a1h1",
         "a1b2", "a1c3", "a1d4", "a1e5", "a1f6", "a1g7", "a1h8",
      };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);
      assert(queen.position == Position(0, 0));

   }  // cleanup
};
