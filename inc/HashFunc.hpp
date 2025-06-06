#ifndef HASH_FUNC_HPP
#define HASH_FUNC_HPP

inline u_int64_t Crc32HashFunc (const char * elem)
{
    u_int64_t hash = 0;

    __asm__(
        ".intel_syntax noprefix         \n\t"
        "                               \n\t"
        "xor rax, rax                   \n\t"
        "                               \n\t"
        "mov rax, 0xffffffffffffffff    \n\t"
        "                               \n\t"
        "jmp 0f                         \n\t"
        "                               \n\t"
        "1:                             \n\t"
        "                               \n\t"
        "crc32 rax, byte ptr [%[elem]]  \n\t"
        "inc %[elem]                    \n\t"
        "                               \n\t"
        "0:                             \n\t"
        "                               \n\t"
        "cmp byte ptr [%[elem]], 0      \n\t"
        "                               \n\t"
        "ja 1b                          \n\t"
        "mov %[hash], rax               \n\t"
        "                               \n\t"
        :[hash] "=m"(hash)
        :[elem] "d"(elem)
        :"%rax");
        
    return hash;
}

#endif //HASH_FUNC_HPP