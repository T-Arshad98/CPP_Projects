#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, string argv[])
{
    bool valid_key = true;
    bool repeated_letters = false;
    bool not_alpha = false;
    string key;
    string plaintext;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    //Continue if there is one command line argument
    if (argc == 2)
    {

        //Store key from command line argument
        key = argv[1];
        //If the length of key is 26 letters
        if (strlen(key) == 26)
        {
            //Loop through all letter elements of the key
            for (int i = 0; i < strlen(key); i++)
            {
                //If any element of the key is not a letter, key is invalid
                if (!isalpha(key[i]))
                {
                    valid_key = false;
                    break;
                }

                //If there are any repeated letters in the key, key is invalid
                for (int j = 0; j < 26; j++)
                {
                    if ((j != i) && (tolower(key[j]) == tolower(key[i])))
                    {
                        repeated_letters = true;
                        break;
                    }
                }
            }

            //If key contains anything other than letters, say it is invalid and return 1
            if (valid_key == false)
            {
                printf("Key must only contain letters from the alphabet.\n");
                return 1;
            }

            //If key contains repeated letters, say there cannot be any repeated letters and return 1
            else if (repeated_letters == true)
            {
                printf("Key cannot contain repeated letters\n");
                return 1;
            }

            //Else if key is valid, continue
            else
            {
                //Ask user for a text to encrypt
                plaintext = get_string("plaintext: ");
                string text_input = plaintext;
                //Loop through all elements of the text
                for (int i = 0; i < strlen(plaintext); i++)
                {
                    //If character is an alphanumeric character, increase number of letters
                    if (isalpha(plaintext[i]))
                    {
                        //Loop through all elements of the key
                        for (int j = 0; j < strlen(key); j++)
                        {
                            //If the location of the element matches to the location of the alphabet, encrypt the letter
                            if (tolower(plaintext[i]) == alphabet[j])
                            {
                                //If text letter element is lowercase, swap with lowercase key element
                                if (islower(plaintext[i]))
                                {
                                    text_input[i] = tolower(key[j]);
                                    break;
                                }

                                //If text letter element is uppercase, swap with uppercase key element
                                else if (isupper(plaintext[i]))
                                {
                                    text_input[i] = toupper(key[j]);
                                    break;
                                }
                            }
                        }
                    }
                    //If text element is not a letter of the alphabet, directly use the element instead (such as space, punctuation etc.)
                    else if (!isalpha(plaintext[i]))
                    {
                        text_input[i] = plaintext[i];
                    }
                }
                //Print the encrypted text
                printf("ciphertext: %s\n", text_input);

            }

        }

        //If key does not contain 26 letters, print error and return 1
        else
        {
            printf("Key must contain 26 letters.\n");
            return 1;
        }
    }

    //If 0 or more than 1 command line arguments, print error and return 1
    else if (argc != 2)
    {
        printf("Error in number of arguments\n");
        return 1;
    }
}