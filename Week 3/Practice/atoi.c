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



// what is happening here is:
// each time the last integer is being extracted from the string input
// and the size is being reduced by 1
// So, for the no 123  :

// First call:
//     c = 3; (assume after - 48)
//     input = "12";
//     return convert("12") * 10 + 3;  to MAIN  // this call will initialize the second iteration

//      Second call:
//              c = 2;
//              input = "1";
//               return convert("1") * 10 + 2;  to First

//               Third call:
//                           c = 1;
//                           input = "";
//                           return convert("")*10 + 1;   to Second
//                           // here the if statement will execute and 0 will be returned: convert("") = 0
//                            return 0*10 + 1 = 1 to Second

//        Second call:
//              convert("1") = 1
//              return 1*10 + 2 = 12 to Fisrt

// First call:
//      convert("12") = 12
//      return 12*10 + 3 = 123 to Main;