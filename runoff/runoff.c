#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
    //Initialize boolean variable to determine if vote is valid or not
    bool invalid_vote = false;

    //Loop through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //If voted name matches with a name in the list of candidates
        if (strcmp(name, candidates[i].name) == 0)
        {
            //Set preference in order of ranked names
            preferences[voter][rank] = i;

            //Declare the voted name was valid
            invalid_vote = true;
        }

    }
    //Return whether vote is valid or not
    return invalid_vote;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    bool vote_found = false;
    int top_vote = 0;

    //Loop through all candidates
    for (int i = 0; i <  voter_count; i++)
    {
        vote_found = false;
        top_vote = 0;

        //Loop until vote_found is true
        while (vote_found != true)
        {
            //If the candidate at the top of the preference list is not eliminated, continue
            if (candidates[preferences[i][top_vote]].eliminated != true)
            {
                //Increase the votes for the current candidate by 1
                candidates[preferences[i][top_vote]].votes++;
                vote_found = true;
            }

            //If candidate is eliminated, move onto next candidate preference and check again
            else
            {
                top_vote++;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    bool won = false;

    //Loop through number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //If the current candidate vote is greater than the previous, set new max to current votes
        if (candidates[i].votes > (voter_count / 2))
        {
            //Print the name of the winner and declare there was a winner
            printf("%s\n", candidates[i].name);
            won = true;
            break;
        }
    }

    //return true if there is a winner, false if not
    return won;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //Initialize first min as the number of votes for first candidate
    int min = candidates[0].votes;

    //Loop through number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //If candidate has not been eliminated
        if (candidates[i].eliminated != true)
        {
            //If candidate has least votes
            if (candidates[i].votes < min)
            {
                //Set new min if the new min is lower
                min = candidates[i].votes;
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    bool tied = true;

    //Loop through number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //If candidate has not been eliminated
        if (candidates[i].eliminated != true)
        {
            //If any candidate has votes greater than the min, it means there is no tie
            if (min != candidates[i].votes)
            {
                tied = false;
            }
        }

    }

    return tied;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //Loop through number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //If votes for current candidate are min, eliminate them
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
