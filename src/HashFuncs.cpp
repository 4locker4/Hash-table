#include "../inc/HashMain.hpp"

u_int64_t LenghtCalc (const char* elem)
{
    u_int64_t hash = 0;

    while (*elem != '\0')
    {
        hash++;
        elem++;
    }

    return hash;
}

u_int64_t AsciiSumCalc (const char* elem)
{
    u_int64_t hash = 0;

    while (*elem != '\0')
    {
        hash += *elem;
        elem++;
    }

    return hash;
}

u_int64_t DJB2Hash (const char* elem)
{
    u_int64_t hash = 0;

    while (*elem)
    {
        hash = ((hash << 5) + hash) + (*elem);

        elem++;
    }
    
    return hash;
}

u_int64_t JENKINS (const char* elem)
{
    u_int64_t hash = 0;

    while (*elem != '\0')
    {
        hash += (char) *elem++;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

u_int64_t Adler_32 (const char* elem)
{
    size_t s1 = 1;
    size_t s2 = 0;
  
    while(*elem != '\0')
    {
        s1 = ( s1 + *( elem++ ) ) % 65521;
        s2 = ( s2 + s1 ) % 65521;
    }
    return ( s2 << 16 ) + s1;
}

u_int64_t CRC32 (const char* elem)
{
    u_int64_t hash = 0xFFFFFFFF;

    while (*elem != '\0')
    {
        size_t byte = (char) *elem++;
        hash = (hash >> 8) ^ crc32_table[(hash ^ byte) & 0xFF];
    }

    return hash ^ 0xFFFFFFFF;
}