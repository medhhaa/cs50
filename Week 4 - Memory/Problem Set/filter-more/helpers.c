#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //take average of rgb values and turn the pixel to avg value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3;
            avg = round(avg);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
     //to run: ./filter -g images/courtyard.bmp images/courtblack.bmp
}

// Reflect image horizontally :- Swap a line horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int limit = round(width / 2);
    for (int i = 0; i < height; i++)
    {
        int p2 = width - 1;
        for (int p1 = 0; p1 < limit; j++)
        {
            //swap red
            int temp = image[i][p1].rgbtRed;
            image[i][p1].rgbtRed = image[i][p2].rgbtRed;
            image[i][p2].rgbtRed = temp;

            //swap blue
            temp = image[i][p1].rgbtBlue;
            image[i][p1].rgbtBlue = image[i][p2].rgbtBlue;
            image[i][p2].rgbtBlue = temp;

            //swap green
            temp = image[i][p1].rgbtGreen;
            image[i][p1].rgbtGreen = image[i][p2].rgbtGreen;
            image[i][p2].rgbtGreen = temp;

            p2--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
