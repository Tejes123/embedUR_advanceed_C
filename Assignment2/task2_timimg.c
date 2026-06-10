#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

long long primeSum = 0;

/* ---------------- Signal Handler ---------------- */

void signalHandler(int sig)
{
    printf("\nSIGINT received (Ctrl+C).\n");
    printf("Program continues running...\n");
}

/* ---------------- Utility Functions ---------------- */

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

/* ---------------- Actual Work Functions ---------------- */

void computePrimeSum(int N)
{
    int count = 0;
    int num = 2;

    primeSum = 0;

    while (count < N)
    {
        if (isPrime(num))
        {
            primeSum += num;
            count++;
        }

        num++;
    }
}

void printThread1()
{
    for (int t = 0; t < 100; t += 2)
    {
        printf("Thread 1 running\n");
        sleep(2);
    }
}

void printThread2()
{
    for (int t = 0; t < 100; t += 3)
    {
        printf("Thread 2 running\n");
        sleep(3);
    }
}

/* ---------------- Thread Wrappers ---------------- */

void *primeThread(void *arg)
{
    int N = *(int *)arg;

    clock_t start = clock();

    printf("Prime thread started\n");

    computePrimeSum(N);

    clock_t end = clock();

    double timeTaken =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Prime thread completed\n");
    printf("Prime thread time = %.6f seconds\n",
           timeTaken);

    pthread_exit(NULL);
}

void *thread1(void *arg)
{
    clock_t start = clock();

    printf("Thread 1 started\n");

    printThread1();

    clock_t end = clock();

    double timeTaken =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Thread 1 completed\n");
    printf("Thread 1 time = %.6f seconds\n",
           timeTaken);

    pthread_exit(NULL);
}

void *thread2(void *arg)
{
    clock_t start = clock();

    printf("Thread 2 started\n");

    printThread2();

    clock_t end = clock();

    double timeTaken =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Thread 2 completed\n");
    printf("Thread 2 time = %.6f seconds\n",
           timeTaken);

    pthread_exit(NULL);
}

/* ---------------- Main ---------------- */

int main()
{
    int N;

    pthread_t tPrime;
    pthread_t t1;
    pthread_t t2;

    /* Register SIGINT handler */
    signal(SIGINT, signalHandler);

    printf("Enter N: ");
    scanf("%d", &N);

    clock_t programStart = clock();

    printf("\nCreating threads...\n");

    pthread_create(&tPrime, NULL, primeThread, &N);
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    printf("All threads created\n");

    pthread_join(tPrime, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    clock_t programEnd = clock();

    double totalTime =
        (double)(programEnd - programStart) /
        CLOCKS_PER_SEC;

    printf("\n=====================\n");
    printf("Sum of first %d prime numbers = %lld\n",
           N,
           primeSum);

    printf("Total program time = %.6f seconds\n",
           totalTime);

    printf("=====================\n");

    return 0;
}