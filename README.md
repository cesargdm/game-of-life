# Conway's Game of Life
> Final evaluation for Advanced programming class, using MP and PGM images.  [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway's_Game_of_Life).

**Sample**

Generated GIF, using samples/bichitos.txt file, a 500x500 initial state

![Game of Life](http://i.imgur.com/ZJs1SvP.gif)

## Description

The game is played on its own, with cells arranged in a matrix. The cells can be alive or dead. At every iteration of the game, the cells can remain as they are, die or be born, following this rules.
* Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
* Any live cell with two or three live neighbours lives on to the next generation.
* Any live cell with more than three live neighbours dies, as if by overpopulation.
* Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## Requirements
[OpenMP](http://www.openmp.org)

## Compile and run
**Build**
> gcc-7 main.c string_functions.c -fopenmp -o life

**Run**
Executable, initial state text file and number of iterations
> ./life ./samples/bichitos.txt 1000

## LICENSE
MIT &copy; César Guadarrama
&copy; Gilberto Echeverría

GIF Encoder &copy; lecram
