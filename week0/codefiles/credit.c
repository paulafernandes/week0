#include <cs50.h>
#include <stdio.h>
#include <math.h>

int calculateLength(long long n){
	if( n < 0 )
    n = -n;

	if( n == 0 )
    return 1;
	else
    return (int)(log10(n) + 1);
}

int * getSingleNumber(int sizeNum, long long ccNumber){
	static int * newDigits;

	newDigits = (int*)malloc(sizeNum * sizeof(int));

	for (int i = sizeNum - 1; i >= 0; i--)
	{
		newDigits[i] = ccNumber % 10;
		ccNumber = ccNumber / 10;
	}
	return newDigits;
}

int getFirstDigits(long long ccNum)
{
    while(ccNum > 99){
	ccNum = ccNum / 10;}
    return ccNum;
}

int getFirstOneDigit(long long ccNum)
{
    while(ccNum > 9){
	ccNum = ccNum / 10;}
    return ccNum;
}

bool valCcNumber(int * newDigits, int sizeNum){
	bool isCC = false;
	int calcVal = 0;
	int calcTotal = 0;
	int calcSingleTotal = 0;
	int iTotalValid = 0;
	int n = 1;

	for(int i = sizeNum; i >= 0; i--){
		n++;
		if(n % 2 == 0)
		{
			calcSingleTotal = calcSingleTotal +	newDigits[i];
		}
		else {
			calcVal = newDigits[i] * 2;
			if (calcVal > 9)
		    {
		        calcVal = calcVal - 9;
			}
		    calcTotal = calcTotal + calcVal;
		}

	}
	iTotalValid = calcTotal + calcSingleTotal;

	if(iTotalValid % 10 == 0){
		isCC = true;

	}
	return isCC;

}

int main(void){
    long long lCardNum = 0;
    int longLength = 0;
	int * allDigits;
	bool isCcValid = false;
	int firstDigits = 0;
	int oneDigit = 0;

	lCardNum = get_long_long("Number: ");
	longLength = calculateLength(lCardNum);
	allDigits = getSingleNumber(longLength, lCardNum);
	oneDigit = getFirstOneDigit(lCardNum);

	isCcValid = valCcNumber(allDigits, longLength - 1);
	if(isCcValid)
	{
		firstDigits = getFirstDigits(lCardNum);
		if (longLength == 15 && (firstDigits == 34 || firstDigits == 37))
		{
			printf("AMEX\n");
		}
		else if(longLength == 16 && (firstDigits >= 51 && firstDigits <= 55)) {
			printf("MASTERCARD\n");
		}
		else if((longLength == 13 || longLength == 16) && oneDigit == 4)
		{
			printf("VISA\n");
		}
		else {
			printf("INVALID\n");
		}
	}
	else {
		printf("INVALID\n");
	}
}