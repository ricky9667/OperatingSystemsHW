#include <stdio.h>
#include <stdlib.h>

#define CYLINDERS 5000
#define REQUESTS 1000

int start = 0;

int ranArray[REQUESTS];

int *sort_array()
{
    int temp = 0, i = 0, j = 0;

    for (i = 0; i < REQUESTS; ++i)
    {
        for (j = i + 1; j < REQUESTS; ++j)
        {
            if (ranArray[i] > ranArray[j])
            {
                temp = ranArray[i];
                ranArray[i] = ranArray[j];
                ranArray[j] = temp;
            }
        }
    }

    return ranArray;
}

int fcfs(int *ranArray)
{
    int i = 0, headMovement = 0, thisStart = ranArray[start];

    for (i = start; i < REQUESTS; i++)
        headMovement += abs(ranArray[i] - thisStart);

    for (i = 0; i < start; i++)
        headMovement += abs(thisStart - ranArray[i]);

    return headMovement;
}

int sstf(int *ranArray)
{
    ranArray = sort_array();

    int leftIndex = start - 1, rightIndex = start + 1;
    int smallDiff = 0, largeDiff = 0;
    int headMovement = 0, total = REQUESTS - 2, new_head = start;

    while (total >= 0)
    {
        smallDiff = abs(ranArray[new_head] - ranArray[leftIndex]);
        largeDiff = abs(ranArray[rightIndex] - ranArray[new_head]);

        if (smallDiff < largeDiff)
        {
            headMovement += smallDiff;
            new_head = leftIndex;
            leftIndex--;
        }
        else
        {
            headMovement += largeDiff;
            new_head = rightIndex;
            rightIndex++;
        }

        total--;
    }

    return headMovement;
}


int scan(int *ranArray)
{
    int i = 0;
    int current = 0, temp = ranArray[start], difference = 0;
    int headMovement = 0;

    for (i = start - 1; i >= 0; --i)
    {

        current = ranArray[i];
        difference = abs(temp - current);
        headMovement += difference;
        temp = current;
    }

    headMovement += temp;
    temp = 0;

    for (i = start + 1; i < REQUESTS; i++)
    {

        current = ranArray[i];
        difference = abs(current - temp);
        headMovement += difference;
        temp = current;
    }

    return headMovement;
}

int cscan(int *ranArray)
{
    int i = 0;
    int current = 0, temp = ranArray[start], difference = 0;
    int headMovement = 0, max = 4999;

    for (i = start + 1; i < REQUESTS; i++)
    {
        current = ranArray[i];
        difference = abs(temp - current);
        headMovement += difference;
        temp = current;
    }

    headMovement += max - temp;
    temp = 0;
    headMovement += 4999;

    for (i = 0; i < start; i++)
    {
        current = ranArray[i];
        difference = abs(current - temp);
        headMovement += difference;
        temp = current;
    }

    return headMovement;
}

int main(int argc, char *argv[])
{
    int i = 0;
    start = atoi(argv[1]);

    if (argc != 2)
    {
        printf("Please execute with a number in 0-4999.\n");
        exit(-1);
    }

    for (i = 0; i < REQUESTS; i++)
        ranArray[i] = rand() % 5000;

    printf("\nStart index: %d, start value: %d\n\n", start, ranArray[start]);

    printf("FCFS head movements: %d\n", fcfs(ranArray));
    printf("SSTF head movements: %d\n", sstf(ranArray));
    printf("SCAN head movements: %d\n", scan(ranArray));
    printf("CSCAN head movements: %d\n", cscan(ranArray));

    return 0;
}
