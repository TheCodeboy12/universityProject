#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./enums.h"
#include "../globals/helperFuncs.h"
#include "lineStructs.h"
#include "../globals/criticalNumbers.h"
#include "./helperFunctions.h"


char *getLabel(char *cursor, int rowNum, unsigned int *errorsInFile, unsigned int *labelFound)
{
    char *p, *p2;
    p2 = skipUntil(cursor, ':');

    /*If a label deliminator is found*/
    if (p2 != NULL)
    {
        p = cursor;
        /*A label must begin with an alpha charecter*/
        if (isalpha(*p))
        {
            /*Now we check that all of label is alphanumeric*/
            while (p < p2 && isalnum(*p))
            {
                p++;
            }
            if (*p != ':')
            {
                (*errorsInFile) = 1;
                printf("Error: line %d: label must contain only alpha Numeric charecters \n", rowNum);
            }
            else
            {
                *labelFound = 1;
                return getWordUntil(cursor, ':');
            }
        }
        else
        {
            printf("Error: line %d: label must begin with an alpha charecter\n", rowNum);
            (*errorsInFile) = 1;
        }
    }
    else
    {
        return NULL;
    }
    return NULL;
}

void getLineType(char *line ,int *AItype , int *AIsubType)
{

    char *AI;
    char *cursor, *p;

    cursor = line;
    cursor = skipWhites(cursor);
    /*Try to go to the label deliminator*/
    p = skipUntil(cursor, ':');
    /*Now, p is either NULL or a pointer in the line*/
    if (p != NULL)
    {
        cursor = p + 1;
        cursor = skipWhites(cursor);
        /*now cursor pointer to something, we want to check what that is.*/
    }
    if (*cursor == '.')
    {
        cursor++;
    }

    AI = getWordUntil(cursor, ' ');
    if (AI == NULL)
    {
        (*AItype) = -1;
        (*AIsubType) = -1;
        return;
    }
    else
    {

        /*=====Now we want to check what kind of line we have======*/
        (*AIsubType) = checkIfOP(AI);
        if ((*AIsubType) == -1)
        {
            /*Its not an action
            We will check if its an instruction*/

            (*AIsubType) = checkIfInstruction(AI);

            if ((*AItype) == -1)
            {
                /*Its not an instruction either*/
                (*AItype) = -1;
                (*AIsubType) = -1;
                return;
            }
            else
                (*AItype)=  INSTRUCTION;
        }
        else
        {
            (*AItype) = ACTION;
        }
        free(AI);  /*We dont need the word anymore*/
        AI = NULL; /*We dont want a dangline pointer*/

    }
}



int getNumberFromString(char *buffer)
{
    int num = 0;
    int sign = 1;
    char *p = buffer;
    if (*p == '-' || *p == '+')
    {
        if (*p == '-')
            sign = -1;
        p++;
    }
    while (isdigit(*p))
    {
        num = num * 10 + (*p - '0');
        p++;
    }
    return num * sign;
}

char *getActionOperand(char *cursor, char *endOfLine)
{
    char *p;
    char *operand;
    if (*cursor == '@')
    {
        /* we could be looking at a register*/
        p = cursor;
        p++;
        while (cursor < endOfLine && isalnum(*p))
        {
            p++;
        }
        if (*p == '\0' || *p == '\n' || isspace(*p) || *p == ',')
        {
            operand = (char *)malloc((p - cursor) * sizeof(char) + 1);
            operand = strncpy(operand, cursor, p - cursor);
            operand[p - cursor] = '\0';
            return operand;
        }
        else
        {
            return NULL;
        }
    }

    else if (*cursor == '-' || *cursor == '+' || isdigit(*cursor))
    {
        /*we could be looking at a number
        We are going to take the whole number and later check them
        we could be loking at
        6,  -9 ,    15
        -1  , X
        6,  -9 ,   . 15 - error

        */
        if (*cursor == '-' || *cursor == '+')
            p = cursor + 1;
        else
            p = cursor;
        while (isdigit(*p) && p < endOfLine)
        {
            p++;
        }
        /*We check whats right after the number*/
        /*These are charecters that are ok to appear RIGHT after a number.*/

        if (*p == '\0' || *p == '\n' || isspace(*p) || *p == ',')
        {
            operand = (char *)malloc((p - cursor) * sizeof(char) + 1);
            operand = strncpy(operand, cursor, p - cursor);
            operand[p - cursor] = '\0';
            return operand;
        }
        else
        {
            return NULL;
        }
    }
    else if (isalnum(*cursor))
    {
        /*We could be looking at a label*/
        p = cursor;
        while (isalnum(*p) && p < endOfLine)
        {
            p++;
        }
        operand = (char *)malloc((p - cursor) * sizeof(char) + 1);
        operand = strncpy(operand, cursor, p - cursor);
        operand[p - cursor] = '\0';
        return operand;
    }
    else
    {
        printf("Error: unexpected char found in the beginning of your operand operands\n");
        return NULL;
    }
}

int getOperandType(char *operand, int *type, int *subType)
{

    if (operand == NULL)
    {
        printf("operand is null\n");
        return -1;
    }
    if (*operand == '@')
    {
        /*we are looking at a register*/
        (*type) = REGISTER;
        (*subType) = checkIfRegister(operand);

        return (*type);
    }
    else if (*operand == '-' || *operand == '+' || isdigit(*operand))
    {
        /*we are looking at a number*/
        (*type) = NUMBER;
        (*subType) = getNumberFromString(operand);
        if ((*subType) < (MIN_SIGNED(MAX_BITS_ACTION_NUMBER)) || (*subType) > (MAX_SIGNED(MAX_BITS_ACTION_NUMBER)))
        {
            printf("Error: Number %d is too big and wont fit 12 bits\n", (*subType));
            (*subType) = -1;
        }

        return (*type);
    }
    else if (isalpha(*operand))
    {
        /*we are looking at a label*/
        (*type) = LABEL;
        (*subType) = ACTION;
        return (*type);
    }
    else
    {
        printf("Error: invalid operand\n");
        return -1;
    }
}
