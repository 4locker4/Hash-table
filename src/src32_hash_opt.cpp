#include "../inc/HashMain.hpp"

unsigned int Src32HashFunc (const char * hashing_elem)
{
    unsigned int hash = 0;

    __asm__(
        ".intel_syntax noprefix        \n\t"
        "xor rax, rax                  \n\t"
        "mov eax, 0xffffffff           \n\t"
        "jmp .if_loop                  \n\t"
        ".loop:                        \n\t"
        "crc32 eax, byte ptr [%[elem]] \n\t"
        "inc %[elem]                   \n\t"
        ".if_loop:                     \n\t"
        "cmp byte ptr [%[elem]], 0     \n\t"
        "ja .loop                      \n\t"
        "mov %[hash], eax              \n\t"
        :[hash] "=m"(hash)
        :[elem] "d"(hashing_elem)
        :"%rax");
    
    return hash % HASH_TABLE_SIZE;
}