#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//define the constant of 26 letters
#define NUMBER_OF_LETTERS 26

int getCharKeyUser(string iKeyUser, string arrABC, int indexKey)
{
	bool bCharFound = false;
	int outputStep;
	//Loops through the keyword given and compares with the ABC array, returns its index, wich be the step
	for (int j = indexKey, kz = strlen(iKeyUser); j < kz && !bCharFound; j++)
	{
		for (int x = 0, az = strlen(arrABC); x < az && !bCharFound; x++)
		{
			if (tolower(iKeyUser[j]) == arrABC[x])
			{
				bCharFound = true;
				outputStep = x;
			}
		}
	}
	return outputStep;
}

int main(int argc, string argv[])
{
    //case not just one argument, exit program
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
	}

    //retrieve the key
    string iKeyUser = argv[1];

    //Checks if string is all letters
    for (int i = 0, s = strlen(iKeyUser); i < s; i++)
    {
        if (!isalpha(iKeyUser[i]))
        {
			printf("Keyword must be composed only by only letters\n");
			return 1;
		}
	}

	//Creates array with abc
    char arrABC[NUMBER_OF_LETTERS + 1];
    int iAbc, n;

    for (iAbc = 0, n = NUMBER_OF_LETTERS; iAbc < n; iAbc++)
    {
        arrABC[iAbc] = 'a' + iAbc;
	}

    //terminate the array
    arrABC[iAbc]='\0';

	//gets the users input
	string sPlainText = get_string("plaintext: ");
	printf("ciphertext: ");

	int stepKey = 0;
    char cLetter;
	int indexKey = 0;

	//Loops through the plaintext given
	for (int i = 0, pz = strlen(sPlainText); i < pz; i++)
	{
		//maintain the index to the keyword given
		if (indexKey == strlen(iKeyUser))
		{
			indexKey = 0;
		}
		//Calls function to calculate the step to be added do plaintext
		stepKey = getCharKeyUser(iKeyUser, arrABC, indexKey);
		cLetter = sPlainText[i] + stepKey;
		indexKey++;

		//case special characters
        if (!isalpha(sPlainText[i]))
        {
            cLetter = sPlainText[i];
            indexKey--;
		}
        else if (!isalpha(cLetter) || (islower(sPlainText[i]) != islower(cLetter)))   //case letters out of bound
		{
			cLetter = cLetter - NUMBER_OF_LETTERS;
		}

		//Presents the result
		printf("%c", cLetter);
	}

	printf("\n");
	return 0;
}