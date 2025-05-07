#include "../inc/HashMain.hpp"
#include "../DL_list/inc/header.h"

bool avx_strcmp (list_elem_t * first_str, list_elem_t * second_str)
{
    my_assert (first_str && second_str);

    __m256i __first_str  = _mm256_loadu_si256 (&first_str->list_elem_opt);    
    __m256i __second_str = _mm256_loadu_si256 (&second_str->list_elem_opt);
    
    return ~(_mm256_movemask_epi8 (_mm256_cmpeq_epi8 (__first_str, __second_str)));
}