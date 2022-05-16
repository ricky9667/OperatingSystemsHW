#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define CUSTOMERS_COUNT 5
#define RESOURCES_COUNT 4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int allocation[CUSTOMERS_COUNT][RESOURCES_COUNT] = {
    {2, 0, 0, 1},
    {3, 1, 2, 1},
    {2, 1, 0, 3},
    {1, 3, 1, 2},
    {1, 4, 3, 2}};

int max[CUSTOMERS_COUNT][RESOURCES_COUNT] = {
    {4, 2, 1, 2},
    {5, 2, 5, 2},
    {2, 3, 1, 6},
    {1, 4, 2, 4},
    {3, 6, 6, 5}};

int available[RESOURCES_COUNT] = {3, 3, 2, 1};

int need[CUSTOMERS_COUNT][RESOURCES_COUNT] = {0};

void printCurrentData(int customer)
{
    int i;
    printf("\nAllocation: ");
    for (i = 0; i < RESOURCES_COUNT; i++)
        printf("%d ", allocation[customer][i]);

    printf("\nMax: ");
    for (i = 0; i < RESOURCES_COUNT; i++)
        printf("%d ", max[customer][i]);

    printf("\nNeed: ");
    for (i = 0; i < RESOURCES_COUNT; i++)
        printf("%d ", need[customer][i]);

    printf("\nAvailable: ");
    for (i = 0; i < RESOURCES_COUNT; i++)
        printf("%d ", available[i]);
}

void *request(void *ptr)
{
    int *customer = (int *)ptr;
    int i;

    // printf("\nCustomer %d is checking ... \n", *customer);

    while (1)
    {
        int checkIsSafe = 1;
        for (i = 0; i < RESOURCES_COUNT; i++)
        {
            if (need[*customer][i] > available[i])
            {
                checkIsSafe = 0;
                break;
            }
        }

        if (checkIsSafe)
        {
            break;
        }
    }

    pthread_mutex_lock(&lock);
    printf("\nCustomer %d is requesting ... \n", *customer);
    printCurrentData(*customer);

    for (i = 0; i < RESOURCES_COUNT; i++)
        available[i] += allocation[*customer][i];

    printf("\nNew available: ");
    for (i = 0; i < RESOURCES_COUNT; i++)
        printf("%d ", available[i]);
    printf("\n");

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    int i, j;
    for (i = 0; i < CUSTOMERS_COUNT; i++)
    {
        for (j = 0; j < RESOURCES_COUNT; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    pthread_mutex_init(&lock, NULL);
    pthread_t threads[CUSTOMERS_COUNT];

    int a = 0, b = 1, c = 2, d = 3, e = 4;
    pthread_create(&threads[a], NULL, request, &a);
    pthread_create(&threads[b], NULL, request, &b);
    pthread_create(&threads[c], NULL, request, &c);
    pthread_create(&threads[d], NULL, request, &d);
    pthread_create(&threads[e], NULL, request, &e);

    for (i = 0; i < CUSTOMERS_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
        printf("Joined thread %d successfully.\n", i);
    }

    return 0;
}