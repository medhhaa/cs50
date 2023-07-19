# TODO
from cs50 import get_string

def main():
    text = get_string("Text: ")
    #count letters
    letters = count_letters(text) 

    #count words
    words = count_words(text) 

    #count sentences
    sentences = count_sentences(text) 

    #index = 0.0588 * L - 0.296 * S - 15.8
    L = (letters // () words) * 100 
    S = (sentences // () words) * 100 

    g = 0.0588 * L - 0.296 * S - 15.8 
    grade = round(g) 

    # print("%f %f %f %i", L, S, g, grade) 

    if (grade < 2):
        print("Before Grade 1\n") 
    elif (grade > 16):
        print("Grade 16+\n") 
    else:
        print("Grade ", grade) 

def count_letters(text):
    n = 0
    letter = 0 
    for let in text.upper(): #Because OOP, you can directly call fucntions 
        if (let >= 'A' and let <= 'Z'):
            letter += 1 
        n += 1
    return letter 

   count_words(string text)
{
       n = 0, words = 1 
    while (text[n] != '\0')
    {
        text[n] = toupper(text[n]) 
        if (text[n] == ' ')
        {
            words += 1 
        }
        n += 1 
    }
     # print("%i words\n", words) 
    return words 
}
   count_sentences(string text)
{
       n = 0, sentences = 0 
    while (text[n] != '\0')
    {
        text[n] = toupper(text[n]) 
        if (text[n] == '.' || text[n] == '?' || text[n] == '!')
        {
            sentences += 1 
        }
        n += 1 
    }
     # print("%i sentences\n", sentences) 
    return sentences 
}