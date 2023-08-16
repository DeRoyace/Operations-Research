// Program to compute initial basic feasible solution
// of a transportation table using North-West Corner Method (NWCM).

#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
#define min(a, b) a < b ? a: b

int arr[SIZE][SIZE];
int row, col;

void input()
{
    // Taking the transportation matrix from the user;
    // Inputs: Origin Y to Destination X, Capacity or Source supply, Requirements / Demand.
    printf("\nENTER NUMBER OF ORIGINS: ");
    scanf("%d", &row);
    printf("ENTER NUMBER OF DESTINATIONS: ");
    scanf("%d", &col);
    // Below incrementing both row and col by 1 for Capacity column and Requirement row
    row++;
    col++;
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (i < row - 1 && j < col - 1)
            {
                printf("\nEnter cost for ORIGIN %d to DESTINATION %d: ", i + 1, j + 1);
                scanf("%d", &arr[i][j]);
            }
            else if (j == col - 1 && i != row - 1)
            {
                printf("\nEnter total CAPACITY for ORIGIN %d: ", i + 1);
                scanf("%d", &arr[i][j]);
            }
            else if (i == row - 1 && j != col - 1)
            {
                printf("\nEnter REQUIREMENTS for DESTINATION %d: ", j + 1);
                scanf("%d", &arr[i][j]);
            }
        }
        printf("\n-------------------------------------------------------------------\n");
    }
}

int sum(int v)
{
    // if v = 1 the function return sum of capacity
    // if v = 0 the function return sum of requirements
    int i, sum = 0;
    if(v)
    {
        for (i = 0; i < row-1; i++)
        sum += arr[i][col-1];   // stores sum of Capacities
    }
    else
    {
        for (i = 0; i < col-1; i++)
        sum += arr[row-1][i];   // stores sum of Requirements
    }
    return sum;
}

void display()
{
    int i, j;
    printf("\n");
    for (i = -1; i < row; i++)
    {
        for (j = -1; j < col; j++)
        {
            if (i == -1)
            {
                if (j != -1 && j != col - 1)
                    printf("D%d\t", j + 1);
                else if(j == col-1)
                    printf("Capacity");
                else
                    printf("\t\t");
            }
            else if ( j == -1)
            {
                if(i != -1 && i != row-1)
                printf("ORIGIN %d\t", i+1);
                else if(i == row-1 )
                printf("Requirements\t");
            }
            else if(i == row-1 && j == col-1)
            {
                if(sum(1) == sum(0))
                printf("%d", sum(1));
                else
                printf("%d \\ %d", sum(0), sum(1));
            }
            else
                printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}

void balancing()
{
    // 1 = capacity
    // 0 = requirements
    int i;
    int req = sum(0);
    int cap = sum(1);
    if(req != cap)
    {
        if(req > cap)
        {
            // adding row between requirements and last origin row
            row++;
            for(i = 0; i < col-1; i++)
            {
                arr[row-1][i] = arr[row-2][i]; // swapping requirements row values
                arr[row-2][i] = 0;  // making all the cost of new row 0
            }
            // in order to make capacity = requirement: 
            arr[row-2][col-1] = abs(req - cap); // capacity is given to new row
        }
        else
        {
            // adding column between capacity column and last destination column
            col++;
            for(i = 0; i < row-1; i++)
            {
                arr[i][col-1] = arr[i][col-2]; // swapping capacity column values
                arr[i][col-2] = 0;  // making all the cost of new column 0.
            }
            // in order to make capacity = requirement: 
            arr[row-1][col-2] = abs(req - cap); // requirement is given to new column
        }
        printf("\nTransportation Matrix after Balancing:");
        display();
    }
}

int compute()
{
    // code to compute Transportation problem using NWCM:
    int i = 0, j = 0, allot, cost = 0;
    for(; i < row-1 && j < col-1; )     // executing the loop until we reach the right-bottom corner cost
    {
        if(arr[i][col-1] != 0 && arr[row-1][j] != 0)
        {
            // below getting allotment value by finding min of REQUIREMENT and CAPACITY, corresponding to that cost
            allot = min(arr[i][col-1], arr[row-1][j]);
            // below allocating the min(capacity, requirement) to the North-West corner cell whose requirement and capacity != 0
            cost += arr[i][j] * allot;  // adding the allotment and cost product to the TOTAL COST
            printf("\n%d * %d", allot, arr[i][j]);
            printf("\nCost = %d", cost);
            arr[i][col-1] -= allot;
            arr[row-1][j] -= allot;
            display();
        }
        else if(arr[i][col-1] == 0)
        i++;
        else if(arr[row-1][j] == 0)
        j++;
    }
    return cost;    // returntotal cost i.e. basic feasible solution of the inputed Transportation Matrix
}

int main()
{
    input();
    display();
    balancing();
    printf("\nTotal Cost = %d\n", compute());
    return 0;
}