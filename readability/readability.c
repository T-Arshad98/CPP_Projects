#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    int grade_index = 0;
    int num_letters = 0;
    int num_words = 0;
    int num_sentences = 0;
    float L = 0.0;
    float S = 0.0;
    string text;

    //Get text input from user
    text = get_string("Text: ");
    if (isalpha(text[0]))
    {
        num_words++;
    }

    //Loop through every character in the text input
    for (int i = 0; i < strlen(text); i++)
    {
        //If character is a space, increase number of words
        if (text[i] == ' ')
        {
            num_words++;
        }

        //If character is an alphanumeric character, increase number of letters
        else if (isalpha(text[i]))
        {
            num_letters++;
        }

        //If character is a punctuation, increase number of sentences
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            num_sentences++;
        }
    }

    //Calculate the grade index
    L = ((float)num_letters / (float)num_words) * 100.0;
    S = ((float)num_sentences / (float)num_words) * 100.0;
    grade_index = round((0.0588 * L) - (0.296 * S) - 15.8);

    //If grade index is over 16
    if (grade_index >= 16)
    {
        printf("Grade 16+\n");
    }

    //If grade index is less than 1
    else if (grade_index < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", grade_index);
    }
}