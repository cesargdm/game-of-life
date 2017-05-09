/*
   Functions for working with arrays of characters

    Gilberto Echeverria
    gilecheverria@yahoo.com
    01/02/2017
*/

#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max line size of source sample file
#define LINE_SIZE 500

// Read a string using fgets, and remove the trailing '\n'
size_t read_line(char * string, int size, FILE * file_ptr);
// Read the size of the sample file header
void read_size(int *, int *, FILE *);
// Read the content of the sample file
void read_content(int *, int *, FILE *, int **);

#endif
