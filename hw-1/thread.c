#include <stdio.h>
#include <pthread.h>

volatile int n=0;
void* thread1_func(void *arg)
{
    while(1)
    {
        n = n+1;
    }
}


void *thread2_func(void *arg)
{
    while (1)
    {
        if (n != 0)
            printf("N=%d\n",n);
        n = 0;
    }
}

int main()
{
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}

