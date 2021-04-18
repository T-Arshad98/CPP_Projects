#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

//Define BYTE as uint8_t type
typedef uint8_t BYTE;

//Number of bytes stored in a block
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./volume image\n");
        return 1;
    }

    //Use fopen to open the input file to read the data from it
    //Return 1 if unable to open
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int file_num = 0;
    char file_name[10];
    bool found_jpg = false;
    //Create a buffer array of type BYTE (uint8_t) with size BLOCK_SIZE (512)
    BYTE buffer[BLOCK_SIZE];

    //Create a string for the first image file
    sprintf(file_name, "%03i.jpg", file_num);

    //Create an output file using fopen and the string created above
    FILE *output = fopen(file_name, "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    //Repeat while there is data available to read
    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, input))
    {
        //If the first 4 bytes of the buffer match the expected jpg values, continue
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            //If this is the first image found
            if (file_num == 0)
            {
                //Set found_jpg boolean to true to be able to read continuously from now on
                found_jpg = true;

                //Using fwrite, write the buffer variable to the output
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, output);

                //Increment the variable storing which image is currently being processed
                file_num++;
            }

            //If file is not first image found
            else if (file_num != 0)
            {
                //Close the last image file that was being processed
                fclose(output);

                //Create the new image name to the string file_name
                sprintf(file_name, "%03i.jpg", file_num);

                //Open a new image file using fopen and the new string file_name
                output = fopen(file_name, "w");
                if (output == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }

                //Using fwrite, write the buffer variable to the new output
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, output);
                file_num++;
            }

        }

        //If buffer does not start with jpg header but a jpg has been found, continue
        else if (found_jpg == true)
        {
            //Using fwrite, write the buffer to the last image file that was being processed
            fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, output);
        }
    }

    //Close the input file and the last output file
    fclose(output);
    fclose(input);
    return 0;
}
