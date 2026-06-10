
#include <stdio.h>

int searchMatrix(int n, int matrix[n][n], int key)
{
    int row = 0;
    int col = n - 1;  // Start from top-right corner

    while (row < n && col >= 0)
    {
        if (matrix[row][col] == key)
        {
            return 1;   // Found
        }
        else if (matrix[row][col] > key)
        {
            col--;      // Move left
        }
        else
        {
            row++;      // Move down
        }
    }

    return 0;   // Not found
}

int main()
{
    int matrix[4][4] = {
        {10, 20, 30, 40},
        {15, 25, 35, 45},
        {27, 29, 37, 48},
        {32, 33, 39, 50}
    };

    int key = 29;

    if (searchMatrix(4, matrix, key))
        printf("%d found in matrix\n", key);
    else
        printf("%d not found in matrix\n", key);

    return 0;
}