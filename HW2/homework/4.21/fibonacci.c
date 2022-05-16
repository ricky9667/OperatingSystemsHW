#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

int n;
long long fib[100] = {1, 1};

void *fibonacci(void *ptr)
{
    int i = 0;
    for (i = 2; i < n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    return NULL;
}

int main()
{
    pthread_t thread;

    printf("Enter an integer: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("\nNumber not valid!\n");
        printf("Enter an integer: ");
        scanf("%d", &n);
    }

    if (n > 90)
        printf("(Integers greater than 90 may cause an overflow)\n");

    pthread_create(&thread, NULL, &fibonacci, NULL);
    pthread_join(thread, NULL);

    int i = 0;
    for (i = 0; i < n; i++)
        printf("%lld ", fib[i]);

    return 0;
}