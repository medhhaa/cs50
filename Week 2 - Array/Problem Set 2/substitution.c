#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validation(int argc, string argv[]);
int alpha(string argument);
int unique(string argument);
void cipher(string plain, string key);

int main(int argc, string argv[])
{
    //validation
    if (validation(argc, argv) == 1)
    {
        return 1;
    }
    //ask user for plain text
    string plaintext = get_string("plaintext: ");
    //get ciphertext
    printf("ciphertext: ");
    cipher(plaintext, argv[1]);
    printf("\n");
}

int validation(int argc, string argv[])
{
    //validating by calling functions
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if ((strlen(argv[1]) != 26))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (alpha(argv[1]) == 0)
    {
        printf("Key must contain alphabets only.\n");
        return 1;
    }
    else if (unique(argv[1]) == 0)
    {
        printf("Values should be unique.\n");
        return 1;
    }
    return 0;
}

void cipher(string plain, string key)
{
    int length = strlen(plain), index;
    char cipher[length], ch, k;
    for (int i = 0; i < length; i++)
    {
        ch = toupper(plain[i]);
        index = ch - 65;

        //retain upper and lower case
        if ((int) plain[i] > 96)
        {
            k = tolower(key[index]);
        }
        else
        {
            k = key[index];
        }

        //append in cipher char array
        if (isalpha(plain[i]))
        {
            cipher[i] = k;
        }
        else
        {
            cipher[i] = plain[i];
        }
        printf("%c", cipher[i]);
    }
    printf("\n");
}


int alpha(string argument)
{
    int l = strlen(argument), alp = 1;
    //individually check each element is alphabet or not
    for (int i = 0; i < l; i++)
    {
        int index  = argument[i] - 65;
        if (isalpha(argument[i]) == false)
        {
            alp = 0;
        }
    }
    return alp;
}

int unique(string argument)
{
    int l = strlen(argument), alphabets[26], index;
    for (int i = 0; i < 26; i++)
    {
        //new array of alphabets initialized to 1 to check for uniqueness
        alphabets[i] = 1;
        argument[i] = toupper(argument[i]);
    }
    //subtract every value to find distinctness
    for (int i = 0; i < l; i++)
    {
        index  = argument[i] - 65;
        alphabets[index] -= 1;
    }
    //if not 0, means char is repeated or not occured yet, hence not unique.
    for (int i = 0; i < l; i++)
    {
        if (alphabets[i] != 0)
        {
            return 0;
        }
    }
    return 1;

}