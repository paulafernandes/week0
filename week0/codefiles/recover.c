#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
	}

    // remember filename
    char *cRawFile = argv[1];

    // open input file
    FILE *inptr = fopen(cRawFile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", cRawFile);
        return 2;
	}

 	int ijpgNumber = 0;
 	char cFilename[9] = { };
    FILE * img = NULL;

	unsigned char *cBufferjpg = (unsigned char *) malloc(512 * sizeof(unsigned char));
    if(!cBufferjpg)
    {
        return 5; //error 5 for jpg manipulation
	}
    else
    {
        //Reads the first 512 B from input file and controls EOF
        while(fread(cBufferjpg, BLOCK_SIZE, sizeof(unsigned char), inptr) == sizeof(unsigned char))  //reads one block 512 bytes long
        {
            //Checks if is beginning of .jpg
            if (cBufferjpg[0] == 0xff && cBufferjpg[1] == 0xd8 && cBufferjpg[2] == 0xff && (cBufferjpg[3] & 0xf0) == 0xe0)
            {
                //checks if a jpg was already found, and close if so
                if (ijpgNumber > 0)
                {
                    fclose(img);
                }

                //creates dynamically the filename
				snprintf(cFilename, sizeof(cFilename),"%03i.jpg", ijpgNumber);

				//open new file for writing
				img = fopen(cFilename, "w");

				//Writes the 512 bytes into a new .jpg file
				fwrite(cBufferjpg, sizeof(unsigned char), BLOCK_SIZE, img);
                ijpgNumber++;
            }
            else
            {
                //If a jpg was found, keeps writing the file until a new jpg is found
                if (ijpgNumber > 0)
                    fwrite(cBufferjpg, sizeof(unsigned char), BLOCK_SIZE, img);
            }
        }
	}

	free(cBufferjpg);

	fclose(inptr);

    return 0;
}