#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    //In pref[i][j] = i -> voter id, j -> rank
    //it basically stores the index of candidate at specified rank(j)
    //pref[0][1] = 2  <- means that the voter[0] put candidate[2] at rank 1
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    int rank;
    for (int i = 0; i < voter_count; i++)
    {
        rank = 0;
        int j = 0;
        while (j < candidate_count)
        {
            if (!candidates[j].eliminated && preferences[i][rank] == j) //if candidate not eliminated and at top preference, add count
            {
                candidates[j].votes += 1;
                break;
            }
            if (candidates[j].eliminated && preferences[i][rank] == j)
            {
                rank++;   //if this candidate has been eliminated, incremenet and contn
                j = 0;
                continue;
            }
            j++;
        }
    }

    for (int j = 0; j < candidate_count; j++)
    {
        // candidates[j].eliminated

        printf("j: %i name: %s, votes = %i, eliminated? = %i\n", j, candidates[j].name, candidates[j].votes, candidates[j].eliminated);

    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    int half = (voter_count + 1) / 2;
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[j].votes > half) // odd/even - even rahega toh
            {
                printf("%s\n", candidates[j].name);
                return true;
            }
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min = candidates[0].votes;
    for (int j = 1; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false && candidates[j].votes < min)
        {
            min = candidates[j].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int count = 0, alive = 0;
    //check how many candidates are alive
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            alive++;
        }
    }
    //update no of candidates having minimum votes
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false && candidates[j].votes == min)
        {
            count++;
        }
    }
    //check if no of candidates having min == no of candidates alive -> TIE
    if (alive == count)
    {
        return true;
    }
    //else
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes <= min)
        {
            candidates[j].eliminated = true;
        }
    }
    return;
}