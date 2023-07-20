import csv
import sys


def main():

    # TODO: Check for command-line usage
    if(len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        #exit code can be checked using the command echo $?
        #anything other than 0 is considered some kind of error, or not desired route/output
        sys.exit(1)    

    # TODO: Read database file into a variable
    db = open(sys.argv[1])
    
    #The difference between DictReader and just Reader is:
    #For a text file like -    Reader Output:       DictReader Output:
    #A  B  C                      A  B  C          {'A' : 1, 'B' : '2', 'C' : 3}
    #1  2  3                      1  2  3          {'A' : 4, 'B' : '5', 'C' : 6}
    #4  5  6                      4  5  6       DictReader automatically takes first lines as fields for keys!

    db_reader = csv.DictReader(db)

    # TODO: Read DNA sequence file into a variable
    dna = open(sys.argv[2])

    #storing sequence from text file into just a variable for easier access to pass as argument to longest_matching, as well as, files when opened, can be used only ONCE.
    sequence = ''
    for line in dna:
        sequence = line

    #create a dictionary to get all the fields that eventually needs to be compared with the sequences of people.
    subsequences = {}
    # TODO: Find longest match of each STR in DNA sequence

    db_length = 0
    for subsequence in db_reader:
        for key in subsequence:
            #skip if key is name as we only need STRs.
            if(key == 'name'):
                continue
            #initializing the dictionary with 0.
            subsequences[key] = 0
    # print(subsequences, len(subsequences))

    #Close the file readers for database and dna
    db.close()
    dna.close()

    #now, actually doing the required TODO which is finding counts of each STR in dna
    #longest_match( sequence , subsequence )  --> (ATAGTTTTATAG, ATAG) <- 2
    for key in subsequences:
        subsequences[key] = longest_match(sequence, key)
    # print(subsequences)


    # TODO: Check database for matching profiles

    #1. Open a new db (name could have been same but better to take diff for own clarity)
    db1 = open(sys.argv[1])
    db_reader1 = csv.DictReader(db1)

    #2. Get the desired name
    # - Logic here that I implemented was that, if for a person, say Luna, all 8 counts(large) of STRs match, then, DNA belongs to Luna
    # - Small has 4 and Large has 8, but we cant be sure so counting from len() from subsequences
    # - 
    name = ''
    desired_count = len(subsequences)
    
    #db_reader - as already illustrated above in DictReader has multiple dictionaries for each person, Luna, Ron, Harry etc...
    #so going one persons STRs at a time
    for dic in db_reader1:

        #set counter to 0 for each person, 
        # so that at the end you can check whether all 8 fields match, 
        # if not start again from _scratch_ -- 0 for a new person
        count = 0

        #traverse the list by keys
        for key in dic:

            # if name: skip, as subsequences dont have the name key in the first place.
            if(key == 'name'):
                continue
            #interestingly here, I was stuck for some time as the condition was giving false no matter what
            # 18 == 18 was giving False, then I started debugging by printing to realise it was
            # 18 == '18' and hence False, so I type casted it to int.
            # print(dic[key], subsequences[key], key, int(dic[key]) == subsequences[key])

            # What happens when they are same? Th eocunt is incrememnted as well as the name is noted.
            if(int(dic[key]) == subsequences[key]):
                count = count + 1
                name = dic['name']

        #if the count reaches the desired count (8) that means for a person all 8 fields MATCHED and hence print out result and EXIT
        if(count == desired_count):
            print(name)
            sys.exit(0)

    #however, if the exit(0) didnt get executed, that means we are stuck with a NO MATCH
    print('No Match')

    #Close the file reader for database. (large / small)
    db1.close()
    # db_reader1.close()      <--- You CANNOT close the DictReader or Reader only the open needs to be closed.

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


# 20 July 2023
# while I was coding I was just writing codes, 
# unsure whether even I understood what I actually wrote, just debugging and writing, 
# hence once I was positive it worked I took dedicated time to commenting and documenting everything going on 
# and happy to say I was able to understand my approach rather easily