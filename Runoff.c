#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j].name) == 0)
        {
            preferences[voter][rank] = j;                       // We can think of "j" as the number of the current candidate, Ex, Say we have candidates Sam, Max, we could say Sam is number j = 0
            return true;                                        // and Max is j = 1
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int candidate_number;
    for (int i = 0; i < voter_count; i++)                         // In the tabulate function, int i is the # of voters and int j is the rank each voter has for the different candidates
    {
        for (int j = 0; j < candidate_count; j++)                 // The number of ranked candidates for each voter is the same as the candidate count in the election
        {
            candidate_number = preferences[i][j];

            if(candidates[candidate_number].eliminated == false)
            {
                candidates[candidate_number].votes ++;
                j = candidate_count;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int vote_limit; 
    vote_limit = ceil(((float)voter_count / 2));
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > vote_limit)             //Double check this function: Jan 11, 2021
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int v1[MAX_CANDIDATES];
    int remaining = 0;
    int switches = 1;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            v1[i] = candidates[i].votes;
            remaining ++;
        }
    }
    
    while (switches != 0)                                    //Double Check this function: Jan 12, 2021
    {
        switches = 0;
        
        for (int y = 0; y < remaining - 1; y++)
        {
            if (v1[y] < v1[y + 1])
            {
                int temp1;
                temp1 = v1[y + 1];
                v1[y + 1] = v1[y];
                v1[y] = temp1;
                switches++;
            }
        }
    }
    
    return v1[remaining - 1];
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int remaining_candidates = 0;
    int y = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            remaining_candidates++;
            if (candidates[i].votes == min)
            {
                y++;
            }
        }
    }
    
    if (remaining_candidates == y)
    {
        return true;
    }
    
    // Basically, cycle through all the candidate votes using for loop, inside for loop use an if statment to see if any of the candidate votes are equal to the 
    // min vote we got from the "find_min" function, if everysingle candidates vote is the same as the min that means we have a tie therefore return true, if not return 
    // false. In the if statement have an indicator that goes up 1 for everytime a candidate vote is equal to the min, if at the end the indicator is equal to the number of
    // candidates, that means all candidates have the same number of votes and there is a tie.
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
