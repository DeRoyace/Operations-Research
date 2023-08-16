// Game theory: finding one or more saddle point(s)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 100
int arr[SIZE][SIZE], rowmins[SIZE], colmaxes[SIZE], row, col;
void input()
{
    int i, j;
    printf("\nEnter size of array:\n No. of Rows =  ");
    scanf("%d", &row);
    printf("No. of columns = ");
    scanf("%d", &col);
    printf("\nEnter matrix elements: \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("\nEnter element for row %d column %d : ", i + 1, j + 1);
            scanf("%d", &arr[i][j]);
        }
    }
}

void display()
{
    int i, j;
    printf("\nMatrix: \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}
// int rowmins[N], colmaxes[N];
void saddle()
{
    int i, j, rowmin, colmax, flag = 0;
    for (i = 0; i < row; i++)
    {
        rowmin = arr[i][0];
        for (j = 1; j < col; j++)
        {
            if (rowmin >= arr[i][j])
            {
                rowmin = arr[i][j];
            }
        }
        rowmins[i] = rowmin;
    }
    for (i = 0; i < col; i++)
    {
        colmax = arr[0][i];
        for (j = 1; j < row; j++)
        {
            if (colmax <= arr[j][i])
            {
                colmax = arr[j][i];
            }
        }
        colmaxes[i] = colmax;
    }
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if (rowmins[i] == colmaxes[j])
            {
                printf("Saddle point is %d at row %d col %d\n", rowmins[i], i+1, j+1);
                flag = 1;
            }

        }
    }
    if(flag == 0)
        printf("\nNo saddle point.\n");
}

int main()
{
    input();
    display();
    saddle();
    return 0;
}