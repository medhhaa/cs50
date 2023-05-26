#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int n = strlen(input);
    //base case
    if (n == 0)
    {
        return 0;
    }
    else
    {
        //store the last digit in int form.
        int temp = input[n - 1] - 48;

        //remove last letter by adding \0 and pass reduced input to recursive function.
        input[n - 1] = '\0';

        return convert(input) * 10 + temp ;

    }
}
