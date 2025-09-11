#include <stdio.h>
#include <string.h>
#include <stdalign.h>
#include <stdbool.h>
#include <immintrin.h>

void cleanstr(char** p)
{
  if(*p)
  {
    printf("Value: %s, Address: %p\n", *p, *p);
  }
}

#define ACSTR __attribute__((__cleanup__(cleanstr))) char*
__attribute__((always_inline)) bool __faststrcmp(__m128i V1,__m128i V2)
{
  __m128i mm_cmp = _mm_cmpeq_epi64(V1, V2);
  return _mm_movemask_epi8(mm_cmp) == 0xFFFF;
}

// bool xorupper(char c)
// {
//   return ((c & (~32)) ^ (c)) == 0b00100000;
// }

char xorupper(char c)
{
  return ((c & (~32)) ^ (c)) ;
}


int main(int argc, char *argv[])
{
  // char I[16];
  //
  // scanf("%s", I);
  // ACSTR V = (char*) malloc(16);
  // ACSTR S = (char*) malloc(16);
  //
  // memcpy( V, I , 16);
  // memcpy( S, "FFFFFFFFFFFFFFFF", 16);
  //
  // __m128i V1 = _mm_loadu_epi64((__m128i*)V); // Unaligned load ( Potentially straddles cache lines )
  // __m128i V2 = _mm_loadu_epi64((__m128i*)S); // Unaligned load ( Potentially straddles cache lines )
  //
  // printf("%lu\n", sizeof("FFFFFFFFFFFFFFF"));
  // if(__faststrcmp(V1, V2))
  //   printf("It Worked\n");


  char s = 'B'; 

  printf("%c\n", (char) (s & (~32)) ^ (s));

  for(char i = 'A'; i <= '~'; i++)
  {
    printf("%c",xorupper(i));
  }
  return EXIT_SUCCESS;
}

