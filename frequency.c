#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NUM_LETTERS 26
typedef struct Node
{
    int numWords;
    struct Node *children[NUM_LETTERS];
    int to_print;

} Node;

Node *newNode()
{
    struct Node *ans = (Node *)malloc(sizeof(Node));
    if (!ans)
    {
        return NULL;
    }
    int numWords = 0;
    ans->numWords = numWords;
    ans->to_print = 0;
    int i;
    for (i = 0; i < 26; i++)
    {
        ans->children[i] = NULL;
    }
    return ans;
}

int enterWord(Node *root)
{
    char letter = getchar();
    struct Node *next = root;
    int counter = 0;
    int flag = 1;
    while (letter != EOF && !isspace(letter))
    {
        int c = (int)letter;
        if ((c <= 122 && c >= 97) || (c >= 65 && c <= 90))
        {

            counter++;
            letter = tolower(letter);
            c = (int)letter;
            int index = letter - 'a';
            if (next->children[index] == NULL)
            {

                next->children[index] = newNode();
            }
            next = next->children[index];

            flag = 0;
        }
        letter = getchar();
    }
    if (flag)
    {
        root->to_print++;
    }
    next->numWords++;
    return counter;
}

void printLex(struct Node *root, char str[], int currentDepth)
{
    if (root->numWords && currentDepth != 0)
    {
        str[currentDepth] = '\0';
        printf("%s %d\n", str, root->numWords);
    }
    int i;
    for (i = 0; i < 26; i++)
    {
        if (root->children[i])
        {
            str[currentDepth] = i + 'a';
            printLex(root->children[i], str, currentDepth + 1);
        }
    }
    free(root);
}

void printRev(struct Node *root, char str[], int currentDepth)
{

    int i;
    for (i = NUM_LETTERS; i >= 0; i--)
    {
        if (root->children[i])
        {
            str[currentDepth] = i + 'a';
            printRev(root->children[i], str, currentDepth + 1);
        }
    }
    if (root->numWords && currentDepth != 0)
    {
        str[currentDepth] = '\0';
        printf("%s %d\n", str, root->numWords);
    }
    free(root);
}
//Check the depth of the
int depth(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int max = 0;
    int i;
    int depths[26];
    for (i = 0; i < 26; i++)
    {
        depths[i] = depth(root->children[i]);
    }
    for (i = 0; i < 26; i++)
    {
        if (depths[i] > max)
        {
            max = depths[i];
        }
    }

    return max + 1;
}

int main(int argc, char *argv[])
{
    int doReverse = 0;
    if (argc > 1)
    {
        if (*argv[1] == 'r')
        {
            doReverse = 1;
        }
    }
    struct Node *source = newNode();
    int x = enterWord(source);
    while (x != 0)
    {
        x = enterWord(source);
    }
    int deep = depth(source);
    char *word = (char *)malloc(sizeof(char) * deep);
    if (word == NULL)
    {
        printf("fail");
        exit(1);
    }

    source->to_print = 0;
    if (doReverse)
    {
        printRev(source, word, 0);
    }
    else
    {
        printLex(source, word, 0);
    }

    free(word);
}