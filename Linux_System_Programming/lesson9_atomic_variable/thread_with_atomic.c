#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#define BIG 10000000UL
#if __STDC_VERSION__ < 201112L || __STDC_NO_ATOMICS__ == 1
#error "Atomic not supported"
#endif
_Atomic uint64_t count = 0;
// su dung bien Atomic nay se giong nhu su voi mutex
// Nhung khong phai bat ky compiler nao de co the su dung duoc bien Atomic nen chung ta can phai kiem tra xem coi compile co chua atomic hay khong
void *thread_func(void *arg)
{
    for (int i = 0; i < BIG; i++)
    {
        count += i; // ngoai ra
    }
    return NULL;
}
int main()
{
    pthread_t id1, id2;
    pthread_create(&id1, NULL, thread_func, NULL);
    pthread_create(&id2, NULL, thread_func, NULL);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    printf("Value count: %ld\n", count);
    return 0;
}