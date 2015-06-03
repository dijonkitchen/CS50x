#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    float dollars = 0.01;
    
    do
    {
    
        printf("How much change is owed? \n");
        dollars = GetFloat();
    
    } while (dollars < 0.0);
    
    
    //calculating coins
    int c = round(dollars * 100);
    
//check variables
/*    printf("%f",dollars);*/
/*    printf("%d",c);*/
    
    int p = (((c % 25) % 10) % 5);
    int n = ((c % 25) % 10) / 5;
    int d = ((c % 25) / 10);
    int q = c / 25;
    
    int coins = p + n + d + q;
    
    printf("%d", coins);
    printf("\n");
}

