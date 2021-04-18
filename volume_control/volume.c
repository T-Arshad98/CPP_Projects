// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //Define header as 8 bits and set size to 44 bytes
    uint8_t header[HEADER_SIZE];

    //From the input, read size of uint8_t for the size of the header (44 bytes)
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);

    //To the output, write size of uint8_t for the size of the header (44 bytes)
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    //Create a buffer 16 bits long
    int16_t buffer;

    //While there is data available to be read from the input, 16 bits long, read 16 bits at a time and store to buffer
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        //Resize the data in the buffer by the value of the factor
        buffer *= factor;

        //To the output, write the resized buffer data 16 bits at a time
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
