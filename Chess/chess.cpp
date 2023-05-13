/**************************************************
 * CHESS SOURCE FILE
 **************************************************/

#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for draw*
#include "testKing.h"     // for King unit tests
#include "testQueen.h"    // for Queen unit tests
#include "testBishop.h"   // for Bishop unit tests
#include "testKnight.h"   // for Knight unit tests
#include "testRook.h"     // for Rook unit tests
#include "testPawn.h"     // for Pawn unit tests
#include "TestBoard.h"
#include "board.h"
#include "game.h"

#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING

using namespace std;

//#define DEBUG

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface* pUI, void* p)
{
   Game* game = (Game*)p;
   game->advance(pUI);
   game->draw(pUI);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   Interface ui("Chess");

#ifdef _WIN32
   //  int    argc;
   //  LPWSTR * argv = CommandLineToArgvW(GetCommandLineW(), &argc);
   //  string filename = argv[1];
   //if (__argc == 2)
      //readFile(__argv[1], board);
#else // !_WIN32
   //if (argc == 2)
      //readFile(argv[1], board);
#endif // !_WIN32

#ifdef DEBUG
   TestKing testKing;
   testKing.run();
   TestQueen testQueen;
   testQueen.run();
   TestBishop testBishop;
   testBishop.run();
   TestKnight testKnight;
   testKnight.run();
   TestRook testRook;
   testRook.run();
   TestPawn testPawn;
   testPawn.run();
   TestBoard testBoard;
   testBoard.Run();

#endif

   Game game;

   ui.run(callBack, &game);

   return 0;
}
