#ifndef C_STATIC_LIB_MINESWEEPER_LIBRARY_H
#define C_STATIC_LIB_MINESWEEPER_LIBRARY_H

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Error and Status Codes
*/

typedef enum
{
    MS_LIB_STATUS_OK=1,
    MS_LIB_STATUS_INVALID_BOARD_SIZE=-1,
    MS_LIB_STATUS_UNSUPPORTED_BOARD_SIZE=-2,
    MS_LIB_STATUS_INVALID_LOCATION=-3
    
}MS_LIB_STATUS_CODES;

const unsigned int MAX_WIDTH = 25; // max width of the board
const unsigned int MAX_LEN = 25;   // max length of the board

const unsigned char * MS_getModuleVersion(void);

MS_LIB_STATUS_CODES MS_initRandomGameBoard(unsigned int len , unsigned int width, unsigned int mineCnt);

MS_LIB_STATUS_CODES MS_initGameBoardWithMinePositions(unsigned int len , unsigned int width , unsigned int minePositions[][2], unsigned int mineCnt);

void MS_copyBoard(char myBoard[MAX_LEN][MAX_WIDTH],int len,int width);
void MS_printBoard(char myBoard[MAX_LEN][MAX_WIDTH],int len,int width);
bool MS_executeGame(char command,unsigned int x , unsigned int y);

#endif