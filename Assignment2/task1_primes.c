#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function to check if a number is prime
int isPrime(int num)
{
    if (num < 2)
        return 0;

    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

// Thread A: Sum of first N prime numbers
void *sumPrimes(void *arg)
{
    int N = *(int *)arg;
    long long *sum = malloc(sizeof(long long));

    *sum = 0;
    int count = 0;
    int num = 2;

    while (count < N)
    {
        if (isPrime(num))
        {
            *sum += num;
            count++;
        }
        num++;
    }

    pthread_exit(sum);
}

// Thread B
void *thread1(void *arg)
{
    for (int t = 0; t < 100; t += 2)
    {
        printf("Thread 1 running\n");
        sleep(2);
    }

    pthread_exit(NULL);
}

// Thread C
void *thread2(void *arg)
{
    for (int t = 0; t < 100; t += 3)
    {
        printf("Thread 2 running\n");
        sleep(3);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t A, B, C;
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    // Create threads
    pthread_create(&A, NULL, sumPrimes, &N);
    pthread_create(&B, NULL, thread1, NULL);
    pthread_create(&C, NULL, thread2, NULL);

    // Wait for Thread A and get result
    long long *primeSum;
    pthread_join(A, (void **)&primeSum);

    printf("Sum of first %d prime numbers = %lld\n", N, *primeSum);

    free(primeSum);

    // Wait for Thread B and C
    pthread_join(B, NULL);
    pthread_join(C, NULL);

    printf("All threads completed.\n");

    return 0;
}