
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeperLib.h"

void printBoard(char myBoard[MAX_LEN][MAX_WIDTH], int len, int width, bool showMines)
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
        {
            if (showMines == false && myBoard[i][j] == '*')
            {
                printf("- ");
            }
            else{
                printf("%c ", myBoard[i][j]);
            }
        }
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
        if (MS_LIB_STATUS_OK != MS_initRandomGameBoard(8, 8, 10))
        {
            printf("MS_initRandomGameBoard failed to initialise\n");
            return -1;
        }
    }
    else if (isRandomBoard == 2)
    {
        unsigned int minePositions[][2] = {{0, 1}, {3, 2}, {7, 3}, {5, 6}, {7, 7}, {7, 1}, {4, 3}, {2, 6}, {5, 1}, {6, 7}};
        if (MS_LIB_STATUS_OK != MS_initGameBoardWithMinePositions(8, 8, minePositions, 10))
        {
            printf("MS_initGameBoardWithMinePositions failed to initialise\n");
            return -1;
        }
    }



    char myBoard[MAX_LEN][MAX_WIDTH];
    char command = 'C';
    int x, y;
    MS_LIB_STATUS_CODES gameState = MS_LIB_STATUS_GAME_IN_POGRESS;
    
     MS_copyActualBoardTo(myBoard, 8, 8);
    printBoard(myBoard, 8, 8,false);


    do
    {
        command = 'C';
        printf("\n(C)lear or (F)lag a square.Followed by x y coordinates.");
        scanf("%c %d %d", &command, &x, &y);
        gameState = MS_executeGame(command, x, y);
        MS_copyActualBoardTo(myBoard, 8, 8);
        printBoard(myBoard, 8, 8,false);
    } while (gameState == MS_LIB_STATUS_GAME_IN_POGRESS || gameState == MS_LIB_STATUS_INVALID_CMD|| gameState == MS_LIB_STATUS_CELL_CLEARED_ALREADY);

      if(gameState == MS_LIB_STATUS_GAME_LOST)
      {
          printf("\nGAME IS OVER! YOU LOST");
      }
      else if(gameState == MS_LIB_STATUS_GAME_WON)
      {
          printf("\nGAME IS OVER! YOU WON");
      }
     printBoard(myBoard, 8, 8,true);

};