
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeperLib.h"

int main()
{
    unsigned int isRandomBoard = 1;
    //   printf("Press (1)To initialise a random board or (2) To enter mine positions:");
    //   scanf("%u",&isRandomBoard);

    if (isRandomBoard != 0 && isRandomBoard != 1)
    {
        printf("Invalid init bumethod is choosen\n");
        return -1;
    }

    if (isRandomBoard == 1)
    {
        if (MS_LIB_STATUS_OK != MS_initRandomGameBoard(8, 8,10))
        {
            printf("MS_initRandomGameBoard failed to initialise\n");
        }
    }
    else if (isRandomBoard == 2)
    {
        unsigned int minePositions[][2] = {{0, 1}, {3, 2}, {7, 3}, {5, 6}, {7, 7}, {7, 1}, {4, 3}, {2, 6}, {5,1}, {6,7}};
        if (MS_LIB_STATUS_OK != MS_initGameBoardWithMinePositions(8, 8, minePositions,10))
        {
            printf("MS_initGameBoardWithMinePositions failed to initialise\n");
        }
    }

    char myBoard[MAX_LEN][MAX_WIDTH];
    MS_copyBoard(myBoard, 8, 8);
    MS_printBoard(myBoard, 8, 8);

	printf("Enter your move, (row, column) -> ");
	scanf("%d %d", x, y);
    // puts(MS_getModuleVersion());
}