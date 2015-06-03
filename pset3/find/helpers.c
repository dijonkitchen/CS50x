/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
//#include <stdio.h> //added for printf
#include "helpers.h"

bool binsearch(int value, int values[], int begin, int end);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n <= 0)
    {
    	return false;
    }

    // Recursive binary search
    return binsearch(value, values, 0, n - 1);

    // linear search
    // for (int i = 0; i < n; i++)
    // {
   	// if (value == values[i])
    // 	{
    // 		return true;
    // 	}
    // }
    // 
    // return false; 
}

bool binsearch(int value, int values[], int begin, int end)
{
    if (begin > end)
        return false;

    //Midpoint
    int mid = (begin + end) / 2;

    //Recursion
    if (value == values[mid])
        return true;

    else if (value > values[mid])
        return binsearch(value, values, mid + 1, end);

    else if (value < values[mid])
        return binsearch(value, values, begin, mid - 1);
   
    else
        return false;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // Bubblesort
	bool swapped = false;

	do
	{			
		for (int i = 0; i < (n -1); i++)
		{
			if (values[i] > values[i + 1])
			{
				int tmp = values[i];
				values[i] = values[i + 1];
				values[i + 1] = tmp;
				swapped = true;
				i = -1;
			}
			else 
				swapped = false;
		}
	} while (swapped == true);
	
	// Testing for sort
    // for (int i = 0; i < n; i++)
	// {
	//     printf("%i\n", values[i]);
	// }	

    return;
}
