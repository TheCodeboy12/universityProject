#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globalConstants.h"
#include "globalEnums.h"
#include "../firstRun/enums.h"

/*File open function*/
FILE* openFile(char* filePath) {
    FILE* file;

    file = fopen(filePath, "r"); /* open file in read mode */
    if (file == NULL) {
        perror("Could not open file"); /* print detailed error message to stderr */
        exit(EXIT_FAILURE); /* exit program with failure status */
    }

    return file;
}


/*Check if comment*/
int checkFirstChar(const char *str, const char arg)
{
    int i;
    i=0;
    while (str[i] == ' ') i++;
    return str[i]==arg; 
    /*Return whether the arg char is the first char*/
}

/*Check if string is empty*/
int checkIfEmpty(const char* str) {
    /*If empty ->1
    not empty ->0*/
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
            return 0;
        }
    }
    return 1;
}


char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); /* +1 for the null-terminator*/
    /* in real code you would check for errors in malloc here*/
    if (result == NULL)
    {
        printf("Error allocating memory\n");
        exit(1);
    }
    
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int checkIfOP(char *str)
{
    int i;
    for (i = 0; i < NUM_OPS; i++)
    {
        if (strcmp(str,operationStrings[i]) ==0)
        {
            return i;
        }
        
    }
    return -1;
}
int checkIfInstruction(char *str)
{
    int i;
    for (i = 0; i < NUM_INSTRUCTIONS; i++)
    {
        if (strcmp(str,instructionsArr[i]) ==0)
        {
            return i;
        }
        
    }
    return -1;
}

/**
 * This function takes in a pointer to a string and will return a pointer to the same string after it skipped all the white charecters
 * @param p a pointer to a string
 * @return char * type - a pointer after skipping the white charecters
 */
char *skipWhites(char *p)
{
  while (isspace(*p) && *p != '\n' && *p != '\0')
  {
    p++; /*Skip spaces*/
  }
  return p;
}

/**
 * This function takes in a pointer to a string and will check if there exists any externous text after it
 * @param cursor -  a char* type
 */
int checkIfExternousText(char *cursor)
{
  char *p;
  p = cursor;
  while (*p != '\0' && *p != '\n' && isspace(*p))
  {
    p++;
  }
  if (*p == '\0' || *p == '\n')
  {
    return 0;
  }
  else
  {
    return 1;
  }
}


/**
 * Will attemp to get the word until a certain char is found or until the word is not alphanumeric
 * if the char was not found but end of line or EOF is found itll default to return the word still
 * will autmatically put '\0' at the end of the word
 * @param word is the word to get
 * @param c is the char to stop at
 * @return a pointer to the word or null if not found
 */
char *getWordUntil(char *word, char c)
{
    char *resault;
    char *p = word;
    while (*p != c && isalnum(*p))
    {
        p++;
    }
    if (*p == c || *p == '\0' || *p == '\n')
    {
        resault = (char *)malloc((p - word) * sizeof(char) + 1);
        strncpy(resault, word, p - word);
        resault[p - word] = '\0';
        return resault;
    }
    else
    {

        return NULL;
    }
}


/**
 * Will return a pointer to a charecter as so:
 * *p != c && *p != '\0' && *p != '\n'
 * @return if found that charecter NULL otherwise
 */
char *skipUntil(char *word, char c)
{
    char *p = word;
    while (*p != c && *p != '\0' && *p != '\n')
    {
        p++;
    }
    if (*p == c)
    {
        return p;
    }
   
    else
    {
        return NULL;
    }
}

/**
 * Will return a pointer to a charecter as so:
 * *p != c && *p != '\0' && *p != '\n'
 * @return if found that charecter NULL otherwise
 */
char *skipUntilOrEOF(char *word, char c)
{
    char *p = word;
    while (*p != c && *p != '\0' && *p != '\n')
    {
        p++;
    }
    if (*p == c)
    {
        return p;
    }
    else if (*p == '\0' || *p == '\n')
    {
        return p;
    }
    else
    {
        return NULL;
    }
}



/**
 * This function will get the first word form a given pointer to a string
 * @param str the pointer to the string
 * @return a pointer to the first word
*/
char *getFirstWord(char *str)
{
    char *firstWord;
    char *cursor;
    char *p;
    int i;
    cursor = str;
    p = skipWhites(cursor);
    i = 0;
    while (!isspace(*p) && *p != '\0' && *p != '\n')
    {
        i++;
        p++;
    }
    firstWord = (char *)malloc(sizeof(char) * (i + 1));
    if (firstWord == NULL)
    {
        printf("Malloc failed\n");
        exit(1);
    }
    p = firstWord;
    cursor = skipWhites(cursor);
    while (!isspace(*cursor) && *cursor != '\0' && *cursor != '\n')
    {
        *p = *cursor;
        p++;
        cursor++;
    }
    *p = '\0';
    return firstWord;
}


/**
 * This function will search how many times a char appears in a string
 * @param str is the string to search in
 * @param c is the char to search for
 * @return the number of times c appears in str
 */
int countCharInString(char *str, char c)
{
    int count = 0;
    while (*str != '\0' && *str != '\n')
    {
        if (*str == c)
        {
            count++;
        }
        str++;
    }
    return count;
}
