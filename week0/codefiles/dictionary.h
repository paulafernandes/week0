////// NOTES - Studied code
// www.geeksforgeeks.org/trie-display-content/
// www.geeksforgeeks.org/counting-number-words-trie/
// gist.github.com/cijogeorge/20b41a0dc7385fbc58c93d2e7837c5ee
// www.techiedelight.com/trie-implementation-insert-search-delete/
// github.com/michaelbull/c-dictionary-trie/blob/master/dictionary.c

// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 47
#define ALPHA_SIZE 27

// Trie Structure
typedef struct node
{
	bool isWord;
	struct node *children[ALPHA_SIZE];
} node;

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

// My prototypes
// recursive function to free all the nodes in the structure
void freeNode(node *cursor);

#endif // DICTIONARY_H
