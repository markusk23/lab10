#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of characters in a word
#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};

// Initialize a TrieNode
struct TrieNode *createNode()
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node)
    {
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Inserts a word into the trie structure
void insert(struct TrieNode *root, char *word)
{
    struct TrieNode *current = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
        {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->count++;
}

// Computes the number of occurrences of a word
int numberOfOccurrences(struct TrieNode *root, char *word)
{
    struct TrieNode *current = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
        {
            return 0; // Word not found
        }
        current = current->children[index];
    }
    return current->count;
}

// Deallocates memory for the trie structure
void deallocateTrie(struct TrieNode *root)
{
    if (root)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (root->children[i])
            {
                deallocateTrie(root->children[i]);
            }
        }
        free(root);
    }
}

// Reads the dictionary file and populates the array of words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file==NULL) return -1;

    int count = 0;

    fscanf(file, "%d\n", &count);
    char word[100];
    for(int i=0; i<count; i++){
        fscanf(file, "%s\n", word);
        pInWords[i]= (char*)calloc(strlen(word), sizeof(char));
        strcpy(pInWords[i],word);
    }
    
    return count;
}

int main(void)
{
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode *root = createNode();

    // Insert each word from the dictionary into the trie
    for (int i = 0; i < numWords; i++)
    {
        insert(root, inWords[i]);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }

    // Deallocate memory used by the trie
    deallocateTrie(root);

    return 0;
}
