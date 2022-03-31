#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "minesweeperLib.h"

/**
 * @brief Constants
 */

const unsigned char MODULE_VERSION[] = "V2.0";

/**
 * @brief Extern function declarations
 */
Cell getCellByCoordinates(int x, int y);
void MS_getGameState(Game *destBoard);
const unsigned char *MS_getModuleVersion(void);
MS_LIB_STATUS_CODES MS_GenRandomMines();
MS_LIB_STATUS_CODES MS_GenUserProvidedMines(unsigned int minePositions[][2]);

/**
 * @brief Static functions declarations
 */
static Cell *getCellPtrByCoordinates(int x, int y);

/**
 * @brief Globals
 */
Game game;

/**
 * @brief Utility functions
 */

/**
 * @brief checks if given cartessian coordinates are within the game plane
 */
bool isValid(int row, int col)
{
    return (row >= 0) && (row < game.side) &&
           (col >= 0) && (col < game.side);
}

/**
 * @brief copies internal game state to destination
 */
void MS_getGameState(Game *destBoard)
{
    memcpy(destBoard, &game, sizeof(Game));
}

/**
 * @brief Returns null terminated string of 4 characters to represent module version
 */
const unsigned char *MS_getModuleVersion(void)
{
    return MODULE_VERSION;
}

/**
 * @brief initialises a game to default values
 */
MS_LIB_STATUS_CODES MS_initGame(unsigned int mineCnt, unsigned int gameBoardSize)
{
    if (mineCnt > MAX_MINE)
        return MS_LIB_STATUS_INVALID_MINE_CNT;
    if (gameBoardSize > MAX_SIDE)
        return MS_LIB_STATUS_BOARD_SIZE_EXCEEDS_LIMIT;

    game.mineCnt = mineCnt;
    game.side = gameBoardSize;
    game.remainingMoves = game.side * game.side - game.mineCnt;

    for (int i = 0; i < game.side * game.side; i++)
    {
        game.cells[i].cellState = initial;
        game.cells[i].x = i / game.side;
        game.cells[i].y = i % game.side;
    }
    return MS_LIB_STATUS_OK;
}

/**
 * @brief reads the mine positions and sets them in actual game cells
 */
void addMines(void)
{
    for (int mineInd = 0; mineInd < game.mineCnt; mineInd++)
    {
        int x = game.mines[mineInd].x;
        int y = game.mines[mineInd].y;
        Cell *cell = getCellPtrByCoordinates(x, y);
        cell->cellState = hasmine;
    }
}

/**
 * @brief Returns the copy of a cell in given coordinates.
 */
Cell getCellByCoordinates(int x, int y)
{
    Cell currCell;
    if (!isValid(x, y))
    {
        currCell.cellState = notvalid;
    }
    else
    {
        for (int i = 0; i < game.side * game.side; i++)
        {

            currCell = game.cells[i];
            if (currCell.x == x && currCell.y == y)
                break;
        }
    }
    return currCell;
}

/**
 * @brief Returns pointer to a cell in given coordinates.
 */
Cell *getCellPtrByCoordinates(int x, int y)
{
    Cell *currCell = 0;
    for (int i = 0; i < game.side * game.side; i++)
    {
        currCell = &game.cells[i];
        if (currCell->x == x && currCell->y == y)
            break;
        else
            currCell = 0;
    }

    return currCell;
}

/**
 * @brief Initialise a new board with random mine cells
 */
MS_LIB_STATUS_CODES MS_GenRandomMines()
{

    /* Intializes random number generator */
    time_t t;
    srand(time(NULL)); // Initialization, should only be called once.
    for (int i = 0; i < game.mineCnt; i++)
    {

        unsigned int random1 = 1 + (int) (10.0 * (rand() / (RAND_MAX + 1.0)));
        unsigned int random2 = 1 + (int) (10.0 * (rand() / (RAND_MAX + 1.0)));

        game.mines[i].cellState = initial;
        game.mines[i].x = random1 % game.side;
        game.mines[i].y = random2 % game.side;

        if (!isValid(game.mines[i].x, game.mines[i].y))
            return MS_LIB_STATUS_INVALID_LOCATION;

        game.mines[i].cellState = hasmine;

    }

    addMines();

    return MS_LIB_STATUS_OK;
}

/**
 * @brief Initialise a new board with user provided mine cells
 */
MS_LIB_STATUS_CODES MS_GenUserProvidedMines(unsigned int minePositions[][2])
{
    for (int i = 0; i < game.mineCnt; i++)
    {
        unsigned int x = minePositions[i][0];
        unsigned int y = minePositions[i][1];

        if (!isValid(x, y))
            return MS_LIB_STATUS_INVALID_LOCATION;

        game.mines[i].cellState = hasmine;
        game.mines[i].x = x;
        game.mines[i].y = y;
    }

    addMines();
    return MS_LIB_STATUS_OK;
}

/**
 * @brief Checks if a cell is cleared
 */
bool isClearedAlready(int x, int y)
{
    Cell cell = getCellByCoordinates(x, y);
    return (cell.cellState == cleared);
}

/**
 * @brief Checks if a cell has mine
 */
bool isMine(int x, int y)
{
    Cell cell = getCellByCoordinates(x, y);
    return (cell.cellState == hasmine);
}

/**
 * @brief Counts the number of mines in adjacent cells for the given cell coordinates
 */
int checkNeighbours(int row, int col)
{

    int i;
    int count = 0;
    Cell cell = getCellByCoordinates(row, col);
    // left
    if (isValid(row - 1, col) == true)
    {
        if (isMine(row - 1, col) == true)
            count++;
    }

    // right
    if (isValid(row + 1, col) == true)
    {
        if (isMine(row + 1, col) == true)
            count++;
    }

    // up
    if (isValid(row, col + 1) == true)
    {
        if (isMine(row, col + 1) == true)
            count++;
    }

    // down
    if (isValid(row, col - 1) == true)
    {
        if (isMine(row, col - 1) == true)
            count++;
    }

    // left up
    if (isValid(row - 1, col + 1) == true)
    {
        if (isMine(row - 1, col + 1) == true)
            count++;
    }

    // left down
    if (isValid(row - 1, col - 1) == true)
    {
        if (isMine(row - 1, col - 1) == true)
            count++;
    }

    // right up
    if (isValid(row + 1, col + 1) == true)
    {
        if (isMine(row + 1, col + 1) == true)
            count++;
    }

    // right dpwn
    if (isValid(row + 1, col - 1) == true)
    {
        if (isMine(row + 1, col - 1) == true)
            count++;
    }

    return (count);
}

/**
 * @brief Makes the move provided by external command and coordinates
 */
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
                gameState = MS_LIB_STATUS_CELL_CLEARED_ALREADY;
            }
            else
            {
                int adjacentMines = checkNeighbours(x, y);
                if (adjacentMines != 0)
                {
                    Cell *cell = getCellPtrByCoordinates(x, y);
                    if (!cell)
                    {
                        gameState = MS_LIB_STATUS_INVALID_LOCATION;
                    }
                    else
                    {
                        cell->cellState = cleared;
                        cell->adjMineCnt = adjacentMines;
                    }
                }
            }
        }
    }
    break;

    case 'F':
    case 'f':
    {
        Cell *cell = getCellPtrByCoordinates(x, y);
        if (!cell)
        {
            gameState = MS_LIB_STATUS_INVALID_LOCATION;
        }
        else
        {
            if (cell->cellState != cleared)
            {
                cell->cellState = flagged;
            }
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