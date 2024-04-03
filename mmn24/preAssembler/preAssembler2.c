#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../globals/helperFuncs.h"
#include "../firstRun/helperFunctions.h"
#include "../globals/errorMessages.h"
#include "macroArray.h"
#define macroWord "mcro"
#define endMacroWord "endmcro"
#define macroWordLength 4
#define endMacroWordLength 7
#define MAX_LINE_LENGTH 81
#define INITSIZE 1000


static int checkIfMacroHasValidName(char *str)
{
    return 
        checkIfInstruction(str) != -1 ||
        checkIfOP(str) != -1 ||
        checkIfRegister(str) != -1;
}

/**
 * This function will check if a pointer to a string starts with the macroWord
 * @param str the string to check
 * @return 1 if it is macroWord
 * @return 0 if it is not macroWord
 */
static int checkIfMacro(char *str)
{
    char *cursor;
    char *m;
    size_t i;
    cursor = str;
    m = macroWord;
    for (i = 0; i < macroWordLength; i++)
    {
        if (*cursor != *m)
        {
            return 0;
        }
        cursor++;
        m++;
    }
    if (!isspace(*cursor))
    {
        return 0;
    }

    return 1;
}

static int checkIfEndMacro(char *str)
{
    char *cursor;
    char *m;
    size_t i;
    cursor = str;
    m = endMacroWord;
    for (i = 0; i < endMacroWordLength; i++)
    {
        if (*cursor != *m)
        {
            return 0;
        }
        cursor++;
        m++;
    }

    return 1;
}

/**
 * This function will iterate over the .as file and will check the following:
 * 1. If there are any errors in the file
 * 2. If there are any macros in the file it will save them (if they dont exists already) to the macro array
 * 3. If it encounters that macro by its name itll write what it saved in the macro array to the .am file
 * 4. It will ignore lines that start with  ; or empty lines (after skipping the white charecters)
 * @note a macro is defined if the line starts with "mcro" after skipping the white charecters
 * @note a macro is ended if the line starts with endmcro (not neccessarily in the same line)
 * @note the name of the macro is the first word after the "mcro" word (after skipping the white charecters)
 * @note a macro cannot be defined inside another macro
 * @note a macro name cannot be the name of an action or an instruction or an opernad
 *
 * @note a line cannot exceed 80 charecters (not including the \n)
 * @param asFileName the name of the .as file
 * @param amFileName the name of the .am file
 * @return 0 if there were no errors in the file
 * @return 1 if there were errors in the file
 */
int preAssembler(FILE *asFile, FILE *amFile)
{
    char *line, *cursor, *macroName, *p;
    char *firstWord;
    int lineNum, errorsInFile, insideMacro;
    struct macroArray *ma;
    lineNum = 0;
    errorsInFile = 0;
    insideMacro = 0;
    ma = NULL;
    line = NULL;
    cursor = NULL;
    macroName = NULL;

    ma = newMacroArray(INITSIZE);
    if (ma == NULL)
    {
        printf("Error allocating memory\n");
        return 1;
    }
    line = (char *)malloc((MAX_LINE_LENGTH +2) * sizeof(char));
    if (line == NULL)
    {
        printf("Error allocating memory\n");
        freeMacroArray(ma);
        return 1;
    }

    /*========== START ITERATING ON FILE == == == = */
    while (fgets(line, (MAX_LINE_LENGTH) , asFile) != NULL)
    {
        cursor = line;
        cursor = skipWhites(cursor);
        lineNum++;
        if (checkIfExternousText(line  + MAX_LINE_LENGTH+1))
        {
            printf("Line %d is too long\n", lineNum);
            errorsInFile = 1;
            freeMacroArray(ma);
            free(line);

            return errorsInFile;
        }
        if (cursor[0] == ';' || cursor[0] == '\n' || cursor[0] == '\0')
        {
            /*We just skip that line*/
            continue;
        }

        /*========== CHECK IF MACRO == == == = */

        if (checkIfMacro(cursor))
        {
            if (!insideMacro)
            {
                /*saw a mcro and space following it in the first word*/
                cursor += macroWordLength;
                cursor = skipWhites(cursor);
                /*now were supposed to land on the first charecter of the macro name */
                if (isalpha(*cursor))
                {
                    p = cursor;
                    while (isalnum(*p))
                    {
                        p++;
                    }
                    /*p is now on a non alpha numeric charecter*/
                    /*Check if there is an externous text*/
                    if (!checkIfExternousText(p))
                    {
                        macroName = getWordUntil(cursor, ' ');
                        if (!searchMacroArray(ma, macroName))
                        {
                            if(!checkIfMacroHasValidName(macroName))
                            {
                                insertMacroNameToMacroArray(&ma, macroName);
                                insideMacro = 1;
                                continue;
                            }
                            else
                            {
                                printf("ERROR : Line %d: Macro name %s is not valid and may be a name of an action or an instruction\n", lineNum, macroName);
                                free(macroName);
                                macroName = NULL;
                                errorsInFile = 1;
                                continue;
                            }
                            
                        }
                        else
                        {
                            printf("ERROR : Line %d: Macro name %s already exists\n", lineNum, macroName);
                            free(macroName);
                            macroName = NULL;
                            errorsInFile = 1;
                            continue;
                        }
                    }
                    else
                    {
                        errorsInFile = 1;
                        printf("ERROR : Line %d: externous text found after macro definition \n", lineNum);
                    }
                }
                else
                {
                    printf("ERROR : Line %d: Macro name must start with a letter\n", lineNum);
                    errorsInFile = 1;
                    continue;
                }
            }
            else
            {
                printf("FATAL ERROR : Line %d: Cannot define a macro inside a macro\n", lineNum);
                errorsInFile = 1;
                continue;
            }
        }

        else if (insideMacro)
        {
            /*check if its the end of a maceo*/
            if (checkIfEndMacro(cursor))
            {
                cursor += endMacroWordLength;
                cursor = skipWhites(cursor);
                if (!checkIfExternousText(cursor))
                {
                    free(macroName);
                    macroName = NULL;
                    insideMacro = 0;
                    continue;
                }
                else
                {
                    printf("ERROR : Line %d: externous text found after end of macro command !! \n", lineNum);
                    errorsInFile = 1;
                    continue;
                }
            }
            /*elif check if the curreent line is already existing macro*/
            firstWord = getFirstWord(cursor);
            cursor += strlen(firstWord);
            if (searchMacroArray(ma, firstWord) && !checkIfExternousText(cursor))
            {
                /*see if its a macro*/
                writeMacroToFile(ma, firstWord, amFile);
                free(firstWord);
                continue;

            }
            else
            {
                insertLineToMacroArray(ma, macroName, line);
                free(firstWord);
                firstWord = NULL;
            }
        }
        else
        {
            firstWord = getFirstWord(cursor);
            if (searchMacroArray(ma, firstWord))
            {
                cursor += strlen(firstWord);
                if (!checkIfExternousText(cursor))
                {
                    writeMacroToFile(ma, firstWord, amFile);
                    free(firstWord);
                    continue;
                }
            }
            else
            {
                free(firstWord);
                fprintf(amFile, "%s", line);
            }
        }
    }

    /*========== END ITERATING ON FILE == == == = */
    if (!errorsInFile)
    {
        if (insideMacro)
        {
            writeMacroToFile(ma, macroName, amFile);
        }
    }

    free(line);
    freeMacroArray(ma);
    return errorsInFile;
}
