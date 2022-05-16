#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int totalPoints = 0;
int pointsInCircle = 0;

void *calculate(void *ptr)
{
    int i = 0;
    for (i = 0; i < totalPoints; i++)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1)
            pointsInCircle++;
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t thread;

    printf("Enter number of points: ");
    scanf("%d", &totalPoints);
    while (totalPoints <= 0)
    {
        printf("\nNumber not valid!\n");
        printf("Enter an integer: ");
        scanf("%d", &totalPoints);
    }

    pthread_create(&thread, NULL, &calculate, NULL);
    pthread_join(thread, NULL);

    double pi = 4.0 * pointsInCircle / totalPoints;
    printf("Estimated PI: %f\n", pi);
    return 0;
}