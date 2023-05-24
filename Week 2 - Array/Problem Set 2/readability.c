#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    //count letters
    int letters = count_letters(text);

    //count words
    int words = count_words(text);

    //count sentences
    int sentences = count_sentences(text);

    //index = 0.0588 * L - 0.296 * S - 15.8
    float L = (letters / words) * 100.0;
    float S = (sentences / words) * 100.0;
    float g = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(g);
    if(grade<2)
    {
        printf("Before Grade 1\n");
    }
    else if(grade>16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade: %i\n", grade);
    }

}

int count_letters(string text)
{
    int n = 0, letter = 0;
    while(text[n] != '\0')
    {
        text[n] = toupper(text[n]);
        if(text[n] >= 'A' && text[n] <= 'Z')
        {
            letter++;
        }
        n++;
    }
    // printf("%i letters\n", letter);
    return letter;
}
int count_words(string text)
{
   int n = 0, words = 1;
    while(text[n] != '\0')
    {
        text[n] = toupper(text[n]);
        if(text[n] == ' ')
        {
            words++;
        }
        n++;
    }
    // printf("%i words\n", words);
    return words;
}
int count_sentences(string text)
{
    int n = 0, sentences = 0;
    while(text[n] != '\0')
    {
        text[n] = toupper(text[n]);
        if(text[n] == '.' || text[n] == '?' || text[n] == '!')
        {
            sentences++;
        }
        n++;
    }
    // printf("%i sentences\n", sentences);
    return sentences;
}