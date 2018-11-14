#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void){

    float fltChange;
    bool isValid = false;

	do
	{
		fltChange = get_float("Change: ");
		if (fltChange > 0 )
        {
			isValid = true;
		}
	}
	while (!isValid);

    if (isValid)
    {
        int intCoins = 0;
        int intDimes = 0;
        int intNickel = 0;
        int intPennie = 0;

		int iRemainerChange = 0;
        int intCents = round(fltChange * 100);

		//Calculate Number of Quarters
        int intQuarter = (intCents / 25);

		//Calculate Number of Dimes
		iRemainerChange = intCents - (intQuarter * 25);
        if(intCents % 25 != 0){
			intDimes = (iRemainerChange / 10);
		}

		//Calculate Number of Nickel
		iRemainerChange = iRemainerChange - (intDimes * 10);
		if(iRemainerChange % 10 != 0)
		{
			intNickel =  (iRemainerChange / 5);
		}

		//Calculate Number of Pennies
		intPennie =  iRemainerChange - (intNickel * 5);

		//Calculate and show result
		intCoins = intQuarter + intDimes + intNickel + intPennie;
		printf("%i\n", intCoins);
	}
}