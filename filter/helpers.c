#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Initialize variables to store original colours
    double originalRed = 0;
    double originalGreen = 0;
    double originalBlue = 0;

    //Loop through all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Store original colour of pixel
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            //Replace original colour with average of all elements to make it grey
            image[i][j].rgbtRed = nearbyint((originalRed + originalGreen + originalBlue) / 3);
            image[i][j].rgbtGreen = nearbyint((originalRed + originalGreen + originalBlue) / 3);
            image[i][j].rgbtBlue = nearbyint((originalRed + originalGreen + originalBlue) / 3);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Initialize original and new colour variables
    double originalRed = 0;
    double originalGreen = 0;
    double originalBlue = 0;

    int newRed = 0;
    int newGreen = 0;
    int newBlue = 0;

    //Loop through all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Store original colours
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            //Find and store new sepia colour by using the formula provided
            newRed = nearbyint((.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue));
            newGreen = nearbyint((.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue));
            newBlue = nearbyint((.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue));

            //If sepia colour is greater than 255 due to the formula, set it to 255 as maximum
            if (newRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            //Otherwise, set it to value found from formula
            else
            {
                image[i][j].rgbtRed = newRed;
            }

            if (newGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = newGreen;
            }

            if (newBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = newBlue;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Store original colours in arrays
    int originalRed[height][width];
    int originalGreen[height][width];
    int originalBlue[height][width];

    //Loop through all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Store original colours into original colour arrays
            originalRed[i][j] = image[i][j].rgbtRed;
            originalGreen[i][j] = image[i][j].rgbtGreen;
            originalBlue[i][j] = image[i][j].rgbtBlue;
        }
    }

    //Loop through all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Starting from the end of the row, replace all colours with the colours from the beginning of the row
            image[i][width - 1 - j].rgbtRed = originalRed[i][j];
            image[i][width - 1 - j].rgbtGreen = originalGreen[i][j];
            image[i][width - 1 - j].rgbtBlue = originalBlue[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Store original colours into arrays
    float replaceRed[height][width];
    float replaceGreen[height][width];
    float replaceBlue[height][width];

    //Loop through all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //If pixel is in the first row
            if (i == 0)
            {
                //If pixel is in the first column
                if (j == 0)
                {
                    replaceRed[i][j] = ((((float)image[i][j].rgbtRed + (float)image[i][j + 1].rgbtRed +
                                          (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j + 1].rgbtRed) / 4));
                    replaceGreen[i][j] = ((((float)image[i][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen +
                                            (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen) / 4));
                    replaceBlue[i][j] = ((((float)image[i][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue +
                                           (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue) / 4));
                }

                //If pixel is in the last column
                else if (j == (width - 1))
                {
                    replaceRed[i][j] = ((((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed +
                                          (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j - 1].rgbtRed) / 4));
                    replaceGreen[i][j] = ((((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen +
                                            (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen) / 4));
                    replaceBlue[i][j] = ((((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue +
                                           (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue) / 4));
                }

                //If pixel is between the first and last column
                else
                {
                    replaceRed[i][j] = ((((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i][j + 1].rgbtRed +
                                          (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j - 1].rgbtRed + (float)image[i + 1][j + 1].rgbtRed) / 6));
                    replaceGreen[i][j] = ((((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i][j + 1].rgbtGreen +
                                            (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen) / 6));
                    replaceBlue[i][j] = ((((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i][j + 1].rgbtBlue +
                                           (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue) / 6));
                }
            }

            //If pixel is in the last row
            else if (i == (height - 1))
            {
                //If pixel is in the first column
                if (j == 0)
                {
                    replaceRed[i][j] = ((((float)image[i][j].rgbtRed + (float)image[i][j + 1].rgbtRed +
                                          (float)image[i - 1][j].rgbtRed + (float)image[i - 1][j + 1].rgbtRed) / 4));
                    replaceGreen[i][j] = ((((float)image[i][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen +
                                            (float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen) / 4));
                    replaceBlue[i][j] = ((((float)image[i][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue +
                                           (float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue) / 4));
                }

                //If pixel is in the last column
                else if (j == (width - 1))
                {
                    replaceRed[i][j] = ((((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed +
                                          (float)image[i - 1][j].rgbtRed + (float)image[i - 1][j - 1].rgbtRed) / 4));
                    replaceGreen[i][j] = ((((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen +
                                            (float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen) / 4));
                    replaceBlue[i][j] = ((((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue +
                                           (float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue) / 4));
                }

                //If pixel is between the first and last column
                else if ((j > 0) && (j < (width - 1)))
                {
                    replaceRed[i][j] = ((((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i][j + 1].rgbtRed +
                                          (float)image[i - 1][j].rgbtRed + (float)image[i - 1][j - 1].rgbtRed + (float)image[i - 1][j + 1].rgbtRed) / 6));
                    replaceGreen[i][j] = ((((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i][j + 1].rgbtGreen +
                                            (float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen) / 6));
                    replaceBlue[i][j] = ((((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i][j + 1].rgbtBlue +
                                           (float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue) / 6));
                }
            }

            //If pixel is between the first and last rows
            else
            {
                //If pixel is in the first column
                if (j == 0)
                {
                    replaceRed[i][j] = ((((float)image[i][j].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i - 1][j].rgbtRed +
                                          (float)image[i - 1][j + 1].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j + 1].rgbtRed) / 6));
                    replaceGreen[i][j] = ((((float)image[i][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen +
                                            (float)image[i - 1][j + 1].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen) / 6));
                    replaceBlue[i][j] = ((((float)image[i][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue +
                                           (float)image[i - 1][j + 1].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue) / 6));
                }

                //If pixel is in the last column
                else if (j == (width - 1))
                {
                    replaceRed[i][j] = ((((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i - 1][j].rgbtRed +
                                          (float)image[i - 1][j - 1].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j - 1].rgbtRed) / 6));
                    replaceGreen[i][j] = ((((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen +
                                            (float)image[i - 1][j - 1].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen) / 6));
                    replaceBlue[i][j] = ((((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue +
                                           (float)image[i - 1][j - 1].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue) / 6));
                }

                //If pixel is between the first and last column
                else
                {
                    replaceRed[i][j] = ((((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i][j + 1].rgbtRed +
                                          (float)image[i - 1][j].rgbtRed + (float)image[i - 1][j - 1].rgbtRed + (float)image[i - 1][j + 1].rgbtRed +
                                          (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j - 1].rgbtRed + (float)image[i + 1][j + 1].rgbtRed) / 9));
                    replaceGreen[i][j] = ((((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i][j + 1].rgbtGreen +
                                            (float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen +
                                            (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen) / 9));
                    replaceBlue[i][j] = ((((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i][j + 1].rgbtBlue +
                                           (float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue +
                                           (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue) / 9));
                }
            }
        }
    }

    //Loop through all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Replace pixel colours with blurred colours found from above
            image[i][j].rgbtRed =  round(replaceRed[i][j]);
            image[i][j].rgbtGreen = round(replaceGreen[i][j]);
            image[i][j].rgbtBlue = round(replaceBlue[i][j]);
        }
    }
    return;
}
