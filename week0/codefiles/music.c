// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //Separate ints for delimiter /
    string sValue = strtok(fraction, "/");
    char sDuration[3];
    int i = 0;

    while(sValue != NULL ) {
        sDuration[i] = sValue[0];
        i++;
		sValue = strtok(NULL, "/");
	}
    sDuration[2] = '\0';

    //Calculate duration
    int iUp = sDuration[0]-'0';
    int iDown = sDuration[1]-'0';
    return ((iUp * 8) / iDown);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char cNote[2];
    int cOctave[2];
    char cAcc[2];
    int iFreq = 0;
    int semi_tone = 0;
    const int iFreqA4 = 440;
    //https://www.cs.cmu.edu/~music/cmsip/readings/music-theory.htm
    //https://pages.mtu.edu/~suits/notefreqs.html - list
    //int major_scale[] ={0, 2, 4, 5, 7, 9, 11};
    //Aplying the indexes needed
    const int major_scale[] ={-9, -7, -5, -4, -2, 0, 2};
    const char *sNotes[8] = {"C", "D", "E", "F", "G", "A", "B", "\0"};
    bool bIsFound = false;

    //Separates note from accidental and octave
    if(strlen(note) > 2)
    {
        cNote[0] = note[0];
        cNote[1] = '\0';
        cAcc[0] = note[1];
        cAcc[1] = '\0';
        cOctave[0] = note[2] - '0';
        cOctave[1] =  '\0';
	}
    else
    {
        cNote[0] = note[0];
        cNote[1] = '\0';
        cOctave[0] = note[1] - '0';
        cOctave[1] =  '\0';
	}

    //Calculate the correct frequency for the semi tones
    int iFinalFreq = iFreqA4 * pow(2, (cOctave[0]-4));

    //Calculates the final frequency
	for (int i = 0, j = sizeof(sNotes); i < j && !bIsFound; i++)
	{
		if(strcmp(sNotes[i], cNote) == 0)
		{
			semi_tone = major_scale[i];
			if (cAcc[0] == '#')
			semi_tone++;
			else if (cAcc[0] == 'b')
			semi_tone--;
			iFreq = round(iFinalFreq * pow(2, (semi_tone/12.0))); //TODO Try round on pow alone
			bIsFound = true;
		}
	}

    return iFreq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //Checks if is empty line
    if (strcmp(s, "") == 0)
		return true;
    else
		return false;
}