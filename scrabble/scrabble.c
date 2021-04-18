#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    //Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    //Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //If player 1 has a higher score, they win
    if (score1 > score2)
    {
        printf("player 1 wins!\n");
    }

    //If player 2 has a higher score, they win
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }

    //If player 1 and player 2 have equal scores, it is a tie
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

//Function to compute score of the words
int compute_score(string word)
{
    //Initialize local variable score to 0
    int score = 0;

    //Iterate through every character in the word to find score
    for (int i = 0; i < strlen(word); i++)
    {
        //If uppercase character, use ASCII table to shift relative to 'A' character position to 0 based on POINTS array
        //Increase score by value determined from POINTS array
        if (isupper(word[i]))
        {
            score = score + POINTS[word[i] - 'A'];
        }

        //If lowercase character, use ASCII table to shift relative to 'a' character position to 0 based on POINTS array
        //Increase score by value determined from POINTS array
        else if (islower(word[i]))
        {
            score = score + POINTS[word[i] - 'a'];
        }
    }

    //Return the score from this function
    return score;
}