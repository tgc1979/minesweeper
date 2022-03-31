
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "minesweeperLib.h"
static     Game myGame;

//#define UNIT_TEST

/**
 * @brief prints the game board. If showMines is true then mines will be visible
*/

void printBoard(Game game,bool showMines)
{
int i, j;

    printf ("\n\n");

    printf ("    ");
 
    for (i=0; i<game.side; i++)
        printf ("%d ", i);
 
    printf ("\n\n");
 
    for (i=0; i<game.side; i++)
    {
        printf ("%d   ", i);

        for (j=0; j<game.side; j++)
         {
             int x = i;
             int y = j%game.side;

             Cell cell =  getCellByCoordinates( x,y);
             switch(cell.cellState)
                {
                 case hasmine:
                 if(showMines)
                    printf ("* ");
                else
                    printf ("- ");
                   
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

#ifdef UNIT_TEST

    assert(MS_initGame(10,8)==MS_LIB_STATUS_OK);
    
    unsigned int minePositions[][2] = {{0, 1}, {3, 2}, {7, 3}, {5, 6}, {7, 7}, {7, 1}, {4, 3}, {2, 6}, {5, 1}, {6, 7}};
    assert(MS_GenUserProvidedMines(minePositions)==MS_LIB_STATUS_OK);
    assert(MS_executeGame('x', 5, 0)==MS_LIB_STATUS_INVALID_CMD);
    assert(MS_executeGame('f', 5, 0)==MS_LIB_STATUS_GAME_IN_POGRESS);
    Cell cell =  getCellByCoordinates( 5,0);
    assert(cell.cellState==flagged);
    assert(MS_executeGame('c', 5, 0)==MS_LIB_STATUS_GAME_IN_POGRESS);
    cell =  getCellByCoordinates( 5,0);
    assert(cell.cellState!=flagged);
    assert(cell.cellState==cleared);
    cell =  getCellByCoordinates(150,0);
    assert(cell.cellState==notvalid);
    
#else


    if(MS_initGame(10,8)!=MS_LIB_STATUS_OK)
    {
        printf("Invalid Game configuration. Check mine count and board size\n");
        return -1;

    }





    unsigned int isRandomBoard = 1;
    printf("Press (1)To initialise a random board or (2) To enter mine positions:");
    scanf("%u",&isRandomBoard);


    if (isRandomBoard != 1 && isRandomBoard != 2)
    {
        printf("Invalid mine generation is choosen\n");
        return -1;
    }

    if (isRandomBoard == 1)
    {
        if (MS_LIB_STATUS_OK != MS_GenRandomMines())
        {
            printf("\n Failed to randomly initialise mines.Check mine locations.");
            return -1;
        }
    }
    else if (isRandomBoard == 2)
    {
        unsigned int minePositions[][2] = {{0, 1}, {3, 2}, {7, 3}, {5, 6}, {7, 7}, {7, 1}, {4, 3}, {2, 6}, {5, 1}, {6, 7}};
        if (MS_LIB_STATUS_OK != MS_GenUserProvidedMines(minePositions))
        {
            printf("\n Failed to initialise mines.Check mine locations.");
            return -1;
        }
    }


    char command = 'C';
    int x, y;
    MS_LIB_STATUS_CODES gameState = MS_LIB_STATUS_GAME_IN_POGRESS;
    
    MS_getGameState(&myGame);
    printBoard(myGame,false);


    do
    {
        printf("\n(C)lear or (F)lag a square.Followed by x y coordinates.");
        scanf("%c %d %d", &command, &x, &y);
        gameState = MS_executeGame(command, x, y);
        MS_getGameState(&myGame);
        printBoard(myGame,false);
    } while (gameState == MS_LIB_STATUS_GAME_IN_POGRESS || gameState == MS_LIB_STATUS_INVALID_CMD|| gameState == MS_LIB_STATUS_CELL_CLEARED_ALREADY);

      if(gameState == MS_LIB_STATUS_GAME_LOST)
      {
          printf("\nGAME IS OVER! YOU LOST");
      }
      else if(gameState == MS_LIB_STATUS_GAME_WON)
      {
          printf("\nGAME IS OVER! YOU WON");
      }
     printBoard(myGame,true);

#endif
};