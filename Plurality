#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count; // Any variable outside the main function is a global variable

// Function prototypes, the functions are only initalized here so the main function knows they exist
// but the funtions are coded further down outside of the main function
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) // 
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes ++;
            return true;
        }
    }    
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    string c1[MAX]; // Copying the candidates names array
    int v1[MAX]; // Copying the candidates votes array
    int switches = 1;
    int z, y;
    int tie = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        c1[i] = candidates[i].name;
        v1[i] = candidates[i].votes;
    }
    
    // The code in the while loop is a bubble sorting algorithim that will sort the number of votes for each candidate from smallest (array index 0) to largest (array index n)
    
    while (switches != 0)
    {
        switches = 0;
        
        for (z = 0, y = 1; y < candidate_count; z++, y++)
        {
            if (v1[z] > v1[y])
            {
                v1[z] = candidates[y].votes;
                v1[y] = candidates[z].votes;
                c1[z] = candidates[y].name;
                c1[y] = candidates[z].name;
                                            // Once we swap the votes in lines 107 - 110, we need to make sure that the candidate structure array is updated so it is also the same
                candidates[z].votes = v1[z];// as the v1 and c1 arrays that is why we reintialize the candidate structure array in lines 112 - 113.
                candidates[y].votes = v1[y];
                candidates[z].name = c1[z];
                candidates[y].name = c1[y];
                switches++;
            }
        }
    }
    
    if (v1[candidate_count - 1] > v1[candidate_count - 2])
    {
        printf("%s\n", c1[candidate_count - 1]);
        return;
    }
    
    printf("%s\n", c1[candidate_count - 1]);
    
    for (z = candidate_count - 2, y = candidate_count - 1; z >= 0; z--)
    {
        if (v1[y] == v1[z])
        {
            printf("%s\n", c1[z]);
        }
    }
    return;
}
