// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
	}

    // remember filenames and the resize value
    char *cResize = argv[1];
    int iResize = *cResize - '0';
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
	}

    // open output file
    FILE *outptr = fopen(outfile, "w");
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
    int iNewWidth  = bi.biWidth * iResize;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int iFinalPad = (4 - (iNewWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //***********************************
    //Create new BITMAPINFOHEADER object with the updated values
    BITMAPINFOHEADER bio;
    bio.biSize = bi.biSize;
    bio.biWidth = iNewWidth;
    bio.biHeight = bi.biHeight * iResize;
    bio.biPlanes = bi.biPlanes;
    bio.biBitCount = bi.biBitCount;
    bio.biCompression = bi.biCompression;
    bio.biSizeImage = ((sizeof(RGBTRIPLE) * bio.biWidth) + iFinalPad) * abs(bio.biHeight);
    bio.biXPelsPerMeter = bi.biXPelsPerMeter;
    bio.biYPelsPerMeter = bi.biYPelsPerMeter;
    bio.biClrUsed = bi.biClrUsed;
    bio.biClrImportant = bi.biClrImportant;

    //Create new BITMAPFILEHEADER object with the updated values
    BITMAPFILEHEADER bfo;
    bfo.bfType = bf.bfType;
    bfo.bfSize = bio.biSizeImage + bf.bfOffBits;
    bfo.bfReserved1 = bf.bfReserved1;
    bfo.bfReserved2 = bf.bfReserved2;
    bfo.bfOffBits = bf.bfOffBits;
    //***********************************

    // write outfile's updated BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's updated BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

    //***********************************
    //Creates new char array to store new scanline
    RGBTRIPLE *cNewLine = malloc(bio.biWidth * sizeof(RGBTRIPLE));
    int iSizeLine = 0;
    //***********************************

    if (!cNewLine)
	    return 1;
    else
    {
		// iterate over infile's scanlines
		for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
		{
			// iterate over pixels in scanline
			for (int j = 0; j < bi.biWidth; j++)
			{
				// temporary storage
				RGBTRIPLE triple;

				// read RGB triple from infile
				fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

				for(int x = 0; x < iResize; x++)
				{
					cNewLine[iSizeLine] = triple;
					iSizeLine++;
				}
			}

			for (int f = 0; f < iResize; f++)
			{
				for (int z = 0, m = iSizeLine; z < m; z++)
				{
					// write RGB triple to outfile
					fwrite(&cNewLine[z], sizeof(RGBTRIPLE), 1, outptr);
				}
				for (int k = 0; k < iFinalPad; k++)
				{
					fputc(0x00, outptr);
				}
			}

			iSizeLine = 0;
			// skip over padding, if any
			fseek(inptr, padding, SEEK_CUR);
		}
		return 0;
	}
    // close cResize
    free(cNewLine);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
