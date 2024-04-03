

/*#include "preAssembler/PreAssembler.h"*/
#include "preAssembler/PreAssembler2.h"

#include "firstRun/helperFunctions.h"
#define INITSIZE 100
#include "firstRun/hashTable.h"
#include "firstRun/lineStructs.h"
#include "globals/helperFuncs.h"
#include "secondRun/codingFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include "globals/bitField.h"

int main(int argc, char const *argv[])
{
    const char *fileName;
    char  *amFileName, *objFileName, *extFileName, *entFileName, *asFileName;
    FILE *f, *amFile;
    unsigned int IC = 100, DC = 0;
    labelTable *lt, *ltExterns, *ltEntries;
    size_t i;

    unsigned int firtRunFailed = 0;
    lineStructArray *lsa, *lsd;
    lineStructNode *lsn;

    lsd = NULL;
    lsa = NULL;
    lt = NULL;
    ltExterns = NULL;
    ltEntries = NULL;
    lsn = NULL;
    f = NULL;
    fileName = NULL;
    amFileName = NULL;
    objFileName = NULL;
    extFileName = NULL;
    entFileName = NULL;
    asFileName = NULL;

    if (argc < 2)
    {
        printf("Invalid number of arguments\n");
        exit(EXIT_FAILURE);
    }

    for ( i = 1; i < argc; i++)
    {
        fileName = argv[i];
        asFileName = concat(fileName, ".as");

        f = fopen(asFileName, "r");
        if (f == NULL)
        {
            printf("File does not exist\n");
            exit(EXIT_FAILURE);
        }

        /* =====PREASSEMBLER=====*/
        amFileName = concat(fileName, ".am");
        amFile = fopen(amFileName, "a");
        if (!preAssembler(f, amFile))
        {

            fclose(amFile);
            fclose(f);

            f = fopen(amFileName, "r");
            if (f == NULL)
            {
                exit(EXIT_FAILURE);
            }

            lt = newTable(2);
            ltExterns = newTable(2);
            ltEntries = newTable(2);
            lsa = newLineStructArray();
            lsd = newLineStructArray();
            firtRunFailed = firstRun(f, &IC, &DC, &lt, &ltExterns, &ltEntries, lsa, lsd);
            if (firtRunFailed)
            {
                printf("First run failed\n");
            }
            else
            {

                IC = 0;
                DC = 0;
                lsn = getLSNodeHead(lsa);
                extFileName = concat(fileName, ".ext");
                entFileName = concat(fileName, ".ent");
                objFileName = concat(fileName, ".ob");

                while (lsn != NULL)
                {
                    codeIt(lsn, &IC, &DC, lt, ltExterns, ltEntries, objFileName, extFileName, entFileName);
                    lsn = getNextLSNode(lsn);
                }
                lsn = getLSNodeHead(lsd);
                while (lsn != NULL)
                {
                    codeIt(lsn, &IC, &DC, lt, ltExterns, ltEntries, objFileName, extFileName, entFileName);
                    lsn = getNextLSNode(lsn);
                }
                free(extFileName);
                free(entFileName);
                free(objFileName);
            }
        }
        else
        {
            remove(amFileName);
            printf("Preassembler failed\n");

        }
        
        freeTable(&lt);
        freeTable(&ltExterns);
        freeTable(&ltEntries);
        freeLineStructArray(&lsa);
        freeLineStructArray(&lsd);
        
        free(asFileName);

        free(amFileName);

        fclose(f);
    }

    return 0;
}
