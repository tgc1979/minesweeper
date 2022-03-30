#ifndef C_STATIC_LIB_MINESWEEPER_LIBRARY_H
#define C_STATIC_LIB_MINESWEEPER_LIBRARY_H

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Error and Status Codes
*/

typedef enum
{
    MS_LIB_STATUS_OK,
    MS_LIB_STATUS_INVALID_BOARD_SIZE,
    MS_LIB_STATUS_UNSUPPORTED_BOARD_SIZE,
    MS_LIB_STATUS_INVALID_MINE_CNT,
    MS_LIB_STATUS_INVALID_LOCATION,
    MS_LIB_STATUS_CELL_CLEARED_ALREADY,
    MS_LIB_STATUS_GAME_LOST,
    MS_LIB_STATUS_GAME_WON,
    MS_LIB_STATUS_INVALID_CMD,
    MS_LIB_STATUS_GAME_IN_POGRESS
}MS_LIB_STATUS_CODES;

const unsigned int MAX_WIDTH = 25; // max width of the board
const unsigned int MAX_LEN = 25;   // max length of the board

const unsigned char * MS_getModuleVersion(void);

MS_LIB_STATUS_CODES MS_initRandomGameBoard(unsigned int len , unsigned int width, unsigned int mineCnt);

MS_LIB_STATUS_CODES MS_initGameBoardWithMinePositions(unsigned int len , unsigned int width , unsigned int minePositions[][2], unsigned int mineCnt);

void MS_copyActualBoardTo(char myBoard[MAX_LEN][MAX_WIDTH],int len,int width);
void MS_printBoard(char myBoard[MAX_LEN][MAX_WIDTH],int len,int width);
MS_LIB_STATUS_CODES MS_executeGame(char command,unsigned int x , unsigned int y);

#endif