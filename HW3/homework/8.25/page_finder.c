#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096

int main(int argc, char **argv)
{
    unsigned int address;
    unsigned int pageNumber;
    unsigned int offset;

    if (argc < 2)
    {
        printf("Enter the address: ");
        return -1;
    }

    address = atoi(argv[1]);
    pageNumber = address / PAGE_SIZE;
    offset = address % PAGE_SIZE;

    printf("Address = %u\nPage number = %u\nOffset = %u\n", address, pageNumber, offset);

    return 0;
}