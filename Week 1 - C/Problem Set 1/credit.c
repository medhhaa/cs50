#include <cs50.h>
#include <stdio.h>

int checksum(long c);
int digit_sum(int product);
int digit_count(long c);
void print_card(long c);

int main(void)
{
    //prompt for the input
    long c = get_long("Number: ");

    //checksum using Luhn's Algorithm
    int valid = checksum(c);
    // printf("%i\n",valid);

    if(valid == 0){
        printf("INVALID\n");
    }
    else
    {
        print_card(c);
    }

}

int digit_count(long c)
{
    int count = 0;
    while(c>0)
    {
        count++;
        c /= 10;
    }
    return count;
}

// American Express uses 15-digit numbers, numbers start with 34 or 37;
// MasterCard uses 16-digit, numbers start with 51, 52, 53, 54, or 55;
// and Visa uses 13- and 16-digit, and all Visa numbers start with 4;
void print_card(long c)
{
    int count = digit_count(c);
    if(count == 15){
        //American
        c /= 10000000000000;
        if(c == 34 || c == 37)
        {
            printf("AMEX\n");
        }else{printf("INVALID\n");}
    }
    else if(count == 16)
    {
        //Master OR Visa
        c /= 100000000000000;
        if(c == 51 || c == 52 || c == 53 || c == 54 || c == 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            c/=10;
            if(c == 4)
            {
                printf("VISA\n");
            }else{printf("INVALID\n");}
        }
    }
    else if(count == 13)
    {
        //Visa
        c /= 1000000000000;
        // printf("%li \n", c);
        if(c == 4)
        {
            printf("VISA\n");
        }else{printf("INVALID\n");}
    }
    else
    {
        printf("INVALID\n");
    }
}

int digit_sum(int p) //calculate sum of number given as argument
{
    int sum = 0;
    while(p>0)
    {
        sum += (p%10);
        p /= 10;
    }
    return sum;
}

int checksum(long c)
{
    //1. store sum of digits from last in one variable
    //2. store sum of second to the last digits ( every other digits ) multiplied by 2 in another
    //3. add both of these and check modulo for 0

    int sum_last = 0, sum_alt = 0, digit, flag = 0, sum;
    while(c>0)
    {
       digit = c % 10;
       c /= 10;
       if(flag == 0)  //checking flag for last or second last
       {
            sum_last += digit;
            flag = 1;
            //printf("LAST : digit: %i, sum: %i\n", digit, sum_last );
       }
       else
       {
            sum = digit_sum(digit*2); //take sum of digits and not digit itself!
            sum_alt += (sum);
            flag = 0;
            //printf("ALT : digit: %i, sum: %i\n", digit, sum_alt );
       }
    }
    int add = sum_last + sum_alt;
    //printf("last %i alt  %i  sum %i\n",sum_last, sum_alt, add);

    if(add%10 == 0)
    {
            return 1;
    }else{
            return 0;
    }
    return 0;
}