#include <stdio.h>
#include <time.h>
#define TIME_IT(func) do { clock_t s = clock(); func; clock_t e = clock(); printf("Time: %f s\n", (double)(e-s)/CLOCKS_PER_SEC); } while(0)
void test_func() { for(volatile int i=0; i<1000000; i++); }
int main() { TIME_IT(test_func()); return 0; }
