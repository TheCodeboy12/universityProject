#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hashTable.h"
#include "./helperFunctions.h"
#include "./enums.h"
#include "./firstRunConstants.h"
#include "lineStructs.h"
#include "../globals/criticalNumbers.h"
#include "../globals/globalEnums.h"
#include "../globals/globalConstants.h"
#include "lineAnalayzer.h"
#include "../globals/helperFuncs.h"

#define ACTIONLENGTH 3



/**
 * First run will check for errors in the lines, collect them using token and linstructure struct and will present them
 * in their err members.
 * This function will also collect all of the labels and put them in the lable table (a hash table)
 * @param f is an input file
 * @param lt is a pointer to a label table
 * @param IC - is a pointer to the action memory addresses
 * @param DC - is a pointer to the action memory addresses
 * @param iB is a pointer to a bitfield array of instructions
 * @param aB is a pointer to a bitField array of actions
 */
unsigned int firstRun(FILE *f, unsigned int *IC, unsigned int *DC, labelTable **lt, labelTable **ltExterns, labelTable **ltEntries, lineStructArray *lsa, lineStructArray *lsd)
{
    char *line, *cursor, *endOfLine, *p, *p2;
    unsigned int rowNum = 0, labelFound = 0;
    int AItype, sourceOperandType, destOperandType;
    int AIsubType, sourceOperandSubType, destOperandSubType;
    int useFulInt = 0;
    lineStructNode *ls;
    labelTableNode *tn;

    Token *t_label,*t_AI , *t_source, *t_dest;
    unsigned int errorsInFile = 0, errorsInLine = 0;

    /*
    token *actionInstruction;
    lineStructure *lineStruct;
    token *labelToken;
    token *source, *dest;
    size_t i;
    labelTableNode *tn;
    */

    char *labelName = NULL, *dest = NULL, *source; /*The words I am trying to collect*/

    line = (char *)malloc(LINELENGH + 3 * sizeof(char));

    /*===========================START ITERATE ON THE FILE===========================*/
    while (fgets(line, LINELENGH + 3, f) != NULL)
    {
        /*Initilize the variables and advance rowNum*/
        rowNum++;
        labelFound = 0;
        labelName = NULL;
        source = NULL;
        dest = NULL;
        destOperandSubType =0;
        sourceOperandSubType =0;
        destOperandType =0;
        sourceOperandType =0;
        AIsubType =0;
        AItype =0;


        /*printf("******New LINE******\n");*/

        cursor = line;
        endOfLine = line + LINELENGH; /*Set the end of the line pointer to point to expected end of the line*/
        if (checkIfExternousText(endOfLine))
        {
            errorsInFile = 1;
            printf("Error: line %d: line is too long\n", rowNum); /*If line is too long*/
            rowNum++;
            continue;
        }

        getLineType(line, &AItype, &AIsubType);


        /*IF we have a properly set AI sub type and type we can continue*/
        if (AItype != -1 && AIsubType != -1)
        {
            /*Create nodes in the respective linestruct arrays*/
            if (AItype == ACTION)
            {
                /*Create a new lineStruct in the action array*/
                ls = createNewLineStructNode(lsa, rowNum);
                setLsType(ls, ACTION);
            }
            else if (AItype == INSTRUCTION)
            {
                /*Create a new lineStruct in the instructions array*/
                ls = createNewLineStructNode(lsd, rowNum);
                setLsType(ls, INSTRUCTION);
            }

            /*Ass*/
            t_AI = newToken();
            setType(t_AI, AItype);
            setSubType(t_AI, AIsubType);
            setLSToken(ls, t_AI , a_tok);
            

            /*DEBUG*/
            
            cursor = skipWhites(cursor);
            /*line cannot be empty becuase of the preassembler*/

            /*=======Try and get the label=======*/

            labelName = getLabel(cursor, rowNum, &errorsInLine, &labelFound);

            if (errorsInLine)
            {
                errorsInLine = 0;
                errorsInFile = 1;
                continue;
            }

            if (labelFound)
            {

                /*printf("label name is %s\n", labelName);*/
                cursor = cursor + strlen(labelName) + 1;
                /*We have a label*/
                if (search(*lt, labelName) == 1)
                {
                    errorsInFile = 1;
                    printf("Error: line %d: label already exists\n", rowNum);
                    free(labelName);
                    continue;
                }
                else
                {
                    t_label = newToken();
                    setWord(t_label, labelName);
                    setType(t_label, LABEL);
                    setSubType(t_label, 0);
                    setLSToken(ls, t_label , l_tok);
                    
                    if (AItype == ACTION)
                    {
                        insertLabelNode(lt, labelName, *IC);
                    }
                    else if (AItype == INSTRUCTION)
                    {
                        insertLabelNode(lt, labelName, *DC);
                    }
                }
            }
            else
            {
                labelFound = 0;
            }
            cursor = skipWhites(cursor);
            cursor = skipUntilOrEOF(cursor, ' ');
            cursor = skipWhites(cursor);
            /*If we look at an instruction line*/
            if (*cursor == '.')
            {
                cursor++;
            }

            /*============= We will continue only if we have properly set type and subtype== == =======*/
            if (AItype != -1 && AIsubType != -1)
            {
                cursor = skipWhites(cursor);
                /*We will now try to get the source operand*/
                if (AItype == ACTION)
                {
                    cursor = skipWhites(cursor);

                    /*We will now attemp to retrive the operands but only if there should be operands
                    depending on the type of action we have.*/

                    if (AIsubType == mov ||
                        AIsubType == cmp ||
                        AIsubType == add ||
                        AIsubType == sub ||
                        AIsubType == lea)
                    {
                        /* Here we have operands that have both a source operand and dest operand seperated by comma */
                        /*First, lets find out if there is even a comma there*/
                        useFulInt = countCharInString(cursor, ',');
                        if (useFulInt > 1)
                        {
                            printf("Error: line %d: too many commas\n", rowNum);
                            errorsInFile = 1;

                            continue;
                        }
                        else if (useFulInt == 0)
                        {
                            printf("Error: line %d: missing comma seperator for second operand or unexepected char found instead of comma\n", rowNum);
                            errorsInFile = 1;
                        }

                        else
                        {
                            /*We have exactly one comma*/
                            p = skipUntil(cursor, ',');
                            /*we now hold the position of the comma and we will retrive the operands from before and after it*/
                            source = getActionOperand(cursor, p);
                            if (source != NULL)
                            {
                                t_source = newToken();
                                setWord(t_source, source);
                                setLSToken(ls, t_source , s_tok);
                                
                                useFulInt = getOperandType(source, &sourceOperandType, &sourceOperandSubType);
                                if (sourceOperandType != -1 && sourceOperandSubType != -1)
                                {
                                    cursor = cursor + strlen(source) + 1;
                
                                    cursor = skipWhites(cursor);
                                    /*Check if a comma is found in the string*/
                                    if (cursor >= p)
                                    {
                                        /* Comma was found and p points to it */
                                        cursor = p + 1;
                                        cursor = skipWhites(cursor);
                                        /*Create a token for it and add it to linestruct*/
                                        setType(t_source, sourceOperandType);
                                        setSubType(t_source, sourceOperandSubType);

                                        /*we will now try to retrive dest*/
                                        dest = getActionOperand(cursor, endOfLine);
                                        if (dest != NULL)
                                        {
                                            t_dest = newToken();
                                            setWord(t_dest, dest);
                                            setLSToken(ls, t_dest, d_tok);
                                            
                                            cursor = cursor + strlen(dest) + 1;
                                            getOperandType(dest, &destOperandType, &destOperandSubType);
                                            
                                            if (destOperandType != -1 && destOperandSubType != -1)
                                            {
                                                
                                                if (!checkIfExternousText(cursor))
                                                {
                                                    
                                                    cursor = skipWhites(cursor);
                                                    /*Create a token for it and add it to linestruct*/
                                                    setType(t_dest, destOperandType);
                                                    setSubType(t_dest, destOperandSubType);

                                                    
                                                    if (destOperandType == REGISTER && sourceOperandType == REGISTER)
                                                    {
                                                        (*IC) += 2;
                                                    }
                                                    else
                                                        (*IC) += 3;
                                                    if (useFulInt == 1)
                                                    {
                                                        errorsInFile = 1;
                                                    }
                                                }
                                                else
                                                {
                                                    errorsInFile = 1;
                                                    printf("Error: line %d: too many operands\n", rowNum);
                                                    continue;
                                                }
                                            }
                                            else
                                            {
                                                errorsInFile = 1;
                                                printf("Error: line %d: invalid dest operand\n", rowNum);
                                                continue;
                                            }
                                        }
                                        else
                                        {
                                            errorsInFile = 1;
                                            printf("Error: line %d: missing dest operand\n", rowNum);

                                            continue;
                                        }
                                    }
                                    else
                                    {
                                        errorsInFile = 1;
                                        printf("Error: line %d: Comma seperator was misplaced or unexpected char found in the operand\nplease check that you placed the comma seperator in between the operands and that your command is correct \n", rowNum);

                                        continue;
                                    }
                                }
                                else
                                {
                                    printf("Error: line %d: invalid source operand please check it.\n", rowNum);
                                    free(source);
                                    errorsInFile = 1;
                                }
                            }
                            else
                            {
                                errorsInFile = 1;
                                printf("Error: line %d: missing source operand or found errors in it - wont check for dest operand\nPlease check the line\n", rowNum);
                            }
                        }
                    }

                    else if (
                        AIsubType == not ||
                        AIsubType == clr ||
                        AIsubType == inc ||
                        AIsubType == dec ||
                        AIsubType == jmp ||
                        AIsubType == bne ||
                        AIsubType == red ||
                        AIsubType == prn ||
                        AIsubType == jsr)
                    {
                        /* Here we have operands that have only a dest operand */
                        /*First, lets find out if there is even a comma there*/
                        useFulInt = countCharInString(cursor, ',');
                        if (useFulInt > 0)
                        {
                            printf("Error: line %d: too many commas\n", rowNum);
                        }
                        else
                        {
                            dest = getActionOperand(cursor, endOfLine);
                            if (dest != NULL)
                            {


                                t_dest = newToken();
                                setWord(t_dest, dest);
                                setLSToken(ls, t_dest , d_tok);
                                
                                getOperandType(dest, &destOperandType, &destOperandSubType);
                                if (destOperandType != -1 && destOperandSubType != -1)
                                {
                                    cursor = cursor + strlen(dest) + 1;
                                    if (!checkIfExternousText(cursor))
                                    {
                                        /*printf("dest is %s\n", dest);*/
                                        cursor = cursor + strlen(dest) + 1;
                                        cursor = skipWhites(cursor);
                                        /*Create a token for it and add it to linestruct*/
                                        setType(t_dest, destOperandType);
                                        setSubType(t_dest, destOperandSubType);
                                        setLSToken(ls, t_dest , d_tok);
                                        
                                        useFulInt = checkActionLinestructsForErrors(ls);
                                        
                                        (*IC) += 2;
                                        if (useFulInt == 1)
                                        {
                                            errorsInFile = 1;
                                        }
                                    }
                                    else
                                    {
                                        errorsInFile = 1;
                                        printf("Error: line %d: too many operands\n", rowNum);
                                    }
                                }
                                else
                                {
                                    errorsInFile = 1;
                                    printf("Error: line %d: invalid dest operand\n", rowNum);
                                }
                            }
                            else
                            {
                                errorsInFile = 1;
                                printf("Error: line %d: missing dest operand or found syntax errors in it\n", rowNum);
                            }
                        }
                    }
                    else if (AIsubType == rts ||
                             AIsubType == stop)
                    {
                        if (*cursor != '\0' && *cursor != '\n' )
                        {
                            errorsInFile = 1;
                            printf("Error: line %d: too many operands for stop command\n", rowNum);
                        }
                        else
                            (*IC)++;
                    }
                    else
                    {
                        errorsInFile = 1;
                        printf("Error: line %d: unknown action\n", rowNum);
                    }
                }
                else if (AItype == INSTRUCTION)
                {
                    cursor = skipWhites(cursor);
                    if (AIsubType == STRING)
                    {
                        if (*cursor == '\"')
                        {
                            /*we are inside of parenthesis*/
                            p = cursor + 1;
                            p2 = skipUntil(p, '\"');
                            if (p2 != NULL)
                            {
                                if (checkIfExternousText(p2 + 1))
                                {
                                    errorsInFile = 1;
                                    printf("Error: line %d: externous text found after string closing parenthesis\n", rowNum);
                                }
                                else
                                {
                                    source = (char *)malloc((p2 - p) * (sizeof(char) + 1));

                                    strncpy(source, p, p2 - p);
                                    source[p - p2] = '\0';

                                    /*printf("source in string is %s\n", source);*/

                                    t_source = newToken();
                                    setWord(t_source, source);
                                    setType(t_source, STR);
                                    setSubType(t_source, (strlen(source)));
                                    (*DC) += getSubType(t_source) + 1;
                                    setLSToken(ls, t_source , s_tok);
                                    
                                }
                            }
                            else
                            {
                                errorsInFile = 1;
                                printf("Error: line %d: missing parenthesis\n", rowNum);
                            }
                        }
                        else
                        {
                            errorsInFile = 1;
                            printf("Error: line %d: missing parenthesis\n", rowNum);
                        }
                    }
                    else if (AIsubType == DATA)
                    {
                        /*Data holds number and so we would like to retrive them
                        numbers are seperated by commas.
                        each number should start with either - + or just a number
                        there could be multiple numbers and there could be one but there must be one*/
                        if (isdigit(*cursor) || *cursor == '-' || *cursor == '+')
                        {
                            p = cursor;
                            while ((isdigit(*p) || *p == '-' || *p == '+' || isspace(*p) || *p == ',') && *p != '\0' && *p != '\n')
                            {
                                p++;
                            }
                            if (*p == '\0' || *p == '\n')
                            {
                                /*We have reached the end of the line*/
                                t_source = newToken();
                                
                                source = (char *)malloc((p - cursor) * sizeof(char) + 1);
                                strncpy(source, cursor, p - cursor);
                                source[p - cursor] = '\0';
                                setWord(t_source, source);
                                setLSToken(ls, t_source , s_tok);


                                if (!checkNumbers(source, &errorsInFile, rowNum))
                                {
                                    /*printf("source in data is %s\n", source);*/
                                    cursor = p;
                                    
                                    
                                    setType(t_source, DATA);
                                    setSubType(t_source, countCharInString(source, ',') + 1);
                                    (*DC) += getSubType(t_source);
                                    setLSToken(ls, t_source , s_tok);
                                    
                                }
                                else
                                {
                                }
                            }
                            else
                            {
                                errorsInFile = 1;
                                printf("Error: line %d: Externous text found after parenthesis in data line\n", rowNum);
                            }
                        }
                    }
                    else if (AIsubType == EXTERN)
                    {
                        /* extern can have one operand and its a label */
                        p = cursor;
                        while (isalnum(*p))
                        {
                            p++;
                        }

                        if (*p == '\0' || *p == '\n' || isspace(*p))
                        {
                            t_source = newToken();
                            source = (char *)malloc((p - cursor) * sizeof(char) + 1);
                            strncpy(source, cursor, p - cursor);
                            source[p - cursor] = '\0';
                            setWord(t_source, source);
                            /*printf("source in extern is %s\n", source);*/
                            cursor = p;
                            setType(t_source, EXTERN);
                            setLSToken(ls, t_source, s_tok);
                            
                            insertLabelNode(ltExterns, source, 0);
                            
                        }
                        else
                        {
                            errorsInFile = 1;
                            printf("Error: line %d: missing operand or unexpected char found in extern\n", rowNum);
                        }
                    }
                    else if (AIsubType == ENTRY)
                    {
                        if (labelFound)
                        {
                            printf("WARNING : line %d: entry command found with label\n", rowNum);
                        }
                        /* entry can have one operand and its a label */
                        p = cursor;
                        while (isalnum(*p))
                        {
                            p++;
                        }
                        if (*p == '\0' || *p == '\n' || isspace(*p))
                        {
                            t_source = newToken();
                            source = (char *)malloc((p - cursor) * sizeof(char) + 1);
                            strncpy(source, cursor, p - cursor);
                            source[p - cursor] = '\0';
                            setWord(t_source, source);
                            /*printf("source in extern is %s\n", source);*/
                            cursor = p;
                            setType(t_source, ENTRY);
                            setLSToken(ls, t_source , s_tok);
                            
                            insertLabelNode(ltEntries, getWord(t_source), 0);
                        }
                        else
                        {
                            errorsInFile = 1;
                            printf("Error: line %d: missing operand or unexpected char found in extern\n", rowNum);
                        }
                    }
                }
            }
            else
            {
                errorsInFile = 1;
                printf("Error: line %d: missing action or instruction or errors found in it\n", rowNum);
                continue;
            }
        }
        else
        {
            printf("Error: line %d: missing or unrecognized action or instruction or errors found in it\n", rowNum);
            errorsInFile = 1;
            continue;
        }
        
    }

    
    if (!errorsInFile)
    {
        ls = getLSNodeHead(lsd);
        while (ls != NULL)
        {
            p = getWord(getLSToken(ls , l_tok));
            if (p != NULL)
            {
                tn = searchAndGetNode(*lt, p);

                while (tn != NULL)
                {
                    /*printf("memAddr  before is %d\n", getMemAddrFromNode(tn));*/
                    setMemAddrOfNode(tn, (getMemAddrFromNode(tn) + *IC));
                    /*printf("memAddr  after is %d\n", getMemAddrFromNode(tn));*/
                    tn = getNextNode(tn);
                }
            }

            ls = getNextLSNode(ls);
        }
    }

    free(line);

    return errorsInFile;

}
