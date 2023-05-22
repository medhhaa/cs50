#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    //Height from user with conditionals
    do
    {
        n = get_int("Height: ");
    }
    while(n<1 || n>8);

    int i, j;
    for(i=0; i<n; i++)  //row
    {
        // col - left - spaces
        for(j=0; j<n-i-1; j++)
        {
            printf(" ");
        }

        //col - left - bricks (#)
        for(j=0;j<=i;j++)
        {
            printf("#");
        }

        //extra space of 2 blocks
        printf("  ");

        //col - right - bricks
        for(j=0; j<=i; j++)
        {
            printf("#");
        }
        printf("\n");
    }


}