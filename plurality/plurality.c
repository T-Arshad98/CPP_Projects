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
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
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
    //Initialize boolean variable to determine if vote is valid or not
    bool invalid_vote = true;
    //Loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //If current vote is in the list of candidates, increase their votes by 1
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            invalid_vote = true;
            break;
        }

        //If current vote is not in the list of candidates, the vote is invalid
        else if (strcmp(name, candidates[i].name) != 0)
        {
            invalid_vote = false;
        }
    }
    //Return whether vote is valid or not
    return invalid_vote;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Initialize max vote variable
    int max = 0;

    //Loop through number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //If the current candidate vote is greater than the previous, set new max to current votes
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
        }
    }

    //Loop thorugh number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //If current candidate votes is equal to the max, print out their name (works for tie votes)
        if (candidates[i].votes == max)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

