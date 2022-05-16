#include <stdio.h>

int main()
{
    int pagesCount = 0, framesCount = 0, pageFaults = 0, i;
    int pages[1000];
    int frames[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    printf("Enter number of pages: ");
    scanf("%d", &pagesCount);
    printf("Enter pages: ");
    for (i = 0; i < pagesCount; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames (frames <= 7): ");
    scanf("%d", &framesCount);
    if (framesCount < 1 || framesCount > 7)
    {
        printf("Invalid number of frames\n");
        return -1;
    }

    int earliestFrame = 0;
    for (i = 0; i < pagesCount; i++)
    {
        int j;
        for (j = 0; frames[j] != -1; j++)
            if (frames[j] == pages[i])
                break;

        if (frames[j] != pages[i])
        {
            pageFaults++;
            if (j == framesCount)
            {
                frames[earliestFrame] = pages[i];
                earliestFrame = (earliestFrame + 1) % framesCount;
            }
            if (j < framesCount)
                frames[j] = pages[i];
        }

        printf("%d : ", pages[i]);
        for (j = 0; j < framesCount; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }

    printf("Page faults: %d\n", pageFaults);

    return 0;
}