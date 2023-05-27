/**************************************************
 * GAME HEADER FILE
 **************************************************/
#pragma once

#include "uiInteract.h"
#include "board.h"

enum Winner
{
    WHITE,
    BLACK,
    NONE
};

/**************************************************
 * GAME
 * Contains the logic to run the Chess game
 **************************************************/
class Game
{
public:
    Game()
    {
        whiteTurn = true;
        board.reset();
        winner = NONE;
    }
    void advance(Interface* pUI);
    void draw(Interface* pUI);

private:
    bool whiteTurn;
    Board board;
    Winner winner;
};