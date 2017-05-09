/*
GAME OF LIFE

César Guadarrama Cantú
cesargdm@icloud.com
A01364853

Some code borrowed from Gilberto Echeverria
gilecheverria@yahoo.com
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "string_functions.h"

#include <sys/time.h>
struct timeval start, end;

void free_matrix(int **, int);
int ** init_matrix(int, int);
void free_dimensions(int *, int *);
void generate_pgm(int **, int, int, int);
void copy_matrix(int **, int **, int, int);
