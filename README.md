# Conway's Game of Life
> Final evaluation for Advanced programming class, using MP and PGM images

Copyright &copy; 2017 César Guadarrama All Rights Reserved.

## Description
The game is played on its own, with cells arranged in a matrix. The cells can be alive or dead. At every iteration of the game, the cells can remain as they are, die or be born, following these rules: (https://en.wikipedia.org/wiki/Conway's_Game_of_Life)

**Rules**

Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## Requirements
OPEN MP

## Compile and run
**Build**
> gcc-7 main.c string_functions.c -o life

**Run**
Executable, initial state text file and number of iterations
> life ./sample.txt 5

## LICENSE
MIT &copy; César Guadarrama
&copy; Gilberto Echeverría
