#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

//pair weight
int pair_weight(int i);

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO

    for (int i = 0; i < candidate_count; i++)
    {
        //name matches then update the ranks 0 - highest and n-1 - lowest
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO: update prefernce array for eg if a > b > c so 'a' will have a,a = 0, a,b = 1; a,c = 1
     for (int i = 0; i < candidate_count; i++)
     {
        for (int j = 0; j < candidate_count; j++)
        {
            // no of voters that prefer i over j
            if (ranks[i] > ranks[j])
            {
                preferences[i][j] += 1;
            }
        }
     }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if there is tie, then do not add the pair and skip (no cycle; no deadlock!)
            if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }
            //if i is preferred over j        ppl that want i over j > ppl that want j over i
            if (preferences[i][j] > preferences[j][i])
            {
                //add them and increase pair count
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }

            // for (int j = 0; j < pair_count; j++)
            // {
            //     // no of voters that prefer i over j
            //     // printf("c[i] = %s, winner = %s loser %s\n", candidates[j], candidates[pairs[j].winner], candidates[pairs[j].loser]);
            // }

}

int pair_weight(int i)
{
    int winner = pairs[i].winner;
    int loser = pairs[i].loser;
    return preferences[winner][loser];
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    int index;

    // // TODO
    // for(int i = 0 ; i < pair_count; i++)
    // {
    //     printf("\n i: %i winner: %i  loser: %i", i, pairs[i].winner, pairs[i].loser);
    // }
    // printf("\n");
    for (int i = 0; i < pair_count; i++)
    {
        int max = pair_weight(i);
        index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (max < pair_weight(j))
            {
                max = pair_weight(j);
                index = j;
                // printf("\n Index changed index: %i, pw i: %i < pw j: %i , c[i]: %s", index, pair_weight(i), pair_weight(j), candidates[j]);
            }
        }
        //swap
        pair temp = pairs[index];
        pairs[index] = pairs[i];
        pairs[i] = temp;
        // printf("\n Swap i: %i index: %i", i, index);
    }

    // for(int i = 0 ; i < pair_count; i++)
    // {
    //     printf("\n i: %i winner: %i  loser: %i", i, pairs[i].winner, pairs[i].loser);
    // }
    // printf("\n");
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // locked[i][j] means i is locked in over j
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        // if there is tie, then do not add the pair and skip (no cycle; no deadlock!)
        if (locked[pairs[i].loser][pairs[i].winner] == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    // //header
    //  for(int i = 0 ; i < candidate_count; i++)
    //  {
    //     printf("\t %s", candidates[i]);
    //  }
    // printf("\n");
    // //side
    //  for (int i = 0; i < candidate_count; i++)
    //  {
    //     printf("%s \t", candidates[i]);
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         // no of voters that prefer i over j
    //         printf(" %i \t", locked[i][j]);
    //     }
    //     printf("\n");
    //  }
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    bool no_arrows;
    for (int i = 0; i < candidate_count; i++)
    {
        no_arrows = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                no_arrows = false;
            }
        }
        if (no_arrows)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
}