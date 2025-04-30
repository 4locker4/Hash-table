#ifndef HASH_MAIN_HPP
#define HASH_MAIN_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "./Parsing.hpp"
#include "../DL_list/inc/header.h"

const int HASH_TABLE_SIZE = 1500;

typedef struct 
{
    char * elem          = NULL;
    int    elem_position = 0;
} LIST_DATA;

typedef struct 
{
    size_t     hash_table_size = 0;
    size_t     n_loaded_elems  = 0;
    POINTERS * list            = NULL;
    bool       is_init         = false;

} HASH_TABLE_DATA;

void         StartHashTable             ();
int          HashTableInit              (HASH_TABLE_DATA * hash_table_data);
//const char * FindTheWord                (char * word);
char **      ReadData                   (size_t * n_elems_in_text);
bool         CheckAvailabilityOfElem    (POINTERS * list, char * elem);
int          HashTableCreate            (HASH_TABLE_DATA * hash_table_data);

#endif // HASH_MAIN_HPP