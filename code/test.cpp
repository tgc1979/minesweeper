
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeperLib.h"
static     Game myGame;

void printBoard(Game game)
{
int i, j;
 
    printf ("    ");
 
    for (i=0; i<SIDE; i++)
        printf ("%d ", i);
 
    printf ("\n\n");
 
    for (i=0; i<SIDE; i++)
    {
        printf ("%d   ", i);

        for (j=0; j<SIDE; j++)
         {
             int x = i;
             int y = j%SIDE;

             Cell cell =  getCellByCoordinates( x,y);
             switch(cell.cellState)
                {
                 case hasmine:
                    printf ("* ");
                    break;
                case flagged:
                    printf ("F ");
                    break;
                 case initial:
                    printf ("- ");
                    break;
                 case cleared:
                    printf ("%d ",cell.adjMineCnt);
                    break;
                }
         }
        printf ("\n");
    }
    return;
}
int main()
{
    unsigned int isRandomBoard = 1;
    //   printf("Press (1)To initialise a random board or (2) To enter mine positions:");
    //   scanf("%u",&isRandomBoard);

    if (isRandomBoard != 1 && isRandomBoard != 2)
    {
        printf("Invalid board initialisation is choosen\n");
        return -1;
    }

    if (isRandomBoard == 1)
    {
        if (MS_LIB_STATUS_OK != MS_GenRandomMines())
        {
            printf("MS_initRandomGameBoard failed to initialise\n");
            return -1;
        }
    }
    else if (isRandomBoard == 2)
    {
        unsigned int minePositions[][2] = {{0, 1}, {3, 2}, {7, 3}, {5, 6}, {7, 7}, {7, 1}, {4, 3}, {2, 6}, {5, 1}, {6, 7}};
        if (MS_LIB_STATUS_OK != MS_GenUserProvidedMines(minePositions))
        {
            printf("MS_initGameBoardWithMinePositions failed to initialise\n");
            return -1;
        }
    }



    char command = 'C';
    int x, y;
    MS_LIB_STATUS_CODES gameState = MS_LIB_STATUS_GAME_IN_POGRESS;
    
    MS_getGameState(&myGame);
    printBoard(myGame);


    do
    {
        command = 'C';
        printf("\n(C)lear or (F)lag a square.Followed by x y coordinates.");
        scanf("%c %d %d", &command, &x, &y);
        gameState = MS_executeGame(command, x, y);
        MS_getGameState(&myGame);
        printBoard(myGame);
    } while (gameState == MS_LIB_STATUS_GAME_IN_POGRESS || gameState == MS_LIB_STATUS_INVALID_CMD|| gameState == MS_LIB_STATUS_CELL_CLEARED_ALREADY);

      if(gameState == MS_LIB_STATUS_GAME_LOST)
      {
          printf("\nGAME IS OVER! YOU LOST");
      }
      else if(gameState == MS_LIB_STATUS_GAME_WON)
      {
          printf("\nGAME IS OVER! YOU WON");
      }
     printBoard(myGame);

};