/**************************************************
 * TEST KNIGHT HEADER FILE
 **************************************************/
#pragma once

#include "knight.h"
#include "pawn.h"
#include "board.h"

#include <cassert>
#include <set>
#include <string>

using namespace std;

/**************************************************
 * TEST KNIGHT
 * Unit tests for the Knight class
 **************************************************/
class TestKnight
{
public:
   void run()
   {
      getMoves_free();
      getMoves_blocked();
      getMoves_capture();
   }

private:
   /**************************************************
    * GET MOVES FREE - Knight can move in all directions
    * +---a-b-c-d-e-f-g-h---+
    * |                     |
    * 8                     8
    * 7         *   *       7
    * 6       *       *     6
    * 5          (n)        5
    * 4       *       *     4
    * 3         *   *       3
    * 2                     2
    * 1                     1
    * |                     |
    * +---a-b-c-d-e-f-g-h---+
    **************************************************/
   void getMoves_free()
   {
      // setup
      Board board;
      board.clear();

      Knight knight;
      knight.white = true;
      knight.position = Position(4, 4); // e5
      board.assign(knight);

      assert(knight.position == Position(4, 4));

      // exercise
      auto moves = knight.getMoves(board);

      // verify
      set<string> expectedMoves{ "e5d7", "e5f7", "e5c6", "e5g6", "e5c4", "e5g4", "e5d3", "e5f3" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);

   }  // cleanup

   /**************************************************
    * GET MOVES BLOCKED - Knight is blocked in all directions
    * +---a-b-c-d-e-f-g-h---+
    * |                     |
    * 8                     8
    * 7        (p) (p)      7
    * 6      (p)     (p)    6
    * 5          (n)        5
    * 4      (p)     (p)    4
    * 3        (p) (p)      3
    * 2                     2
    * 1                     1
    * |                     |
    * +---a-b-c-d-e-f-g-h---+
    **************************************************/
   void getMoves_blocked()
   {
      // setup
      Board board;
      board.clear();

      Knight knight;
      knight.white = true;
      knight.position = Position(4, 4); // e5
      board.assign(knight);

      Pawn pawn1(3, 6, true);  // "e5d7"
      board.assign(pawn1);
      Pawn pawn2(5, 6, true);  // "e5f7"
      board.assign(pawn2);
      Pawn pawn3(2, 5, true);  // "e5c6"
      board.assign(pawn3);
      Pawn pawn4(6, 5, true);  // "e5g6"
      board.assign(pawn4);
      Pawn pawn5(2, 3, true);  // "e5c4"
      board.assign(pawn5);
      Pawn pawn6(6, 3, true);  // "e5g4"
      board.assign(pawn6);
      Pawn pawn7(3, 2, true);  // "e5d3"
      board.assign(pawn7);
      Pawn pawn8(5, 2, true);  // "e5f3"
      board.assign(pawn8);

      // exercise
      auto moves = knight.getMoves(board);

      // verify
      set<string> expectedMoves{};
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);

      // cleanup
   }

   /**************************************************
    * GET MOVES CAPTURE - Knight can capture in all directions
    * +---a-b-c-d-e-f-g-h---+
    * |                     |
    * 8                     8
    * 7        (P) (P)      7
    * 6      (P)     (P)    6
    * 5          (n)        5
    * 4      (P)     (P)    4
    * 3        (P) (P)      3
    * 2                     2
    * 1                     1
    * |                     |
    * +---a-b-c-d-e-f-g-h---+
    **************************************************/
   void getMoves_capture()
   {
      // setup
      Board board;
      board.clear();

      Knight knight;
      knight.white = true;
      knight.position = Position(4, 4); // e5
      board.assign(knight);

      Pawn pawn1(3, 6, false);  // "e5d7"
      board.assign(pawn1);
      Pawn pawn2(5, 6, false);  // "e5f7"
      board.assign(pawn2);
      Pawn pawn3(2, 5, false);  // "e5c6"
      board.assign(pawn3);
      Pawn pawn4(6, 5, false);  // "e5g6"
      board.assign(pawn4);
      Pawn pawn5(2, 3, false);  // "e5c4"
      board.assign(pawn5);
      Pawn pawn6(6, 3, false);  // "e5g4"
      board.assign(pawn6);
      Pawn pawn7(3, 2, false);  // "e5d3"
      board.assign(pawn7);
      Pawn pawn8(5, 2, false);  // "e5f3"
      board.assign(pawn8);

      // exercise
      auto moves = knight.getMoves(board);

      // verify
      set<string> expectedMoves{ "e5d7p", "e5f7p", "e5c6p", "e5g6p", "e5c4p", "e5g4p", "e5d3p", "e5f3p" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);

      // cleanup
   }
};
