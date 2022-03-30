#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "minesweeperLib.h"

/**
 * @brief Constants
 */

const unsigned char MODULE_VERSION[] = "V2.0";
Cell getCellByCoordinates(int x , int y);
Cell * getCellPtrByCoordinates(int x , int y);


/**
 * @brief Globals
 */
Game game;
/**
 * @brief Utility functions
 */

bool isValid(int row, int col)
{
    return (row >= 0) && (row < SIDE) &&
           (col >= 0) && (col < SIDE);
}
void MS_getGameState(Game destBoard)
{
   memcpy(&destBoard,&game,sizeof(Game));
}

/**
 * @brief Returns null terminated string of 4 characters
 */
const unsigned char *MS_getModuleVersion(void)
{
    return MODULE_VERSION;
}

void initGame(void)
{
    game.mineCnt = MINE_CNT;
    game.remainingMoves = SIDE * SIDE - MINE_CNT;

    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            game.cells[i * SIDE + j].cellState = initial;
            game.cells[i * SIDE + j].x = i * SIDE;
            game.cells[i * SIDE + j].y = j;
        }
    }
}

void addMines(void)
{
    for (int mineInd = 0; mineInd < MINE_CNT; mineInd++)
    {
        int x = game.mines[mineInd].x
        int y = game.mines[mineInd].y;
        Cell *cell = getCellPtrByCoordinates(x,y);
        cell->cellState = hasmine;
    }
}


Cell getCellByCoordinates(int x , int y)
{
    Cell currCell;
     for (int i = 0; i < SIDE; i++)
        {
            for (int j = 0; j < SIDE; j++)
            {
                currCell = game.cells[i * SIDE + j];
                if(currCell.x == x && currCell.y == y)
                    break;
                
            }
        }

    return currCell;
}

Cell * getCellPtrByCoordinates(int x , int y)
{
    Cell *currCell;
     for (int i = 0; i < SIDE; i++)
        {
            for (int j = 0; j < SIDE; j++)
            {
                currCell = &game.cells[i * SIDE + j];
                if(currCell->x == x && currCell->y == y)
                    break;
                
            }
        }

    return currCell;
}
/**
 * @brief Initialise a new board with len x width squares
 */
MS_LIB_STATUS_CODES MS_GenRandomMines()
{

    initGame();

    /* Intializes random number generator */
    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < MINE_CNT; i++)
    {
        int x = (rand() * (SIDE * SIDE)) / SIDE;
        int y = (rand() * (SIDE * SIDE)) % SIDE;
        game.mines[i].cellState = hasmine;
        game.mines[i].x = x;
        game.mines[i].y = y;
    }

    addMines();

    return MS_LIB_STATUS_OK;
}

/**
 * @brief Initialise a new board with len x width squares using specified mine positions
 */
MS_LIB_STATUS_CODES MS_GenUserProvidedMines( unsigned int minePositions[][2])
{
    initGame();
    for (int i = 0; i < MINE_CNT; i++)
    {
        unsigned int x = minePositions[i][0];
        unsigned int y = minePositions[i][1];

        game.mines[i].cellState = hasmine;
        game.mines[i].x = x;
        game.mines[i].y = y;
    }

    addMines();
   return MS_LIB_STATUS_OK;

}

bool isClearedAlready(int x, int y)
{
    Cell cell = getCellByCoordinates(x,y);
    return (cell.cellState == cleared);
}
bool isMine(int x, int y)
{
    Cell cell = getCellByCoordinates(x,y);
    return (cell.cellState == hasmine);
}


// A Function to count the number of
// mines in the adjacent cells
int checkNeighbours(int row, int col)
{

    int i;
    int count = 0;
    Cell cell = getCellByCoordinates(row,col);
    if (isValid(row - 1, col) == true)
    {
        if (isMine(row - 1, col) == true)
            count++;
    }

    //----------- 2nd Neighbour (South) ------------

    // Only process this cell if this is a valid one
    if (isValid(row + 1, col) == true)
    {
        if (isMine(row + 1, col) == true)
            count++;
    }

    //----------- 3rd Neighbour (East) ------------

    // Only process this cell if this is a valid one
    if (isValid(row, col + 1) == true)
    {
        if (isMine(row, col + 1) == true)
            count++;
    }

    //----------- 4th Neighbour (West) ------------

    // Only process this cell if this is a valid one
    if (isValid(row, col - 1) == true)
    {
        if (isMine(row, col - 1) == true)
            count++;
    }

    //----------- 5th Neighbour (North-East) ------------

    // Only process this cell if this is a valid one
    if (isValid(row - 1, col + 1) == true)
    {
        if (isMine(row - 1, col + 1) == true)
            count++;
    }

    //----------- 6th Neighbour (North-West) ------------

    // Only process this cell if this is a valid one
    if (isValid(row - 1, col - 1) == true)
    {
        if (isMine(row - 1, col - 1) == true)
            count++;
    }

    //----------- 7th Neighbour (South-East) ------------

    // Only process this cell if this is a valid one
    if (isValid(row + 1, col + 1) == true)
    {
        if (isMine(row + 1, col + 1) == true)
            count++;
    }

    //----------- 8th Neighbour (South-West) ------------

    // Only process this cell if this is a valid one
    if (isValid(row + 1, col - 1) == true)
    {
        if (isMine(row + 1, col - 1) == true)
            count++;
    }

    return (count);
}

MS_LIB_STATUS_CODES MS_executeGame(char command, unsigned int x, unsigned int y)
{
    MS_LIB_STATUS_CODES gameState = MS_LIB_STATUS_GAME_IN_POGRESS;

    switch (command)

    {
    case 'C':
    case 'c':
    {
        if (isMine(x, y))
        {
            gameState = MS_LIB_STATUS_GAME_LOST;
        }
        else
        {
            if (isClearedAlready(x, y))
            {
                printf("\n cell cleared already");
                gameState = MS_LIB_STATUS_CELL_CLEARED_ALREADY;
            }
            else
            {
                int adjacentMines = checkNeighbours(x, y);
                if (adjacentMines != 0)
                {
                   Cell *cell = getCellPtrByCoordinates(x,y);
                   cell->adjMineCnt=adjacentMines;
                }
            }
        }
    }
        break;

    case 'F':
    case 'f':
        {
         Cell *cell = getCellPtrByCoordinates(x,y);
         if(cell->cellState!=cleared)
           { 
               cell->cellState=flagged;
           }
        }
        break;

    default:
        gameState = MS_LIB_STATUS_INVALID_CMD;
        break;
    }

    if (gameState == MS_LIB_STATUS_GAME_IN_POGRESS)
    {
        if (--game.remainingMoves == 0)
        {
            gameState = MS_LIB_STATUS_GAME_WON;
        }
    }
    return gameState;
}