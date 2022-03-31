#ifndef C_STATIC_LIB_MINESWEEPER_LIBRARY_H
#define C_STATIC_LIB_MINESWEEPER_LIBRARY_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Error and Status Codes
*/

/**
 * @brief Maximum side supported by game
*/
#define MAX_SIDE (15)

/**
 * @brief Maximum mines can be placed
*/
#define MAX_MINE (10)


typedef enum
{
    MS_LIB_STATUS_OK,                         //operation succeeded
    MS_LIB_STATUS_BOARD_SIZE_EXCEEDS_LIMIT,   //board size exceeds max length
    MS_LIB_STATUS_INVALID_MINE_CNT,           //mine count exceeds max mine count supported  
    MS_LIB_STATUS_INVALID_LOCATION,           //invalid cell location is requested  
    MS_LIB_STATUS_CELL_CLEARED_ALREADY,       //clearing an already cleared cell
    MS_LIB_STATUS_GAME_LOST,                  //game is lost due to a mine hit  
    MS_LIB_STATUS_GAME_WON,                   //game is won due to all cells being cleared
    MS_LIB_STATUS_INVALID_CMD,                //invalid command requests  
    MS_LIB_STATUS_GAME_IN_POGRESS             //game is not over  
}MS_LIB_STATUS_CODES;


typedef enum{
initial,                                        //initail cell state
hasmine,                                        //mine in cell
flagged,                                        //cell is flagged
cleared,                                        //cell is cleared
notvalid                                        //requested cell is not valid
}CellState;

typedef struct 
{
    CellState cellState;
    int x;
    int y;
    int adjMineCnt;                             //number of adjacent mines when cell is cleared
}Cell;


typedef struct
{
    unsigned int side;
    unsigned int mineCnt;
    unsigned int remainingMoves;                //game will end when remainingMoves reaches 0 or a mine is hit
    Cell cells[MAX_SIDE*MAX_SIDE];
    Cell mines[MAX_MINE];
} Game;



/**
 * @brief returns version of the library
*/
const unsigned char * MS_getModuleVersion(void);

/**
 * @brief generates random mines
 */
MS_LIB_STATUS_CODES MS_GenRandomMines();

/**
 * @brief generates mines using external input
 */
MS_LIB_STATUS_CODES MS_GenUserProvidedMines( unsigned int minePositions[][2]);

/**
 * @brief gets copy of current game state
 */
void MS_getGameState(Game *destBoard);

/**
 * @brief makes a move and run the rules based on move
 */
MS_LIB_STATUS_CODES MS_executeGame(char command,unsigned int x , unsigned int y);

/**
 * @brief get a copy of a cell by given coordinates
 */
extern Cell getCellByCoordinates(int x , int y);

/**
 * @brief starts a new game with mineCnt and board size
 */
MS_LIB_STATUS_CODES MS_initGame(unsigned int mineCnt , unsigned int gameBoardSize);

#if defined (__cplusplus)
}
#endif

#endif

