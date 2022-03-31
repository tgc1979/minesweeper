# minesweeper
Built has been tested Windows 10 using mingw
Follow the steps to configure mingw on visual studio https://code.visualstudio.com/docs/cpp/config-mingw


test.cpp : Test application.

build.bat : Builds the library and test application. Compiler is mingw64 and tested on Windows 10
a.exe : test application binary
minesweeperLib.c : Mine sweeper game
minesweeperLib.h : Mine sweeper game header
minesweeperLib.a : Main deliverable of the project

You can modify build.bat for the target platform you want to test the library


Test application Unit Tests Mode
There is a preprocessor macro UNIT_TEST defined in test.cpp which enables or disables the unit test. 
When undefined a.exe will finction as a minesweeper game. 
When defined unit tests will run . 


Test application Game Mode
In game mode a game board of 8x8 is created with 10 mines placed
You will be promopted to select mine generation
If random is selected 10 mines will be generated randomwly for you
If user input is provided mines will be placed on following coordinates
{{0, 1}, {3, 2}, {7, 3}, {5, 6}, {7, 7}, {7, 1}, {4, 3}, {2, 6}, {5, 1}, {6, 7}};


I have made following assumptions just to make implementation easier and not to get lost in geometry of the game
1)Game board is a square
2)Random mine generation generates mines in 10 unique location
3)Mines are not visible in the game board. If you want to see the mines change the parameter showMines to true




Usage
MS_initGame : initialise a game with a board side len and number of mines
MS_GenUserProvidedMines:You can provide mines to the library using this interface. 
MS_GenRandomMines:Generates random mines
MS_getGameState:Copies the game state to application
MS_executeGame:Makes a move and updates internal game state
getCellByCoordinates:Get the state of a cell by given coordinate. You can use this interface to print the entire game


Design Overview
Most mine sweep libraries/games tend to keep 2 dimensional array with ASCII characters to execute the  game and update internal game state.
This approach forces limits users to choose a GUI of their own choise
With this version of mine sweep it is possible to access the cells as a collection and query them by coordinates. This gives flexibilty
to display any type of GUI to represent the game state.
