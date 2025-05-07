#include "../inc/Parsing.hpp"

static const char * ENTRY_FILE_NAME  = "../HashTable/Text/Tolstoi.txt";
static const char * PARSED_FILE_NAME = "../HashTable/Text/ParsedText.txt";

static char * ParsingFile (char * not_parsed_data, size_t file_size);

int PrepairFile ()
{
    size_t file_size = 0;

    char * pointer_to_file_data = FileToStr (ENTRY_FILE_NAME, &file_size);

    pointer_to_file_data = ParsingFile (pointer_to_file_data, file_size);

    FILE * parsed_file = fopen (PARSED_FILE_NAME, "w");

    //assert (parsed_file);

    fprintf (parsed_file, "%s\0", pointer_to_file_data);

    fclose (parsed_file);

    return 0;
}

char * ParsingFile (char * not_parsed_data, size_t file_size)
{
    //assert (not_parsed_data);

    size_t n_words = CountWords (not_parsed_data);

    char * parsed_data = (char *) calloc (n_words, sizeof (list_elem_t));

    size_t pars_buf_size = 0;

    size_t counter = 0;

    for (int index = 0; file_size > index; index++)
    {
        counter = 0;

        if (isalpha (not_parsed_data[index]))
            parsed_data[pars_buf_size++] = not_parsed_data[index];
        else
        {
            parsed_data[pars_buf_size++] = '\n';

            for ( ; sizeof (list_elem_t) > counter; counter++)
                parsed_data[pars_buf_size++] = NULL;

            while (!isalpha (not_parsed_data[index++]));

            index -= 2;
        }
    }

    return parsed_data;
}

size_t CountWords (char * text_ptr)
{
    assert (text_ptr);

    size_t counter = 0;

    while (*text_ptr != '\0')
    {
        while (isalpha (*text_ptr))
            text_ptr++;
        
        counter++;

        while (!isalpha (*text_ptr))
            text_ptr++;
    }

    return counter;
}