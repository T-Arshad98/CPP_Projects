#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    int height_accepted = 0;
    while (height_accepted == 0)
    {
        height = get_int("Height: "); //Ask for height
        if ((height > 0) && (height <= 8)) //Check if height is accepted
        {
            height_accepted = 1;
        }
    }
    for (int i = 0; i < height; i++)
    {
        //Print spaces
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        //Print first hashes
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        //Print 2 spaces
        for (int l = 0; l < 2; l++)
        {
            printf(" ");
        }
        //Print second set of hashes
        for (int m = 0; m < i + 1; m++)
        {
            printf("#");
        }
        printf("\n");

    }
}