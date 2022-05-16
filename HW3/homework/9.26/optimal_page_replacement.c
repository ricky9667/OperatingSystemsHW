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
                int k, frameIndex = 0;
                int nextAppearIndex[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

                for (k = i + 1; k < pagesCount; k++)
                    for (frameIndex = 0; frameIndex < framesCount; frameIndex++)
                        if (frames[frameIndex] == pages[k] && nextAppearIndex[frameIndex] == -1)
                            nextAppearIndex[frameIndex] = k;

                int replaceIndex = 0;
                for (frameIndex = 1; frameIndex < framesCount; frameIndex++)
                {
                    if (nextAppearIndex[frameIndex] == -1 && nextAppearIndex[replaceIndex] != -1)
                        replaceIndex = frameIndex;
                    else if (nextAppearIndex[replaceIndex] != -1 && nextAppearIndex[frameIndex] > nextAppearIndex[replaceIndex])
                        replaceIndex = frameIndex;
                }

                frames[replaceIndex] = pages[i];
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