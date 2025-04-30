#include "../inc/Utils.hpp"

char * FileToStrWithPutFileSize (const char * file_directory, size_t * file_size)                          
{
    assert (file_directory);

    *file_size = ReadFileSize (file_directory);

    FILE* entry_file = fopen (file_directory, "rb");
    assert (entry_file);

    char * pointer_to_text = NULL;

    pointer_to_text = (char *) calloc (*file_size + 1, sizeof (char));
    assert (file_size);

    size_t check_size = (int) fread (pointer_to_text, sizeof (char), *file_size, entry_file);
    assert (check_size == *file_size);

    pointer_to_text[*file_size] = '\0';

    return pointer_to_text;
}

size_t ReadFileSize (const char * file_directory)
{
    assert (file_directory);

    struct stat to_take_file_size = {};

    stat   (file_directory, &to_take_file_size);

    printf ("%ld - size\n", to_take_file_size.st_size);
    assert (to_take_file_size.st_size);

    return to_take_file_size.st_size;
}

size_t CountStringsAndPutZeroInstNewLine (char * fileFirstElement)                                             // Count quantity of tests
{
    int counterStr = 0;

    while (*fileFirstElement != '\0')
    {
        if (*fileFirstElement == '\n')
        {
            counterStr++;
            
            *fileFirstElement = '\0';
        }

        fileFirstElement++;
    }
    return counterStr + 1;
}
