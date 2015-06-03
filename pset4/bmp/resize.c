/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP piece by piece by a factor
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remembor factor
    int factor = atoi(argv[1]);
    
    if (factor > 100 || factor < 1)
    {
        printf("Factor must be between 1 and 100\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding for scanlines
    int origpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newpadding =  (4 - (bi.biWidth * factor * sizeof(RGBTRIPLE)) % 4) % 4;

    // increase biWidth, biHeight, biSizeImage, and bfSize by factor
    bi.biWidth *= factor;
    bi.biHeight *= factor; 
    bi.biSizeImage = (bi.biWidth * abs(bi.biHeight) * sizeof(RGBTRIPLE)) 
                     + newpadding * abs(bi.biHeight); 
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage; 
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < (abs(bi.biHeight) / factor); i++)
    {
        // vertical multiplication
        for (int m = 0; m < factor; m++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < (bi.biWidth / factor); j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // horizontal multiplication write RGB triple to outfile
                for(int l = 0; l < factor; l++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
            }

            // add padding
            for (int k = 0; k < newpadding; k++)
                fputc(0x00, outptr);

            if (m == (factor - 1))
            {    
                // skip over padding, if any
                fseek(inptr, origpadding, SEEK_CUR);
            }
            else
                fseek(inptr, -(bi.biWidth / factor * sizeof(RGBTRIPLE)), SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
