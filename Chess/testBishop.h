/**************************************************
 * TEST BISHOP HEADER FILE
 **************************************************/
#pragma once

#include "bishop.h"
#include "pawn.h"
#include "board.h"

#include <cassert>
#include <set>
#include <string>

using namespace std;

/**************************************************
 * TEST BISHOP
 * Unit tests for the Bishop class
 **************************************************/
class TestBishop
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

      Bishop bishop;
      bishop.white = true;
      bishop.position = Position(4, 4); // e5
      board.assign(bishop);

      assert(bishop.position == Position(4, 4));

      // exercise
      auto moves = bishop.getMoves(board);

      // verify
      set<string> expectedMoves{ "e5b8","e5h8","e5c7","e5g7","e5d6","e5f6","e5d4","e5f4","e5c3","e5g3","e5b2","e5h2","e5a1" };
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

      Bishop bishop;
      bishop.white = true;
      bishop.position = Position(4, 4); // e5
      board.assign(bishop);

      Pawn pawn1(3, 5, true);  // "e5d6"
      board.assign(pawn1);
      Pawn pawn2(5, 5, true);  // "e5f6"
      board.assign(pawn2);
      Pawn pawn3(3, 3, true);  // "e5d4"
      board.assign(pawn3);
      Pawn pawn4(5, 3, true);  // "e5f4"
      board.assign(pawn4);

      // exercise
      auto moves = bishop.getMoves(board);

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

      Bishop bishop;
      bishop.white = true;
      bishop.position = Position(4, 4); // e5
      board.assign(bishop);

      Pawn pawn1(3, 5, false);  // "e5d6"
      board.assign(pawn1);
      Pawn pawn2(5, 5, false);  // "e5f6"
      board.assign(pawn2);
      Pawn pawn3(3, 3, false);  // "e5d4"
      board.assign(pawn3);
      Pawn pawn4(5, 3, false);  // "e5f4"
      board.assign(pawn4);

      // exercise
      auto moves = bishop.getMoves(board);

      // verify
      set<string> expectedMoves{ "e5d6p", "e5f6p", "e5d4p", "e5f4p" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);

      // cleanup
   }
};
