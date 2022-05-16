#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int VM_SIZE = 256;
const int PAGE_SIZE = 256;
const int TLB_SIZE = 16;
const int MM_SIZE = 256;

int main(int argc, char *argv[])
{
    FILE *file;

    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Unable to open file\n");
        return 1;
    }

    char *value = NULL;
    size_t len = 0;
    ssize_t read;
    long long pageNumber, offset, totalHits = 0, pageFaults = 0, pages = 0;
    int queuePosition = 0, physicalAddress = 0, frame, logicalAddress;
    int tlb[TLB_SIZE][2];
    int pageTable[PAGE_SIZE];

    memset(tlb, -1, TLB_SIZE * 2 * sizeof(tlb[0][0]));
    memset(pageTable, -1, sizeof(pageTable));

    int mask = 255, mask1 = 62580, i, hit;

    while ((read = getline(&value, &len, file)) != -1)
    {
        pages++;
        pageNumber = atoi(value);
        pageNumber = pageNumber >> 8;
        pageNumber = pageNumber & mask;

        offset = atoi(value);
        offset = offset & mask;

        logicalAddress = atoi(value);
        frame = 0, physicalAddress = 0;
        hit = 0;

        for (i = 0; i < TLB_SIZE; i++)
        {
            if (tlb[i][0] == pageNumber)
            {
                hit = 1;
                totalHits++;
                frame = tlb[i][1];
                break;
            }
        }

        if (hit == 1)
        {
            printf("TLB Hit\n");
        }
        else
        {
            int f = 0;
            for (i = 0; i < PAGE_SIZE; i++)
            {
                if (pageTable[i] == pageNumber)
                {
                    frame = i;
                    pageFaults++;
                    break;
                }
                if (pageTable[i] == -1)
                {
                    f = 1;

                    break;
                }
            }

            if (f == 1)
            {
                pageTable[i] = pageNumber;
                frame = i;
            }
            tlb[queuePosition][0] = pageNumber;
            tlb[queuePosition][1] = i;
            queuePosition++;
            queuePosition = queuePosition % 15;
        }
        if (logicalAddress < 10000)
            printf("Virtual Address = %d \t\t\t", logicalAddress);
        else
            printf("Virtual Address = %d \t\t", logicalAddress);

        physicalAddress = frame * PAGE_SIZE + offset;
        printf("PHYSICAL ADDRESS = %d\n", physicalAddress);
    }

    double hitRate = (double)totalHits / pages * 100;
    double pageFaultsRate = (double)pageFaults / pages * 100;
    printf("\nTLB Hit Rate = %.2f%c", hitRate, '%');
    printf("\nTLB Miss Rate = %.2f%c", (100 - hitRate), '%');
    printf("\nPage Table Hit Rate = %.2f%c", pageFaultsRate, '%');
    printf("\nPage Table Miss Rate = %.2f%c\n", (100 - pageFaultsRate), '%');
}
