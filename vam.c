// Program to compute initial basic feasible solution
// of a transportation table using Vogel's Approximation Method (VAM).

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // for using INT_MAX, INT_MIN
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
    // Below incrementing both row and col by 2 for Capacity column, Requirement row, Row and Column Penalty.
    row += 2; col += 2;
    int i, j;
    for (i = 0; i < row-1; i++)
    {
        for (j = 0; j < col-1; j++)
        {
            if (i < row - 2 && j < col - 2)
            {
                printf("\nEnter cost for ORIGIN %d to DESTINATION %d: ", i + 1, j + 1);
                scanf("%d", &arr[i][j]);
            }
            else if (j == col - 2 && i != row - 2)
            {
                printf("\nEnter total CAPACITY for ORIGIN %d: ", i + 1);
                scanf("%d", &arr[i][j]);
            }
            else if (i == row - 2 && j != col - 2)
            {
                printf("\nEnter REQUIREMENTS for DESTINATION %d: ", j + 1);
                scanf("%d", &arr[i][j]);
            }
        }
        printf("\n-------------------------------------------------------------------\n");
    }
}

int sum(int v)  // computes sum of capacities and requirements
{
    // if v = 1 the function return sum of capacity
    // if v = 0 the function return sum of requirements
    int i, sum = 0;
    if(v)
    {
        for (i = 0; i < row-2; i++)
        sum += arr[i][col-2];   // stores sum of Capacities
    }
    else
    {
        for (i = 0; i < col-2; i++)
        sum += arr[row-2][i];   // stores sum of Requirements
    }
    return sum;
}

void display()  // displays the transportation matrix
{
    int i, j;
    printf("\n");
    for (i = -1; i < row; i++)
    {
        for (j = -1; j < col; j++)
        {
            if (i == -1)
            {
                if (j != -1 && j < col - 2)
                    printf("D%d\t", j + 1);
                else if(j == col-2)
                    printf("Capacity\t");
                else if (j == col-1)
                    printf("Row Penalty");
                else
                    printf("\t\t");
            }
            else if ( j == -1)
            {
                if(i != -1 && i < row-2)
                printf("ORIGIN %d\t", i+1);
                else if(i == row-2 )
                printf("Requirements\t");
                else if(i == row-1)
                printf("Column Penalty\t");
            }
            else if(i == row-2 && j == col-2)
                printf("%d \\ %d\t", sum(0), sum(1));
            else if(j == col-1 && i < row-2)
                printf("\t%d", arr[i][j]);
            else if( (i == row-1 && j >= col-2) || (i == row-2 && j == col-1)){}
            else
                printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n-------------------------------------------------------------------\n");
}

void balancing()
{
    // this function checks whether the requirements and capacity are equal or not. 
    // If not then addidtion of row or columns takes place in order to balance it,
    // with their corresponding requirements or capacity value computed by their difference of original value.
    // sum(1) = sum of capacities
    // sum(0) = sum of requirements
    int i;
    int req = sum(0);
    int cap = sum(1);
    if(req != cap)
    {
        if(req > cap)
        {
            // adding row between requirements and last origin row
            row++;
            for(i = 0; i < col-2; i++)
            {
                arr[row-2][i] = arr[row-3][i]; // swapping requirements row values
                arr[row-3][i] = 0;  // making all the cost of new row 0
            }
            // in order to make capacity = requirement: 
            arr[row-3][col-2] = abs(req - cap); // capacity is given to new row
        }
        else
        {
            // adding column between capacity column and last destination column
            col++;
            for(i = 0; i < row-2; i++)
            {
                arr[i][col-2] = arr[i][col-3]; // swapping capacity column values
                arr[i][col-3] = 0;  // making all the cost of new column 0.
            }
            // in order to make capacity = requirement: 
            arr[row-2][col-3] = abs(req - cap); // requirement is given to new column
        }
        printf("\nTransportation Matrix after Balancing:");
        display();
    }
}
int mins[2];
void rowmins(int row_index) // finding two minimum cost value in a row
{
    int i, min1, min2, min1_pos;
    min1 = min2 = INT_MAX;
    for(i = 0; i < col-2; i++)
    {
        if(min1 > arr[row_index][i] && arr[row-2][i] != 0)
        {
            min2 = min1;
            min1 = arr[row_index][i];
            min1_pos = i;
        }
        else if(min2 > arr[row_index][i] && arr[row-2][i] != 0 && i != min1_pos)
        min2 = arr[row_index][i];
    }
    if(min2 == INT_MAX)
    min2 = min1;
    mins[0] = min1;
    mins[1] = min2;
}

void colmins(int col_index) // finding two minimum costs in column of a given column index
{
    // this method is without using INT_MAX unlike rowmins(...)
	int k, min1, min2, min1_pos;
	min1 = arr[0][col_index];
	for (k = 1; k < row - 2; k++)
	{
		if (min1 > arr[k][col_index] && arr[k][col - 2] != 0)
		{
			min1 = arr[k][col_index];
			min1_pos = k;
		}
	}

	for(k = 0; k < row-2; k++)
	{
		if (arr[k][col - 2] != 0 && k != min1_pos)
		min2 = arr[k][col_index];
	}
	for (k = 0; k < row - 2; k++)
	{
		if (min2 > arr[k][col_index] && arr[k][col - 2] != 0 && k != min1_pos)
			min2 = arr[k][col_index];
	}
	mins[0] = min1;
	mins[1] = min2;
}

void penalty()  // computing row and column penalties
{
    int i;
    // computing row penalty:
    for(i = 0; i < row-2; i++)
    {
        if(arr[i][col-2] != 0)
        {
            rowmins(i);
            arr[i][col-1] = abs(mins[0] - mins[1]);
        }
        else
        arr[i][col-1] = -1;
    }

    // computing column penalty:
    for(i = 0; i < col-2; i++)
    {
        if(arr[row-2][i] != 0)
        {
            colmins(i);
            arr[row-1][i] = abs(mins[0] - mins[1]);
        }
        else
        arr[row-1][i] = -1;
    }
}
int maxPenalty[2];  // maxPenalty[ index, row/col index indicator]
void getMaxPenalty()    // finds the maximum penalty in row and column
{
    int i, maxColPenalty, maxRowPenalty, rowpos, colpos;
    maxColPenalty = maxRowPenalty = INT_MIN;
    for(i = 0; i < row-2; i++)
    {
        if( maxRowPenalty < arr[i][col-1])
        {
            maxRowPenalty = arr[i][col-1];
            rowpos = i;
        }
    }

    for(i = 0; i < col-2; i++)
    {
        if( maxColPenalty < arr[row-1][i])
        {
            maxColPenalty = arr[row-1][i];
            colpos = i;
        }
    }

    if(maxColPenalty > maxRowPenalty)
    {
        maxPenalty[0] = colpos;
        maxPenalty[1] = 0;  // indicates column index
    }
    else
    {
        maxPenalty[0] = rowpos;
        maxPenalty[1] = 1;  // indicates row index
    }

}

int compute()
{
    // code to compute Transportation problem using Vogel's Approximation method:
    int i = 0, j = 0, allot, cost = 0;
    while(sum(1) !=0 && sum(0) != 0)     // executing the loop until all requirements and capacity cells are 0
    {
        penalty();
        display();
        getMaxPenalty();
        int minCost = INT_MAX;
        int row_index, col_index;
        if(maxPenalty[1])
        {
            // max penalty in row
            row_index = maxPenalty[0];
            for(j = 0; j < col -2; j++)
            {
                if(minCost > arr[row_index][j] && arr[row-2][j] != 0)
                {
                    minCost = arr[row_index][j];
                    col_index = j;
                }
            }
        }
        else
        {
            // max penalty in column
            col_index = maxPenalty[0];
            for(i = 0; i < row-2; i++)
            {
                if(minCost > arr[i][col_index] && arr[i][col-2] != 0)
                {
                    minCost = arr[i][col_index];
                    row_index = i;
                }
            }
        }
        i = row_index;
        j = col_index;
        if(arr[i][col-2] != 0 && arr[row-2][j] != 0)
        {
            // below getting allotment value by finding min of REQUIREMENT and CAPACITY, corresponding to that cost
            allot = min(arr[i][col-2], arr[row-2][j]);
            // below allocating the min(capacity, requirement) to the cell whose cost is minimum and its corresponding requirement and capacity != 0
            cost += arr[i][j] * allot;  // adding the allotment and cost product to the TOTAL COST
            printf("\n%d * %d", allot, arr[i][j]);
            printf("\nCost = %d", cost);
            arr[i][col-2] -= allot;
            arr[row-2][j] -= allot;
            display();
        }
    }
    return cost;    // returns total cost i.e. basic feasible solution of the inputed Transportation Matrix
}

int main()
{
    input();
    display();
    balancing();
    printf("\nTotal Cost = %d\n", compute());
    return 0;
}