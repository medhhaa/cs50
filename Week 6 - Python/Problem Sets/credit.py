#convert credit.C of week 1 to Py
# TODO
from cs50 import get_int

def main():
    #prompt for the input
    c = get_int("Number: ")

    #checksum using Luhn's Algorithm
    valid = checksum(c)
    # print(valid)

    if (valid == 0):
        print("INVALID\n")
    else:
        print_card(c)


def digit_count(c):
    count = 0
    while (c > 0):
        count += 1
        c //= 10
    return count

#American Express uses 15-digit numbers, numbers start with 34 or 37;
#MasterCard uses 16-digit, numbers start with 51, 52, 53, 54, or 55;
#and Visa uses 13- and 16-digit, and all Visa numbers start with 4;

def print_card(c):
    count = digit_count(c)
    if (count == 15):

        #American
        c //= 10000000000000
        if (c == 34 or c == 37):
            print("AMEX\n")
        else:
            print("INVALID\n")

    elif (count == 16):

        #Master OR Visa
        c //= 100000000000000;
        if (c == 51 or c == 52 or c == 53 or c == 54 or c == 55):
            print("MASTERCARD\n")
        else:
            c //= 10;
            if (c == 4):
                print("VISA\n")
            else:
                print("INVALID\n")

    elif (count == 13):
        #Visa
        c //= 1000000000000
        #print(c)
        if (c == 4):
            print("VISA\n")
        else:
            print("INVALID\n")
    else:
        print("INVALID\n")

def digit_sum(p): #calculate sum of number given as argument
    sum = 0
    while (p > 0):
        sum += (p % 10)
        p //= 10
    return sum

def checksum(c):
    # 1. store sum of digits from last in one variable
    # 2. store sum of second to the last digits ( every other digits ) multiplied by 2 in another
    # 3. add both of these and check modulo for 0

    sum_last = 0
    sum_alt = 0
    flag = 0
    while (c > 0):
        digit = c % 10
        c //= 10
        if (flag == 0):  #checking flag for last or second last
            sum_last += digit
            flag = 1
            # print(f"LAST : digit: {digit}, sum: {sum_last}")
        else:
            sum = digit_sum(digit * 2) #take sum of digits and not digit itself!
            sum_alt += sum
            flag = 0
            # print(f"ALT : digit: {digit}, sum: {sum}")
    add = sum_last + sum_alt
    # print(f"last {sum_last} alt  {sum_alt}  sum {add}")

    if (add % 10 == 0):
        return 1
    else:
        return 0

main()
