#include "../inc/HashMain.hpp"

static const char * POS_ANSWER = "We found it!\n";
static const char * NEG_ANSWER = "Word is not in this text\n";

static const char * PARSED_FILE_NAME     = "../HashTable/Text/ParsedText.txt";
static const char * HASH_TABLE_DUMP_FILE = "../HashTable/Text/HashTableResult.txt";

const char * FIND_WORD = "Nevsky";

inline size_t HashCalc (char * pointer_to_data);

int main ()
{
    PrepairFile ();

    StartHashTable ();

    return 0;
}

void StartHashTable ()
{
    HASH_TABLE_DATA hash_table = {};

    HashTableInit (&hash_table);

    HashTableCreate (&hash_table);

    OutputHashTableIntoFile (&hash_table);

    FindTheWord (&hash_table, (char *) FIND_WORD);

    return;
}

const char * FindTheWord (HASH_TABLE_DATA * hash_table, char * word)
{
    assert (word);
    
    int hash = HashCalc (word);

    printf ("%d - index (if not found: -1)\n",  FindElemIndex (&hash_table->list[hash], word));

    return NEG_ANSWER;
}

int HashTableInit (HASH_TABLE_DATA * hash_table_data)
{
    assert (hash_table_data);

    hash_table_data->hash_table_size = HASH_TABLE_SIZE;
    hash_table_data->list            = (POINTERS *) calloc (HASH_TABLE_SIZE, sizeof (POINTERS));
    hash_table_data->n_loaded_elems  = 0;
    hash_table_data->is_init         = true;

    for (int i = 0; HASH_TABLE_SIZE > i; i++)
        ListCtor (&hash_table_data->list[i]);

    assert (hash_table_data->list);

    return 0;
}

int HashTableCreate (HASH_TABLE_DATA * hash_table_data)
{
    size_t n_elems_in_text = 0;

    // table_elem *

    char ** data = ReadData (&n_elems_in_text);

    int hash = 0;

    printf ("n elems: %d\n", n_elems_in_text);

    for (int i = 0; n_elems_in_text > i; i++)
    {
        hash = HashCalc (data[i]);

        if (CheckAvailabilityOfElem (&hash_table_data->list[hash], data[i]))
            continue;

        printf ("Hash: %d, i: %d\n", hash, i);
        
        PhysInsertElem (&hash_table_data->list[hash], data[i], hash_table_data->list[hash].free - 1);
    }

    return 0;
}

bool CheckAvailabilityOfElem (POINTERS * list, char * elem)
{
    assert (list && elem);

    if (FindElemIndex (list, elem) == ELEM_NOT_FIND)
        return false;
    
    return true;
}

inline size_t HashCalc (char * pointer_to_data)
{
    size_t hash = 0;

    while (isalpha (*pointer_to_data))
    {
        hash = ((hash << 5) + hash) ^ (*pointer_to_data);

        pointer_to_data++;
    }
    
    return hash % HASH_TABLE_SIZE;
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

        while (*file_data != '\0')
            file_data++;
        file_data++;
    }

    *n_elems_in_text = n_strings;

    return data;
}

int OutputHashTableIntoFile (HASH_TABLE_DATA * hash_table)
{
    my_assert (hash_table);

    FILE * dump_file = fopen (HASH_TABLE_DUMP_FILE, "w");
    my_assert (dump_file);

    size_t counter = 0;

    printf ("start output\n");

    for (int i = 0; HASH_TABLE_SIZE > i; i += 4)
    {
        fprintf (dump_file, "|\t  HASH %4d   |\t\tHASH %4d |\t\tHASH %4d\t|\t  HASH %4d\t\n", i, i+ 1, i + 2, i + 3);

        counter = 1;

        while (hash_table->list[i].size     >= counter && hash_table->list[i + 1].size >= counter && 
               hash_table->list[i + 2].size >= counter && hash_table->list[i + 3].size >= counter) 
        {
            if (hash_table->list[i].free >= counter && hash_table->list[i].is_init)
                fprintf (dump_file, "|%19s", hash_table->list[i].leaf[counter].list_elem);
            else
            fprintf (dump_file, "|       none        ");
            
            if (hash_table->list[i + 1].free >= counter && hash_table->list[i + 1].is_init)
                fprintf (dump_file, "|%19s", hash_table->list[i + 1].leaf[counter].list_elem);
            else
                fprintf (dump_file, "|       none        ");

            
            if (hash_table->list[i + 2].free >= counter && hash_table->list[i + 2].is_init)
                fprintf (dump_file, "|%19s", hash_table->list[i + 2].leaf[counter].list_elem);
            else
                fprintf (dump_file, "|       none        ");


            if (hash_table->list[i + 3].free >= counter && hash_table->list[i + 3].is_init)
                fprintf (dump_file, "|%19s\n", hash_table->list[i + 3].leaf[counter].list_elem);
            else
                fprintf (dump_file, "|       none        \n");
                
            counter++;
        }

        fprintf (dump_file, "\n\n");
    }

    my_assert (!fclose (dump_file));

    return 0;
}
