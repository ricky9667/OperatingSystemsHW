#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void copyFile(FILE *source, FILE *destination)
{
    char c;
    while ((c = fgetc(source)) != EOF)
    {
        fputc(c, destination);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Input file and output file are required.\n");
        return -1;
    }

    char *src = argv[1], *dest = argv[2];

    if (access(src, F_OK) != 0)
    {
        printf("File %s is not found.\n", src);
        return -1;
    }

    FILE *source = fopen(src, "r");
    FILE *destination = fopen(dest, "w");

    copyFile(source, destination);

    fclose(source);
    fclose(destination);

    return 0;
}