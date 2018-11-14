#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int i = 0; //= get_int("Height: \n");
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
            int x;
            for (x = 0; x < blanknum; x++)
            {
                printf("%s", " ");
			}
            int y;
            printf("%s", "#");
            for (y = 0; y < hashnum; y++)
            {
                printf("%s", "#");
			}
            printf("\n");
		}
	}
}