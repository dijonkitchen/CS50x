#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int h = 0;
    
    do 
    {
        printf("Height: ");
        h = GetInt();
        
    } while (h > 23 || h < 0);
    
    if (h == 0)
    {
    printf("");
    }
    else
    {
        int l = h + 1;
        
        do 
        {
            int x = 0;
            
            //spaces        
            while (x <= (h - 2))
            {
                printf(" ");
                x++;
            }
            
            //hashes        
            while (x < l)
            {
                printf("#");
                x++;
            } 
            
            // new line and decrement
            printf("\n");
            h--;
            
        } while (h > 0);
    }   
}
