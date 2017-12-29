#include <stdio.h>

#define ARGUMENTS_NUM 2
#define PARENTHESIS_MAX 10000
#define R_PARENTHESIS '('
#define L_PARENTHESIS ')'
#define R_BRACES '{'
#define L_BRACES '}'
#define R_DIAMOND '<'
#define L_DIAMOND '>'
#define R_BRACKETS '['
#define L_BRACKETS ']'


/**
 * check if a given char is a parenthesis(of any kind).
 * @param ch the char to test.
 * @return 1 if the char is a parenthesis, false otherwise
 */
int isParenthesis(char ch);

/**
 * given a path of a file, reads it, and return the parenthesis characters from it.
 * @param fileName the path of the file.
 * @return a String contains only parenthesis.
 */
char* getParenthesis(char *fileName);

/**
 * given a pointer to a char, and check if it's a legall combination.
 * @param parenthesis the combination of parenthesis to check.
 * @return 1 if it's legal, 0 otherwise.
 */
int isLegal(char *parenthesis);

/**
 * this program given a path of a file as argument, and test if the parenthesis inside it are
 * legall combination. prints a message to the screen accordingly.
 * @param argc the number of arguments give to the program.
 * @param argv the file's path.
 * @return 0 for a success run of the program, 1 otherwise.
 */
int main(int argc, char* argv[])
{
    if (argc != ARGUMENTS_NUM)
    {
        fprintf(stderr, "Please supply a file!\nusage: CheckParenthesis <file name>\n");
        return 1;
    }
    char* parenthesis;
    if ((parenthesis = getParenthesis(argv[1])) == NULL)
    {
        return 1;
    }
    int ok = isLegal(parenthesis);
    if (ok)
    {
        printf("ok\n");
    }
    else
    {
        printf("bad structure\n");
    }
    return 0;
}

int isParenthesis(char ch)
{
    char const parenthesis[] = {'<', '{', '(', '[', '>', '}', ')', ']', '\0' };
    unsigned int i;
    for (i = 0; i < sizeof(parenthesis) / sizeof(char); i++)
    {
        if (ch == parenthesis[i])
        {
            return 1;
        }
    }
    return 0;
}

char* getParenthesis(char *fileName)
{
    char c;
    static char outcome[PARENTHESIS_MAX];
    FILE *file;
    file = fopen(fileName, "r");
    if (!file)
    {
        fprintf(stderr, "Error! trying to open the file %s\n", fileName);
        return NULL;
    }
    else
    {
        int i = 0;
        while ((c = (char)getc(file)) != EOF)
            // reading the file char by char
        {
            if (isParenthesis(c))
            {
                outcome[i] = c;
                i++;
            }
        }
        outcome[i] = '\0';
        fclose(file);
        return outcome;
    }
}

int isLegal(char *parenthesis)
{
    char stack[10000];
    unsigned int stackSize = 0;
    unsigned int j = 0;
    char currentParenthesis = parenthesis[0];
    while ((currentParenthesis != '\0'))
    {
        if (currentParenthesis == R_BRACKETS || currentParenthesis == R_PARENTHESIS ||
            currentParenthesis == R_BRACES || currentParenthesis == R_DIAMOND )
        {
            // if it's an open parenthesis, just add it to the stack
            stack[stackSize] = currentParenthesis;
            stackSize++;
        }
        else if (currentParenthesis == L_BRACES || currentParenthesis == L_BRACKETS ||
                 currentParenthesis == L_PARENTHESIS || currentParenthesis == L_DIAMOND)
        {
            if (stackSize < 1)
                // first parenthesis in the stack is a closed one. definitely not legal
            {
                return 0;
            }
            char lastParenthesis = stack[stackSize - 1];
            if ((currentParenthesis == L_BRACKETS && lastParenthesis != R_BRACKETS) ||
                (currentParenthesis == L_PARENTHESIS && lastParenthesis != R_PARENTHESIS) ||
                (currentParenthesis == L_BRACES && lastParenthesis != R_BRACES) ||
                (currentParenthesis == L_DIAMOND && lastParenthesis != R_DIAMOND))
                // if the current parenthesis is closed one, and in the stack there is a
                // corresponding open parenthesis, remove the open one and keep checking. otherwise
                // it's not legal, and return 0
            {
                return 0;
            }
            stackSize--;
        }
        j++;
        currentParenthesis = parenthesis[j];
    }
    if (stackSize != 0)
        // stack must be empty in the end of the process
    {
        return 0;
    }
    return 1;
}