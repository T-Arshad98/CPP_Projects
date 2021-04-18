#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int number_accepted = 0;
    long number_get = 0;
    long number_check = 0;
    long type_check = 0;
    long number = 0;
    int LSB = 0;
    int odd_sum = 0;
    int even_sum = 0;
    int total = 0;
    string card_type;

    //Loop until a valid entry (numbers only) is received
    while (number_accepted == 0)
    {
        number_get = get_long("Number: ");
        number_check = number_get;

        //Condense input to check for type of card
        for (int i = 0; i < 12; i++)
        {
            number_check = number_check / 10.0;
        }

        //if condensed input between 1 and 10, it is VISA (length 13)
        if ((number_check >= 1) && (number_check <= 10))
        {
            card_type = "VISA";
            number_accepted = 1;
        }

        //if condensed input between 100 and 1000, it is AMEX (length 15)
        else if ((number_check > 100) && (number_check <= 1000))
        {
            card_type = "AMEX";
            number_accepted = 1;
        }

        //if condensed input between 1000 and 10000, it is either MASTERCARD or VISA (length 16)
        else if ((number_check > 1000) && (number_check <= 10000))
        {
            card_type = "MASTERVISA";
            number_accepted = 1;
        }

        //Invalid card number if not between any of these lengths (not 13, 15, or 16 digits long)
        else
        {
            card_type = "INVALID";
            number_accepted = 1;
        }
    }

    //If input is VISA type, determine if valid number or not
    if (strcmp(card_type, "VISA") == 0)
    {
        //Find sum of alternating digits without multiplying by 2
        number = number_get;
        for (int i = 0; i < 13; i++)
        {
            LSB = number % 10;
            if ((i % 2) == 0)
            {
                odd_sum = odd_sum + (LSB);
            }
            number = number / 10;
        }

        //Find sum of alternating digits with multiplying by 2
        number = number_get;
        for (int i = 0; i < 13; i++)
        {
            number = number / 10;
            LSB = number % 10;
            if ((i % 2) == 0)
            {
                //If multiplied number is greater than 10, split the digits and add them together to the sum
                if ((LSB) * 2 >= 10)
                {
                    even_sum = even_sum + ((LSB * 2) / 10) + ((LSB * 2) % 10);
                }

                else
                {
                    even_sum = even_sum + (LSB * 2);
                }
            }
        }

        total = odd_sum + even_sum;
        if ((total % 10) == 0)
        {
            type_check = number_get;
            for (int i = 0; i < 12; i++)
            {
                type_check = type_check / 10.0;
            }

            //If card begins with 4, it is a VISA
            if (type_check == 4)
            {
                card_type = "VISA";
            }

            //If card does not begin with 4, it is invalid
            else
            {
                card_type = "INVALID";
            }
        }

        else
        {
            card_type = "INVALID";
        }
    }

    //If input is AMEX type, determine if valid number or not
    else if (strcmp(card_type, "AMEX") == 0)
    {
        //Find sum of alternating digits without multiplying by 2
        number = number_get;
        for (int i = 0; i < 15; i++)
        {
            LSB = number % 10;
            if ((i % 2) == 0)
            {
                odd_sum = odd_sum + (LSB);
            }
            number = number / 10;

        }

        //Find sum of alternating digits with multiplying by 2
        number = number_get;
        for (int i = 0; i < 15; i++)
        {
            number = number / 10;
            LSB = number % 10;
            if ((i % 2) == 0)
            {
                //If multiplied number is greater than 10, split the digits and add them together to the sum
                if ((LSB * 2) >= 10)
                {
                    even_sum = even_sum + ((LSB * 2) / 10) + ((LSB * 2) % 10);
                }

                else
                {
                    even_sum = even_sum + (LSB * 2);
                }
            }
        }

        total = odd_sum + even_sum;
        if ((total % 10) == 0)
        {
            type_check = number_get;
            for (int i = 0; i < 13; i++)
            {
                type_check = type_check / 10.0;
            }

            //If card begins with 34 or 37, it is an AMEX
            if (type_check == 34 || type_check == 37)
            {
                card_type = "AMEX";
            }

            //If card does not begin with 34 or 37, it is invalid
            else
            {
                card_type = "INVALID";
            }
        }

        else
        {
            card_type = "INVALID";
        }
    }

    //If input is of length 16, determine if valid number or not and whether it is MASTERCARD or VISA
    else if (strcmp(card_type, "MASTERVISA") == 0)
    {
        //Find sum of alternating digits with multiplying by 2
        number = number_get;
        for (int i = 0; i < 16; i++)
        {
            number = number / 10;
            LSB = number % 10;
            if ((i % 2) == 0)
            {
                //If multiplied number is greater than 10, split the digits and add them together to the sum
                if ((LSB * 2) >= 10)
                {
                    odd_sum = odd_sum + ((LSB * 2) / 10) + ((LSB * 2) % 10);
                }

                else
                {
                    odd_sum = odd_sum + (LSB * 2);
                }
            }

        }

        //Find sum of alternating digits without multiplying by 2
        number = number_get;
        for (int i = 0; i < 16; i++)
        {
            LSB = number % 10;
            if ((i % 2) == 0)
            {
                even_sum = even_sum + (LSB);
            }
            number = number / 10;

        }
        total = odd_sum + even_sum;

        //If last digit of total of the sums of alternating digits equals 0, it is a valid card
        if ((total % 10) == 0)
        {
            type_check = number_get;
            for (int i = 0; i < 14; i++)
            {
                type_check = type_check / 10;
            }

            //If card begins with 51, 52, 53, 54, or 55, it is a MASTERCARD
            if (type_check == 51 || type_check == 52 || type_check == 53 || type_check == 54 || type_check == 55)
            {
                card_type = "MASTERCARD";
            }

            //If card begins with 4, it is a VISA
            else if ((type_check / 10) == 4)
            {
                card_type = "VISA";
            }

            //If card does not begin with 4, 51, 52, 53, 54, or 55, it is invalid
            else
            {
                card_type = "INVALID";
            }
        }

        //If last digit of total of the sums of alternating digits does not equal 0, it is an invalid card
        else
        {
            card_type = "INVALID";
        }

    }
    //Output final card type
    printf("%s\n", card_type);

}