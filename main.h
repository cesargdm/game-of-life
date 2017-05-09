/*
GAME OF LIFE

César Guadarrama Cantú
cesargdm@icloud.com
A01364853

*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <stdbool.h>
#include "string_functions.h"

#include <sys/time.h>
struct timeval start, end;

// Function to free memory allocated
void free_matrix(int **, int);
// Function to allocate matrix's space
int ** init_matrix(int, int);
// Function to free columns and rows
void free_dimensions(int *, int *);
// Function to generate pgm file
void generate_pgm(int **, int, int, int);
// Function to copy the contents of temp_matrix to matrix
void copy_matrix(int **, int **, int, int);
