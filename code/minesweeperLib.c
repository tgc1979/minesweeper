#include <stdio.h>
#include <stdlib.h>
#include "minesweeperLib.h"

/**
 * @brief Constants
 */

const unsigned char MODULE_VERSION[] = "V2.0";

typedef struct
{
    unsigned int boardLen;
    unsigned int boardWidth;
    // Actual Board and My Board
    char realBoard[MAX_WIDTH][MAX_LEN];
    char myBoard[MAX_WIDTH][MAX_LEN];
} MS_board;

/**
 * @brief Globals
 */
MS_board board;

/**
 * @brief Utility functions
 */
const unsigned int MS_getMaxWidth();
const unsigned int MS_getMaxLen();
// void MS_printBoard(char myBoard[MAX_WIDTH][MAX_LEN],int len,int width);

void debugPrint(const char *str)
{
#ifdef DEBUG_MS_LIB
    puts(str);
#endif
}
void MS_copyBoard(char myBoard[MAX_LEN][MAX_WIDTH], int len, int width)
{
    for (int i = 0; i < board.boardLen; i++)
    {
        for (int j = 0; j < board.boardWidth; j++)
        {
            myBoard[i][j] = board.realBoard[i][j];
        }
    }
}

void MS_printBoard(char myBoard[MAX_LEN][MAX_WIDTH], int len, int width)
{
    int i, j;
    printf("\n");

    printf("    ");

    for (i = 0; i < len; i++)
        printf("%d ", i);

    printf("\n\n");

    for (i = 0; i < len; i++)
    {
        printf("%d   ", i);

        for (j = 0; j < width; j++)
            printf("%c ", myBoard[i][j]);
        printf("\n");
    }
}
MS_LIB_STATUS_CODES validateBoard(unsigned int len, unsigned int width)
{
    if (len <= 0 || width <= 0)
    {
        return MS_LIB_STATUS_INVALID_BOARD_SIZE;
    }
    if (len > MS_getMaxLen() || width > MS_getMaxWidth())
    {
        return MS_LIB_STATUS_UNSUPPORTED_BOARD_SIZE;
    }
    return MS_LIB_STATUS_OK;
}
/**
 * @brief Returns null terminated string of 4 characters
 */
const unsigned char *MS_getModuleVersion(void)
{
    return MODULE_VERSION;
}

/**
 * @brief Returns max width of the board
 */
const unsigned int MS_getMaxWidth()
{
    return MAX_WIDTH;
}

/**
 * @brief Returns max len of  the board
 */
const unsigned int MS_getMaxLen()
{
    return MAX_LEN;
}

/**
 * @brief Initialise a new board with len x width squares
 */
MS_LIB_STATUS_CODES MS_initRandomGameBoard(unsigned int len, unsigned int width)
{
    MS_LIB_STATUS_CODES ret = validateBoard(len, width);
    board.boardLen = len;
    board.boardWidth = width;
    for (int i = 0; i < board.boardLen; i++)
    {
        for (int j = 0; j < board.boardWidth; j++)
        {
            board.realBoard[i][j] = '-';
        }
    }

    for (int i = 0; i < len; i++)
    {
        int random = rand() % (MAX_LEN*MAX_WIDTH);
        int x = (rand() * (MAX_LEN*MAX_WIDTH)) % len;
        int y = (rand() * (MAX_LEN*MAX_WIDTH)) % width;
        board.realBoard[x][y] = '*';
    }

    MS_printBoard(board.realBoard, len, width);

    return ret;
}

/**
 * @brief Initialise a new board with len x width squares using specified mine positions
 */
MS_LIB_STATUS_CODES MS_initGameBoardWithMinePositions(unsigned int len, unsigned int width, unsigned int minePositions[][2])
{
    debugPrint("IN MS_initGameBoardWithMinePositions\n");
    MS_LIB_STATUS_CODES ret = validateBoard(len, width);

    for (int i = 0; i < len; i++)
    {
        unsigned int x = minePositions[i][0];
        unsigned int y = minePositions[i][1];

        if ((x < 0 || x > len) || (y < 0 || y > len))
        {
            return MS_LIB_STATUS_INVALID_LOCATION;
        }
    }

    board.boardLen = len;
    board.boardWidth = width;
    for (int i = 0; i < board.boardLen; i++)
    {
        for (int j = 0; j < board.boardWidth; j++)
        {
            board.realBoard[i][j] = '-';
        }
    }

    for (int i = 0; i < len; i++)
    {
        unsigned int x = minePositions[i][0];
        unsigned int y = minePositions[i][1];
        board.realBoard[x][y] = '*';
    }

    MS_printBoard(board.realBoard, len, width);
    debugPrint("OUT MS_initGameBoardWithMinePositions\n");
    return ret;
}