#include <cs50.h>
#include <stdio.h>

void FillString(int sizeStr, char * charStr){
	int x;

	for (x = 0; x < sizeStr; x++)
	{
		printf("%s", charStr);
	}
}

int main(void)
{
    int i = 0;
    bool isValid = false;
	do
	{
		i = get_int("Height: ");
		if (i >= 0 && i < 24 )
        {
			isValid = true;
		}
	}
	while (!isValid);

	if (isValid){
        int j;
        int hashnum;
        int blanknum;
        for (j = 0; j < i; j++) {
            hashnum = j + 1;
            blanknum = i - hashnum;

			FillString(blanknum, " ");
			FillString(hashnum, "#");
			printf("%s", "  ");
			FillString(hashnum, "#");
			printf("\n");
		}
	}
}