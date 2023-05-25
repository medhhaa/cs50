#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int alpha(string argument);
int unique(string argument);
string cipher(string plain, string key);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if( (strlen(argv[1]) != 26) || alpha(argv[1]) == 0)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: %s", cipher(plaintext, argv[1]));
    printf("\n");
}

string cipher(string plain, string key)
{
    int length = strlen(plain), index;
    string cipher = "";
    for( int i = 0; i < length; i++)
    {
        index = plain[i];
        if(isalpha(plain[i]))
        {
            cipher[i] = key[index];
        }
        else
        {
            cipher[i] = plain[i];
        }
        printf("i: %i, index %i", i, index);
    }
    return cipher;
}


int alpha(string argument)
{
    int l = strlen(argument), alp = 1;
    for (int i = 0; i < l; i++)
    {
        int index  = argument[i] - 65;
        if(isalpha(argument[i] == false))
        {
            alp = 0;
        }
    }
    return alp;
}

int unique(string argument)
{
    int l = strlen(argument), alphabets[26], unique = 0;
    for (int i = 0; i < 26; i++)
    {
            //new array of alphabets initialized to 1 to check for uniqueness
            alphabets[i] = 1;
            argument[i] = toupper(argument[i]);
    }
    for (int i = 0; i < l; i++)
    {
        int index  = argument[i] - 65;
        alphabets[index] -= 1;
    }
    int sum = 0;
    for (int i = 0; i < l; i++)
    {
        sum += alphabets[i];
    }
    // printf("%i\n",sum);
    if(sum == 0)
    {
        unique = 1;
    }
    return unique;

}