
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeperLib.h"

void printBoard(char myBoard[MAX_LEN][MAX_WIDTH], int len, int width)
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
int main()
{
    unsigned int isRandomBoard = 2;
    //   printf("Press (1)To initialise a random board or (2) To enter mine positions:");
    //   scanf("%u",&isRandomBoard);

    if (isRandomBoard != 1 && isRandomBoard != 2)
    {
        printf("Invalid board initialisation is choosen\n");
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
    char command = 'C';
    int x,y;
    bool isGameOver=false;
    do
    {
     command = 'C';
	 printf("\n(C)lear or (F)lag a square.Followed by x y coordinates.");
	 scanf("%c %d %d",&command, &x, &y);
     isGameOver=MS_executeGame(command,x,y);
     MS_getActualBoardState(myBoard, 8, 8);
     printBoard(myBoard, 8, 8);
    } while (isGameOver==false);
    

};