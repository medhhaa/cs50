import csv
import sys


def main():

    # TODO: Check for command-line usage
    if(len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    db = open(sys.argv[1])
    db_reader = csv.DictReader(db)

    # TODO: Read DNA sequence file into a variable
    dna = open(sys.argv[2])

    sequence = ''
    for line in dna:
        sequence = line

    subsequences = {}
    # TODO: Find longest match of each STR in DNA sequence
    db_length = 0
    for subsequence in db_reader:
        for key in subsequence:
            if(key == 'name'):
                continue
            subsequences[key] = 0
    # print(subsequences, len(subsequences))

    #Close the file readers for database and dna
    db.close()
    db_reader.close()
    dna.close()


    for key in subsequences:
        subsequences[key] = longest_match(sequence, key)
    # print(subsequences)


    # TODO: Check database for matching profiles
    db1 = open(sys.argv[1])
    db_reader1 = csv.DictReader(db1)


    name = ''
    desired_count = len(subsequences)
    for dic in db_reader1:
        count = 0
        for key in dic:
            if(key == 'name'):
                continue
            # print(dic[key], subsequences[key], key, int(dic[key]) == subsequences[key])
            if(int(dic[key]) == subsequences[key]):
                count = count + 1
                name = dic['name']
        if(count == desired_count):
            print(name)
            sys.exit(0)

    print('No Match')

    #Close the file readers for database.
    db1.close()
    db_reader1.close()

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
