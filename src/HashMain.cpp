#include "../inc/HashMain.hpp"

static const char * POS_ANSWER = "We found it!\n";
static const char * NEG_ANSWER = "Word is not in this text\n";

static const char * PARSED_FILE_NAME = "../HashTable/Text/ParsedText.txt";

inline int HashCalc (char * pointer_to_data);

int main ()
{
    StartHashTable ();

    return 0;
}

void StartHashTable ()
{
    PrepairFile ();

    HASH_TABLE_DATA hash_table = {};

    HashTableInit (&hash_table);

    HashTableCreate ()
}

const char * FindTheWord (char * word)
{
    assert (word);

    int hash = 0;
    
    HashCalc (word, &hash);

    LIST_DATA list_elem = hash_table[hash];

    while (list_elem.prev_elem != NULL)
    {
        if (strcasecmp (list_elem.elem, word))
            return POS_ANSWER;

        list_elem = *list_elem.prev_elem;
    }
    
    return NEG_ANSWER;
}

int HashTableInit (HASH_TABLE_DATA * hash_table_data)
{
    assert (hash_table_data);

    hash_table_data->hash_table_size = HASH_TABLE_SIZE;
    hash_table_data->list            = (LIST_DATA **) calloc (HASH_TABLE_SIZE, sizeof (LIST_DATA *));
    hash_table_data->n_loaded_elems  = 0;
    hash_table_data->is_init         = true;

    assert (hash_table_data->list);

    return 0;
}

int HashTableCreate (HASH_TABLE_DATA * hash_table_data)
{
    size_t n_elems_in_text = 0;

    char ** data = ReadData (&n_elems_in_text);

    int hash = 0;

    for (int i = 0; n_elems_in_text > i; i++)
    {
        hash = HashCalc (data[i]);

        if (CheckAvailabilityOfElem (hash_table_data->list[hash], data[i]))
            continue;
        
        hash_table_data->list

    }
}

bool CheckAvailabilityOfElem (LIST_DATA ** list, char * elem)
{
    assert (list && elem);

    size_t counter = 0;

    while (list[counter]->elem != NULL)
    {
        if (strcasecmp (list[counter]->elem, elem))
            return true;
        
        counter++;
    }

    return false;
}

inline int HashCalc (char * pointer_to_data)
{
    int hash = 0;

    while (isalpha (*pointer_to_data))
    {
        hash = ((hash << 5) + hash) ^ (*pointer_to_data);

        pointer_to_data++;
    }

    return hash % (HASH_TABLE_SIZE - 1);
}

char ** ReadData (size_t * n_elems_in_text)
{
    size_t file_size = 0;                                                       // TD file_size нам не нужен, но требуется в функции. Исправить.

    char * file_data = FileToStr (PARSED_FILE_NAME, &file_size);

    size_t n_strings = CountStringsAndPutZeroInstNewLine (file_data);

    char ** data = (char **) calloc (n_strings, sizeof (char *));

    char * word = NULL;

    for (int i = 0; n_strings > i; i++)
    {
        word = (char *) calloc (1, 32 * sizeof (char));
        assert (word);

        data[i] = strcpy (word, file_data);
    }

    free (file_data);

    *n_elems_in_text = n_strings;

    return data;
}