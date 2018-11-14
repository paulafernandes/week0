#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//define the constant of 26 letters
#define NUMBER_OF_LETTERS 26

int main(int argc, string argv[])
{
    //case not just one argument, exit program
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
	}

    //retrieve the key
    int iKeyUser = atoi(argv[1]);
    //int iFinalKey = iKeyUser;

    //Checks if key is bigger than 26 and corrects the key
    if (iKeyUser > NUMBER_OF_LETTERS)
    {
        do
        {
            iKeyUser = iKeyUser - NUMBER_OF_LETTERS;
		}
        while (iKeyUser > NUMBER_OF_LETTERS);
	}

    //gets the users input

    string sPlainText = get_string("plaintext: ");
    printf("ciphertext: ");
    char cLetter;

    //Loop through string and add the key
    for (int i = 0, n = strlen(sPlainText); i < n; i++)
    {
        cLetter = sPlainText[i] + iKeyUser;

        //case special characters
        if (!isalpha(sPlainText[i]))
        {
            cLetter = sPlainText[i];
		}
        //case letters
        else if (!isalpha(cLetter))
		{
			cLetter = cLetter - NUMBER_OF_LETTERS;
		}
        //Presents the result
        printf("%c", cLetter);
	}
    printf("\n");
    return 0;
}