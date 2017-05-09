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

// Read a string using fgets, and remove the trailing '\n'
size_t read_line(char * string, int size, FILE * file_ptr);
// Get rid of the newline in the input buffer
void clearBufferEnter();

#endif
