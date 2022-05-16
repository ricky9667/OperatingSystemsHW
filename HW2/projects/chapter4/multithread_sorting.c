#include <stdio.h>
#include <pthread.h>

int n, a, b;
int A[50], B[50], C[100];

void *sort_first_list(void *ptr)
{
    for (int j = 1; j < a; j++)
    {
        int key = A[j];
        int i = j - 1;
        while (i >= 0 && key < A[i])
        {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }
    return NULL;
}

void *sort_second_list(void *ptr)
{
    for (int j = 1; j < b; j++)
    {
        int key = B[j];
        int i = j - 1;
        while (i >= 0 && key < B[i])
        {
            B[i + 1] = B[i];
            i--;
        }
        B[i + 1] = key;
    }
    return NULL;
}

void *merge_lists(void *ptr)
{
    int i = 0, j = 0, k = 0;
    while (i < a && j < b)
    {
        if (A[i] < B[j])
            C[k++] = A[i++];
        else
            C[k++] = B[j++];
    }
    while (i < a)
        C[k++] = A[i++];
    while (j < b)
        C[k++] = B[j++];
    return NULL;
}

int main()
{
    pthread_t thread1, thread2, thread3;
    int i;
    a = b = 0;

    printf("Enter size of list: ");
    scanf("%d", &n);
    printf("Enter items of list: ");
    for (i = 0; i < n; i++)
        scanf("%d", &C[i]);

    for (i = 0; i < n; i++)
    {
        if (i < n / 2)
        {
            A[i] = C[i];
            a++;
        }
        else
        {
            B[i - n / 2] = C[i];
            b++;
        }
    }

    pthread_create(&thread1, NULL, &sort_first_list, NULL);
    pthread_create(&thread2, NULL, &sort_second_list, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_create(&thread3, NULL, &merge_lists, NULL);
    pthread_join(thread3, NULL);

    printf("After merge: ");
    for (i = 0; i < a + b; i++)
        printf("%d ", C[i]);

    return 0;
}