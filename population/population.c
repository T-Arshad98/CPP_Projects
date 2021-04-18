#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size = 0;
    int end_size = 0;
    int number_accepted = 0;
    int years = 0;
    int years_found = 0;
    int llamas = 0;

    //Ask user for start size until valid number is entered
    while (number_accepted == 0)
    {
        start_size = get_long("Start size: ");
        if (start_size >= 9)
        {
            number_accepted = 1;
        }
    }

    //Ask user for end size until valid number is entered
    number_accepted = 0;
    while (number_accepted == 0)
    {
        end_size = get_long("End size: ");
        if (end_size >= start_size)
        {
            number_accepted = 1;
        }
    }

    //Iterate for a certain amount of years until end number of llamas is greater than starting number of llamas
    llamas = start_size;
    while (years_found == 0)
    {
        llamas = llamas + (llamas / 3) - (llamas / 4);

        //If start and end size are the same, number of years is 0 and program ends
        if (start_size == end_size)
        {
            years_found = 1;
        }

        //If new number of llamas after an iteration is greater than 0, number of years increases by 1 and program ends
        else if (llamas >= end_size)
        {
            years = years + 1;
            years_found = 1;
        }
        //If new total number of llamas is still less than end size requirement, increase years passed by 1 and start again
        else
        {
            years = years + 1;
        }
    }

    //Print how many years it took to go from start size to end size of llamas
    printf("Years: %i\n", years);
}