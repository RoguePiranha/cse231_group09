/**************************************************
 * TEST PAWN HEADER FILE
 **************************************************/
#pragma once

#include "pawn.h"
#include "board.h"

#include <cassert>
#include <set>
#include <string>

using namespace std;

/**************************************************
 * TEST PAWN
 * Unit tests for the Pawn class
 **************************************************/
class TestPawn
{
public:
   void run()
   {
      getMoves_blocked();
      getMoves_simpleMove();
      getMoves_initialMove();
      getMoves_capture();
      getMoves_enpassant();
      getMoves_promotion();
      cout << "\033[32m" << "Pawn Test Passed." << "\033[0m" << endl;
   }

private:
 
   void getMoves_blocked()
   {
      // setup
      Board board;
      board.clear();

      Pawn pawn;
      pawn.white = true;
      pawn.position = Position(3, 3); // d4
      pawn.nMoves = 1;
      board.assign(pawn);

      Pawn pawn2;
      pawn2.white = false;
      pawn2.position = Position(3, 4); // d5
      pawn2.nMoves = 1;
      board.assign(pawn2);

      // exercise
      auto moves = pawn.getMoves(board);

      // verify
      set<string> expectedMoves{};
      set<string> actualMoves{};
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);
      assert(pawn.position == Position(3, 3));
      assert(pawn2.position == Position(3, 4));

   }  // cleanup


   void getMoves_simpleMove()
   {
      // setup
      Board board;
      board.clear();

      Pawn pawn;
      pawn.white = true;
      pawn.position = Position(1, 3); // b4
      pawn.nMoves = 2;
      board.assign(pawn);

      // exercise
      auto moves = pawn.getMoves(board);

      // verify
      set<string> expectedMoves{ "b4b5" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);
      assert(pawn.position == Position(1, 3));

   }  // cleanup


   void getMoves_initialMove()
   {
      // setup
      Board board;
      board.clear();

      Pawn pawn;
      pawn.white = true;
      pawn.position = Position(1, 1); // b2
      pawn.nMoves = 0;
      board.assign(pawn);

      // exercise
      auto moves = pawn.getMoves(board);

      // verify
      set<string> expectedMoves{ "b2b3", "b2b4" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);
      assert(pawn.position == Position(1, 1));

   }  // cleanup


   void getMoves_capture()
   {
      // setup
      Board board;
      board.clear();

      Pawn pawn;
      pawn.white = true;
      pawn.position = Position(1, 5); // b6
      pawn.nMoves = 1;
      board.assign(pawn);

      Pawn pawn2;
      pawn2.white = false;
      pawn2.position = Position(0, 6); // a7
      pawn2.nMoves = 1;
      board.assign(pawn2);

      Pawn pawn3;
      pawn3.white = false;
      pawn3.position = Position(1, 6); // b7
      pawn3.nMoves = 1;
      board.assign(pawn3);

      Pawn pawn4;
      pawn4.white = false;
      pawn4.position = Position(2, 6); // c7
      pawn4.nMoves = 1;
      board.assign(pawn4);

      // exercise
      auto moves = pawn.getMoves(board);

      // verify
      set<string> expectedMoves{ "b6a7p", "b6c7p" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);
      assert(pawn.position == Position(1, 5));
      assert(pawn2.position == Position(0, 6));
      assert(pawn3.position == Position(1, 6));
      assert(pawn4.position == Position(2, 6));

   }  // cleanup


   void getMoves_enpassant()
   {
      // setup
      Board board;
      board.clear();
      board.setCurrentMove(2);

      Pawn pawn;
      pawn.white = true;
      pawn.position = Position(1, 4); // b5
      pawn.nMoves = 2;
      board.assign(pawn);

      Pawn pawn2;
      pawn2.white = false;
      pawn2.position = Position(1, 5); // b6
      pawn2.nMoves = 1;
      board.assign(pawn2);

      Pawn pawn3;
      pawn3.white = false;
      pawn3.position = Position(0, 4); // a5
      pawn3.nMoves = 1;
      pawn3.lastMove = 1;
      board.assign(pawn3);

      Pawn pawn4;
      pawn4.white = false;
      pawn4.position = Position(2, 4); // c5
      pawn4.nMoves = 1;
      pawn4.lastMove = 1;
      board.assign(pawn4);

      // exercise
      auto moves = pawn.getMoves(board);

      // verify
      set<string> expectedMoves{ "b5c6E", "b5a6E" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);
      assert(pawn.position == Position(1, 4));
      assert(pawn2.position == Position(1, 5));
      assert(pawn3.position == Position(0, 4));
      assert(pawn4.position == Position(2, 4));

   }  // cleanup


   void getMoves_promotion()
   {
      // setup
      Board board;
      board.clear();

      Pawn pawn;
      pawn.white = true;
      pawn.position = Position(1, 6); // b7
      board.assign(pawn);

      Pawn pawn2;
      pawn2.white = false;
      pawn2.position = Position(0, 7); // b7
      board.assign(pawn2);

      Pawn pawn3;
      pawn3.white = false;
      pawn3.position = Position(2, 7); // b7
      board.assign(pawn3);

      // exercise
      auto moves = pawn.getMoves(board);

      // verify
      set<string> expectedMoves{ "b7a8pQ", "b7b8Q", "b7c8pQ" };
      set<string> actualMoves;
      for (auto& move : moves)
         actualMoves.insert(move.getText());

      assert(expectedMoves == actualMoves);
      assert(pawn.position == Position(1, 6));

   }  // cleanup
};
