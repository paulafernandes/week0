// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "dictionary.h"

// initiates struct root
node *root = NULL;

// initiates count of words in true
unsigned int countWordsTrie = 0;

// initiates struct currentnode for insert word in trie, recursively
node* pCurrentNode = NULL;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
	node *cursor = root;
	int index = 0;

	// check if word or root are empty
	if (!word || cursor == NULL)
	{
		printf("Error on check function\n");
		return false;
	}

	// goes through all chars of the word until it hits null or if it is a word
	int wordLength = strlen(word);
	for (int i = 0; i < wordLength; i++)
	{
		if (word[i] == '\'')
			index = (ALPHA_SIZE - 1);
		else
			index = tolower(word[i]) - 'a';

		if (cursor->children[index] == NULL)
			return false;

		cursor = cursor->children[index];
	}

	return (cursor != NULL && cursor->isWord);
}

// function to insert the chars of a word in to trie
bool insertIntoTrie(node *cursor, char *words)
{
	int wordLength = strlen(words) - 1;
	int nodeIndex;
	pCurrentNode = cursor;

	// goes through all chars of the word
	for (int i = 0; i < wordLength; i++)
	{
		if (words[i] == '\'')
			nodeIndex = (ALPHA_SIZE - 1);  // if it is char ' then stores it in the last index of trie
		else
			nodeIndex = tolower(words[i]) - 'a'; // converts char into int

		if (nodeIndex >= 0 && nodeIndex <= ALPHA_SIZE)
		{
			if (pCurrentNode->children[nodeIndex] == NULL)
			{
				pCurrentNode->children[nodeIndex] = calloc(1, sizeof(node));  // if node still not created, allocate memory for it
			}

			pCurrentNode = pCurrentNode->children[nodeIndex];
		}
	}
	pCurrentNode->isWord = true; // set field to true

    return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
	int errnum = 0;
	// open dictionary
	FILE *fDict = fopen(dictionary, "r");

	// error case
	if (fDict == NULL)
	{
		errnum = errno;
		fprintf(stderr, "Value of errno: %d, Error opening file: %s\n", errno, strerror(errnum));
		return false;
	}

	//// init of root
	if (root == NULL)
		root = calloc(1, sizeof(node));

	//// buffer for storing word
	char words[LENGTH];

	// loads words of dictionary into struct
	while (fgets(words, LENGTH, fDict))
	{
		if (!insertIntoTrie(root, words))
			return false;
		else
			countWordsTrie++;
	}
	fclose(fDict);
	return (root != NULL);
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
	// -1 to remove last line
	return (countWordsTrie);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
   	if (root != NULL)  // free allocated memory for struct root
	{
		node *cursor = root;
		freeNode(cursor);
		return true;
	}
	else
		return false;

	if (pCurrentNode != NULL)   // free allocated memory for struct currentnode
	{
		node *current = pCurrentNode;
		freeNode(current);
		return false;
	}


	return (root == NULL);
}

// recursive function to free all the nodes in the structure
void freeNode(node *cursor)
{
	for (int i = 0; i < ALPHA_SIZE; i++)
	{
		if (cursor->children[i] != NULL)
		{
			freeNode(cursor->children[i]);
		}
	}

	// free root
	free(cursor);
}