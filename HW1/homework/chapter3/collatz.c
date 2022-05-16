#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void collatz(int n)
{
    if (n == 1)
    {
        printf("1\n");
        return;
    }

    printf("%d, ", n);
    (n % 2 == 0) ? collatz(n / 2) : collatz(3 * n + 1);
}

int main()
{
    int n, exit_status;
    pid_t pid = fork();

    switch (pid)
    {
    case -1:
        perror("fork");
        exit(-1);
    case 0:
        printf("[Child process]\n");
        printf("Enter a number: ");
        scanf("%d", &n);

        if (n < 1)
        {
            printf("Invalid number.\n");
            exit(0);
        }
        collatz(n);
        scanf("%d", &exit_status);
        break;
    default:
        printf("[Parent process]\n");
        wait(&exit_status);
        printf("[Parent] Child's exit status is [%d]\n", WEXITSTATUS(exit_status));
        break;
    }

    return 0;
}