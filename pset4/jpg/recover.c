/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    // Open FAT file
    FILE* inptr = fopen("card.raw", "r");
    FILE* outptr = NULL;

    // Create memory buffer for continually scanning 512B JPEG blocks
    int blocksize = 512;
    char* buffer = malloc(blocksize);

    int titlenum = 0;

	// Read file while looking for JPEG signatures (0xff 0xd8 0xff 0xe0) or (0xff 0xd8 0xff 0xe1) in first 4B of each block
    do
    {
        if (&buffer == 0xff 0xd8 0xff 0xe0 || &buffer == 0xff 0xd8 0xff 0xe1)
	    {
            // If a file is not open
            if (outptr == NULL)
            {
                // Open new numbered file
                sprintf(titlenum, "%d.jpg", .3);
                outptr = fopen(title, "a");
            }
            // Else close file and open a new one
            else
            {
                fclose(outptr);
                titlenum++;
                sprintf(titlenum, "%d.jpg", .3);
                outptr = fopen(title, "a");
            }

            // Write whole JPEG blocks into new numbered files in format ### until new JPEG found
            do
            {
                fwrite(&buffer, blocksize, 1, outptr);
            } while (&buffer != 0xff 0xd8 0xff 0xe0 && &buffer != 0xff 0xd8 0xff 0xe1)
            
        }

    } while(fread(&buffer, blocksize, 1, inptr) == blocksize)

    // Writes last partial block
    fwrite(&buffer, blocksize, 1, outptr);

    // Close FAT files
    fclose(outptr):
    fclose(inptr);

    // Free memory
    free(buffer);

	// End without errors
	return 0;
}
