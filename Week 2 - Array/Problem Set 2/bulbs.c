#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string msg = get_string("Message: ");
    int length = strlen(msg);
    for (int k = 0; k < length; k++)
    {
        //converting to binary by dividing by 2 and remainder
        int dec = msg[k];
        int bits[BITS_IN_BYTE], i = 7;
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            bits[j] = 0;
        }
        while (dec > 0)
        {
            bits[i] = dec % 2;
            dec /= 2;
            i--;
        }
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            //Call lights function
            print_bulb(bits[j]);
        }
        printf("\n");
    }
}


void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
