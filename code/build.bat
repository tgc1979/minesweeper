del *.a
del *.o
del *.exe


g++ -c .\minesweeperLib.c
ar rvs .\minesweeperLib.a .\minesweeperLib.o
g++ test.c .\minesweeperLib.a