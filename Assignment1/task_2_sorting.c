#include <stdio.h>

void rearrangeEvenOdd(int *arr, int size)
{
    int *current, *search, *shift;
    int temp;

    for (current = arr + 1; current < arr + size; current++)
    {
        if ((*current % 2) == 0)   // Current element is even
        {
            search = current;

            // Find first odd number before current
            while (search > arr && (*(search - 1) % 2) != 0)
            {
                search--;
            }

            if (search != current)
            {
                temp = *current;

                // Shift odd numbers right
                for (shift = current; shift > search; shift--)
                {
                    *shift = *(shift - 1);
                }

                *search = temp;
            }
        }
    }
}

void printArray(int *arr, int size)
{
    int *ptr;

    for (ptr = arr; ptr < arr + size; ptr++)
    {
        printf("%d ", *ptr);
    }
    printf("\n");
}

int main()
{
    int arr[] = {1, 4, 3, 6, 8, 5, 2, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, size);

    rearrangeEvenOdd(arr, size);

    printf("After rearranging:\n");
    printArray(arr, size);

    return 0;
}