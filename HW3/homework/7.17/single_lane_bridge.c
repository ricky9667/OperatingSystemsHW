#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int northVillagerCount = 0, southVillagerCount = 0;

void *north(void *ptr)
{
    for (int i = 0; i < northVillagerCount; i++)
    {
        int waitTime = rand() % 8;
        sleep(waitTime);

        printf("North villager %d ready to enter bridge\n", i);

        pthread_mutex_lock(&lock);
        int passBridgeTime = rand() % 5;
        while (passBridgeTime--)
        {
            printf("North villager %d passing bridge, %d seconds left\n", i, passBridgeTime);
            sleep(1);
        }
        pthread_mutex_unlock(&lock);
        printf("North villager %d passed bridge\n", i);
    }

    return NULL;
}

void *south(void *ptr)
{
    for (int i = 0; i < southVillagerCount; i++)
    {
        int waitTime = rand() % 8;
        sleep(waitTime);

        printf("South villager %d ready to enter bridge\n", i);

        pthread_mutex_lock(&lock);
        int passBridgeTime = rand() % 5;
        while (passBridgeTime--)
        {
            printf("South villager %d passing bridge, %d seconds left\n", i, passBridgeTime);
            sleep(1);
        }
        pthread_mutex_unlock(&lock);
        printf("South villager %d passed bridge\n", i);
    }

    return NULL;
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_t north_thread, south_thread;

    printf("Enter number of north villagers: ");
    scanf("%d", &northVillagerCount);
    printf("Enter number of south villagers: ");
    scanf("%d", &southVillagerCount);

    pthread_create(&north_thread, NULL, north, NULL);
    pthread_create(&south_thread, NULL, south, NULL);

    pthread_join(north_thread, NULL);
    pthread_join(south_thread, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}