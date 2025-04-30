#ifndef UTILS_HPP
#define UTILS_HPP

#include <sys/stat.h>

#include "./HashMain.hpp"

char * FileToStr                           (const char * file_directory, size_t * file_size);
size_t ReadFileSize                        (const char * file_directory);
size_t CountStringsAndPutZeroInstNewLine   (char * fileFirstElement);                                          // Count quantity of \n


#endif // UTILS_HPP