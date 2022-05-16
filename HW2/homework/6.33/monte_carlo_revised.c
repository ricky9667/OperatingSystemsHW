#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int n, totalPoints;
int pointsInCircle = 0;

void *calculate(void *ptr)
{
    int i = 0;
    for (i = 0; i < totalPoints; i++)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1)
        {
            pthread_mutex_lock(&lock);
            pointsInCircle++;
            pthread_mutex_unlock(&lock);
        }
    }
    return NULL;
}

int main()
{
    printf("Enter number of threads: ");
    scanf("%d", &n);
    while (n <= 1)
    {
        printf("\nNumber should be greater than 1\n");
        printf("Enter number of threads: ");
        scanf("%d", &n);
    }

    printf("Enter number of points: ");
    scanf("%d", &totalPoints);

    int i, result;
    pthread_t threads[n];
    pthread_mutex_init(&lock, NULL);

    for (i = 0; i < n; i++)
    {
        result = pthread_create(&threads[i], NULL, calculate, NULL);
        if (result)
            printf("\nThread creation failed\n");
    }

    for (i = 0; i < n; i++)
    {
        result = pthread_join(threads[i], NULL);
        if (result)
            printf("\nThread join failed\n");
    }

    pthread_mutex_destroy(&lock);

    double pi = (4.0 * pointsInCircle / totalPoints) / n;
    printf("Estimated PI with %d threads: %f\n", n, pi);

    return 0;
}
