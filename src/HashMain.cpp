#include "../inc/HashMain.hpp"
#include "../inc/HashFunc.hpp"

static const char * POS_ANSWER = "We found it!\n";
static const char * NEG_ANSWER = "Word is not in this text\n";

static const char * PARSED_FILE_NAME      = "../HashTable/Text/ParsedText.txt";
static const char * HASH_TABLE_DUMP_FILE  = "../HashTable/Text/HashTableResult.txt";
static const char * HASH_TABLE_LENGHTS    = "../HashTable/Text/Lenghts.txt";
static const char * HASH_TABLE_COLLISIONS = "../HashTable/Text/CollisionsCRC32.txt";

size_t HashCalc (char * pointer_to_data);

int main ()
{
    StartHashTable ();

    return 0;
}

void StartHashTable ()
{
    HASH_TABLE_DATA hash_table = {};

    HashTableInit (&hash_table);

    HashTableCreate (&hash_table);

    for (int j = 0; 10 > j; j++)
    {
        for (int i = 0; 100000000 > i; i++)
            FindTheWord (&hash_table, &hash_table.list[i % 967].leaf[i % 5].list_elem);
    }

    return;
}

const char * FindTheWord (HASH_TABLE_DATA * hash_table, list_elem_t * word)
{
    assert (word);
    
    unsigned int hash = Crc32HashFunc (&word->list_elem_str) % HASH_TABLE_SIZE;

    bool res = FindElemIndex (&hash_table->list[hash], word);

    if (res)
        return POS_ANSWER;
    
    return NEG_ANSWER;
}

int HashTableInit (HASH_TABLE_DATA * hash_table_data)
{
    assert (hash_table_data);

    hash_table_data->hash_table_size = HASH_TABLE_SIZE;
    hash_table_data->list            = (POINTERS *) calloc (HASH_TABLE_SIZE, sizeof (POINTERS));
    hash_table_data->is_init         = true;

    for (int i = 0; HASH_TABLE_SIZE > i; i++)
        ListCtor (&hash_table_data->list[i]);

    assert (hash_table_data->list);

    return 0;
}

int HashTableCreate (HASH_TABLE_DATA * hash_table_data)
{
    size_t n_elems_in_text = 0;

    list_elem_t * data = ReadData (&n_elems_in_text);

    unsigned int hash = 0;

    for (int i = 0; n_elems_in_text > i; i++)
    {
        hash = Crc32HashFunc (&data[i].list_elem_str) % HASH_TABLE_SIZE;

        if (CheckAvailabilityOfElem (&hash_table_data->list[hash], &data[i]))
            continue;
                
        PhysInsertElem (&hash_table_data->list[hash], &data[i], hash_table_data->list[hash].free - 1);
    }
    
    return 0;
}

bool CheckAvailabilityOfElem (POINTERS * list, list_elem_t * elem)
{
    assert (list && elem);

    if (FindElemIndex (list, elem) == ELEM_NOT_FIND)
        return false;
    
    return true;
}

size_t HashCalc (char * elem)
{
    unsigned int hash = 0xFFFFFFFF;

    while (*elem != '\0')
    {
        size_t byte = (char) *elem++;
        hash = (hash >> 8) ^ crc32_table[(hash ^ byte) & 0xFF];
    }

    return hash ^ 0xFFFFFFFF;
}

list_elem_t * ReadData (size_t * n_elems_in_text)
{
    size_t file_size = 0;                                                       // TD file_size нам не нужен, но требуется в функции. Исправить.

    char * file_data = FileToStr (PARSED_FILE_NAME, &file_size);

    size_t n_strings = CountStringsAndPutZeroInstNewLine (file_data);

    list_elem_t * data = (list_elem_t *) calloc (n_strings, sizeof (list_elem_t));

    for (int i = 0; n_strings > i; i++)
    {
        memcpy (&data[i], file_data, sizeof (list_elem_t));

        file_data += sizeof (list_elem_t);
    }

    *n_elems_in_text = n_strings;

    return data;
}

int OutputHashTableIntoFile (HASH_TABLE_DATA * hash_table)
{
    assert (hash_table);

    FILE * dump_file = fopen (HASH_TABLE_DUMP_FILE, "w");
    assert (dump_file);

    size_t counter = 0;

    printf ("start output\n");

    for (int i = 0; HASH_TABLE_SIZE > i; i += 4)
    {
        fprintf (dump_file, "|\t  HASH %4d     |\t\tHASH %4d   |\t\tHASH %4d\t|\t  HASH %4d\t\n", i, i+ 1, i + 2, i + 3);

        counter = 1;

        while (hash_table->list[i].size     >= counter && hash_table->list[i + 1].size >= counter && 
               hash_table->list[i + 2].size >= counter && hash_table->list[i + 3].size >= counter) 
        {
            if (hash_table->list[i].free >= counter && hash_table->list[i].is_init)
                fprintf (dump_file, "|%19s", &hash_table->list[i].leaf[counter].list_elem.list_elem_str);
            else
            fprintf (dump_file, "|       none        ");
            
            if (hash_table->list[i + 1].free >= counter && hash_table->list[i + 1].is_init)
                fprintf (dump_file, "|%19s", &hash_table->list[i + 1].leaf[counter].list_elem.list_elem_str);
            else
                fprintf (dump_file, "|       none        ");

            
            if (hash_table->list[i + 2].free >= counter && hash_table->list[i + 2].is_init)
                fprintf (dump_file, "|%19s", &hash_table->list[i + 2].leaf[counter].list_elem.list_elem_str);
            else
                fprintf (dump_file, "|       none        ");


            if (hash_table->list[i + 3].free >= counter && hash_table->list[i + 3].is_init)
                fprintf (dump_file, "|%19s\n", &hash_table->list[i + 3].leaf[counter].list_elem.list_elem_str);
            else
                fprintf (dump_file, "|       none        \n");
                
            counter++;
        }

        fprintf (dump_file, "\n\n");
    }

    fclose (dump_file);

    return 0;
}

int OutputLenghts (HASH_TABLE_DATA * hash_table)
{
    FILE * dump_file = fopen (HASH_TABLE_LENGHTS, "w");

    int size = 0;

    for (int i = 0; HASH_TABLE_SIZE > i; i++)
    {
        size = hash_table->list[i].size;

        for (int j = 0; size > j; j++)
        {
            if (strcmp (&hash_table->list[i].leaf[j].list_elem.list_elem_str, "nononononononononon"))
            fprintf (dump_file, "%d\n", strlen (&hash_table->list[i].leaf[j].list_elem.list_elem_str));
            
            if (strlen (&hash_table->list[i].leaf[j].list_elem.list_elem_str) == 17)
                fprintf (dump_file, "%s\n", hash_table->list[i].leaf[j].list_elem);
        }
    }

    fclose (dump_file);

    return 0;
}

int OutputCollisions (HASH_TABLE_DATA * hash_table)
{
    FILE * dump_file = fopen (HASH_TABLE_COLLISIONS, "w");

    int size = 0;

    for (int i = 0; HASH_TABLE_SIZE > i; i++)
    {
        size = hash_table->list[i].free;

        fprintf (dump_file, "%d\n", size);
    }

    fclose (dump_file);

    return 0;
}