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

    char * parsed_data = (char *) calloc (file_size, sizeof (char));

    size_t pars_buf_size = 0;

    for (int i = 0; file_size > i; i++)
    {
        if (isalpha (not_parsed_data[i]))
            parsed_data[pars_buf_size++] = not_parsed_data[i];
        else
        {
            parsed_data[pars_buf_size++] = '\n';

            while (!isalpha (not_parsed_data[i++]));

            i -= 2;
        }
    }

    return parsed_data;
}