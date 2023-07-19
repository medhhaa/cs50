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

    # print(letters, words, sentences)

    #index = 0.0588 * L - 0.296 * S - 15.8
    L = (letters //  words) * 100
    S = (sentences //  words) * 100

    g = 0.0588 * L - 0.296 * S - 15.8
    grade = round(g)

    # print(L, S, g, grade)

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

def count_words(text):
    # words = 1
    words = text.split()
    return len(words)

def count_sentences(text):
    sentences = 0
    for let in text.upper():
        if (let == '.' or let == '?' or let == '!'):
            sentences += 1
    return sentences

main()