/**
 * Here I am going to put all of my coding related functions things
 *
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "../firstRun/enums.h"
#include "../globals/globalEnums.h"
#include "../firstRun/hashTable.h"
#include "../firstRun/lineStructs.h"
#include "../globals/bitField.h"
#include "intLinkedList.h"

/* == == == THESE FUNCTIONS BELOW WILL BE ADDED TO HELPERS= = == = */

static int writebfToFile(bitField *bf, FILE *f)
{
    char *b64;
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }
    if (f == NULL)
    {
        printf("file is null\n");
        return 0;
    }

    b64 = malloc(sizeof(char) * 3);
    bitfieldToBase64(bf, b64);
    fprintf(f, "%s\n", b64);
    free(b64);
    return 1;
}

static int writeToEntryOrExternFile(const char *fileName, const char *labelName, unsigned int memAddr)
{
    FILE *f;
    if (fileName == NULL)
    {
        printf("fileName is null\n");
        return 0;
    }
    if (labelName == NULL)
    {
        printf("labelName is null\n");
        return 0;
    }
    f = fopen(fileName, "a");
    if (f == NULL)
    {
        printf("Error opening file %s\n", fileName);
        return 0;
    }
    fprintf(f, "%s \t %d\n", labelName, memAddr);
    fclose(f);
    return 1;
}

/* == == == THESE FUNCTIONS BELOW WILL BE ADDED TO HELPERS= = == = */

/**
 * The function will take in lines of type linStructure and depending on their type and types of
 * tokens they hold, will put them into the correct data or actions arrays
 * This functions is "naive" - it assume that the lines have passed all error check beforehand
 * @param  ls is an initilized and error proofed linestruct
 * @param actions is a memory allocated actions bitfield array
 * @param actions is a memory allocated instructions bitfield array
 * @return void - wont return anything
 */
void codeIt(lineStructNode *ls, unsigned int(*IC), unsigned int *DC, labelTable *lt, labelTable *ltExterns, labelTable *ltEntries, const char *objectFileName, const char *externalFileName, const char *entriesFileName)
{
    FILE *f;
    intLinkedList *ILL;
    intLinkedListNode *node;
    bitField *bf;
    Token *tok;
    char *p;
    char *b64;
    /*int useFulInt =0;*/
    b64 = malloc(sizeof(char) * 3);
    
    bf = newBitField();

    if (getLSType(ls) == INSTRUCTION)
    {
        tok = getLSToken(ls, l_tok);
        p = (tok != NULL) ? getWord(tok) : NULL;
        if (p != NULL)
        {

            if (search(ltEntries, p))
            {

                writeToEntryOrExternFile(entriesFileName, p, (*IC) + (*DC) + 100);
            }
        }

        if (getSubType(getLSToken(ls, a_tok)) == DATA)
        {

            /*This goes into a function*/
            ILL = newIntLinkedList();
            p = getWord(getLSToken(ls, s_tok));
            extractNumbersFromString(p, ILL);
            node = getILLHead(ILL);
            f = fopen(objectFileName, "a");
            while (node != NULL)
            {
                codeNumberToBitField(bf, getNumberFromNode(node));
                bitfieldToBase64(bf, b64);
                writebfToFile(bf, f);
                initBitField(bf);
                (*DC)++;
                node = getILLNextNode(node);
            }
            freeIntLinkedList(ILL);
            fclose(f);
        }
        else if (getSubType(getLSToken(ls, a_tok)) == STRING)
        {
            p = getWord(getLSToken(ls, s_tok));
            if (p != NULL)
            {
                f = fopen(objectFileName, "a");
                while (*p != '\0')
                {
                    codeNumberToBitField(bf, (int)(*p));
                    bitfieldToBase64(bf, b64);
                    writebfToFile(bf, f);
                    (*DC)++;
                    p++;
                    initBitField(bf);
                }
                codeNumberToBitField(bf, 0);
                bitfieldToBase64(bf, b64);
                fprintf(f, "%s\n", b64);
                (*DC)++;
                fclose(f);
            }
        }
        else if (getSubType(getLSToken(ls, a_tok)) == ENTRY)
        {
            p = getWord(getLSToken(ls, s_tok)); /*get the name of ths source*/
            if (p != NULL)
            {
            }
        }
        else if (getType(getLSToken(ls, a_tok)) == EXTERN)
        {
        }
    }
    else if (getLSType(ls) == ACTION)
    {
        p = getLSToken(ls, l_tok) != NULL ? getWord(getLSToken(ls, l_tok)) : NULL;
        if (p != NULL)
        {

            if (search(ltEntries, p))
            {

                writeToEntryOrExternFile(entriesFileName, p, (*IC) + (*DC) + 100);
            }
        }

        /*We now code the first line containing maans and opcode*/
        if (codeLine(bf, ls))
        {
            bitfieldToBase64(bf, b64);
            f = fopen(objectFileName, "a");
            fprintf(f, "%s\n", b64);
            fclose(f);
            (*IC)++;
            initBitField(bf);
        }
        else
        {
            printf("Error: line was not coded\n");
        }
        /*If we have two operands*/
        if (getLSToken(ls, s_tok) != NULL && getLSToken(ls, d_tok) != NULL)
        {
            /*Meaning we have two operands*/

            /*If both operands are registers we code them into a single bitField using codeTwoRegisters*/
            if (getType(getLSToken(ls, s_tok)) == REGISTER && getType( getLSToken(ls, d_tok)) == REGISTER)
            {
                codeTwoRegisters(bf, getSubType(getLSToken(ls, s_tok)), getSubType(getLSToken(ls, d_tok)));
                f = fopen(objectFileName, "a");
                writebfToFile(bf, f);
                fclose(f);
                (*IC)++;
                initBitField(bf);
            }
            else
            {

                if (getType(getLSToken(ls, s_tok)) == LABEL)
                {

                    if (search(lt, getWord(getLSToken(ls, s_tok))))
                    {
                        /*If the label was found in the regular label table*/
                        codeLabelOperand(bf, searchAndGetMemAddr(lt, getWord(getLSToken(ls, s_tok))), 0);
                        f = fopen(objectFileName, "a");
                        writebfToFile(bf, f);
                        fclose(f);
                        (*IC)++;
                        initBitField(bf);
                    }
                    else if (search(ltExterns, getWord(getLSToken(ls, s_tok))))
                    {
                        codeLabelOperand(bf, searchAndGetMemAddr(ltExterns, getWord(getLSToken(ls, s_tok))), 1);
                        f = fopen(objectFileName, "a");
                        writebfToFile(bf, f);
                        fclose(f);

                        writeToEntryOrExternFile(externalFileName, getWord(getLSToken(ls, s_tok)), (*IC) + 100);
                        (*IC)++;
                        initBitField(bf);
                    }

                    else
                    {
                        printf("Error: label %s not found in labelTable or externs lableTable \n", getWord(getLSToken(ls, s_tok)));
                    }
                }
                else if (getType(getLSToken(ls, s_tok)) == REGISTER)
                {
                    /*usefulInt = getSubType(getLSToken(ls, s_tok));*/
                    codeOneRegister(bf, getSubType(getLSToken(ls, s_tok)), 1);
                    f = fopen(objectFileName, "a");
                    writebfToFile(bf, f);
                    fclose(f);

                    (*IC)++;
                    initBitField(bf);
                }
                else if (getType(getLSToken(ls, s_tok)) == NUMBER)
                {
                    /*it should have the number as its subtype*/
                    codeActionLineNumber(bf, getSubType(getLSToken(ls, s_tok)));
                    f = fopen(objectFileName, "a");
                    writebfToFile(bf, f);
                    fclose(f);
                    (*IC)++;
                    initBitField(bf);
                }
                else
                {
                    /* $ERROR MESSAGE TO ADD */

                    printf("Error: Invalid operand type\n");
                }
                if (getType(getLSToken(ls, d_tok)) == LABEL)
                {
                    if (search(lt, getWord(getLSToken(ls, d_tok))))
                    {
                        /*If the label was found in the regular label table*/
                        codeLabelOperand(bf, searchAndGetMemAddr(lt, getWord(getLSToken(ls, d_tok))), 0);
                        f = fopen(objectFileName, "a");
                        writebfToFile(bf, f);
                        fclose(f);
                        (*IC)++;
                        initBitField(bf);
                    }
                    else if (search(ltExterns, getWord(getLSToken(ls, d_tok))))
                    {
                        codeLabelOperand(bf, searchAndGetMemAddr(ltExterns, getWord(getLSToken(ls, d_tok))), 1);
                        f = fopen(objectFileName, "a");
                        writebfToFile(bf, f);
                        fclose(f);
                        writeToEntryOrExternFile(externalFileName, getWord(getLSToken(ls, d_tok)), (*IC) + 100);
                        (*IC)++;
                        initBitField(bf);
                    }

                    else
                    {
                        printf("Error: label %s not found in labelTable or externs lableTable \n", getWord(getLSToken(ls, s_tok)));
                    }
                }
                else if (getType(getLSToken(ls, d_tok)) == REGISTER)
                {
                    codeOneRegister(bf, getSubType(getLSToken(ls, d_tok)), 0);
                    f = fopen(objectFileName, "a");
                    writebfToFile(bf, f);
                    fclose(f);

                    (*IC)++;
                    initBitField(bf);
                }
                else if (getType(getLSToken(ls, d_tok)) == NUMBER)
                {
                    /*it should have the number as its subtype*/
                    codeActionLineNumber(bf, getSubType(getLSToken(ls, s_tok)));
                    f = fopen(objectFileName, "a");
                    writebfToFile(bf, f);
                    fclose(f);
                    (*IC)++;
                    initBitField(bf);
                }
            }
        }
        else if (getLSToken(ls, d_tok) != NULL && getLSToken(ls, s_tok) == NULL)
        {
            if (getType(getLSToken(ls, d_tok)) == LABEL)
            {
                if (search(lt, getWord(getLSToken(ls, d_tok))))
                {
                    /*If the label was found in the regular label table*/
                    codeLabelOperand(bf, searchAndGetMemAddr(lt, getWord(getLSToken(ls, d_tok))), 0);
                    f = fopen(objectFileName, "a");
                    writebfToFile(bf, f);
                    fclose(f);
                    (*IC)++;
                    initBitField(bf);
                }
                else if (search(ltExterns, getWord(getLSToken(ls, d_tok))))
                {
                    codeLabelOperand(bf, searchAndGetMemAddr(ltExterns, getWord(getLSToken(ls, d_tok))), 1);
                    f = fopen(objectFileName, "a");
                    writebfToFile(bf, f);
                    fclose(f);
                    writeToEntryOrExternFile(externalFileName, getWord(getLSToken(ls, d_tok)), (*IC) + 100);
                    (*IC)++;
                    initBitField(bf);
                }

                else
                {
                    printf("Error: label %s not found in labelTable or externs lableTable \n", getWord(getLSToken(ls, s_tok)));
                }
            }
            else if (getType(getLSToken(ls, d_tok)) == REGISTER)
            {
                initBitField(bf);
                codeOneRegister(bf, getSubType(getLSToken(ls, d_tok)), 1);
                f = fopen(objectFileName, "a");
                writebfToFile(bf, f);
                fclose(f);

                (*IC)++;
                initBitField(bf);
            }
            else if (getType(getLSToken(ls, d_tok)) == NUMBER)
            {
                initBitField(bf);
                codeActionLineNumber(bf, getSubType(getLSToken(ls, d_tok)));
                f = fopen(objectFileName, "a");
                writebfToFile(bf, f);
                fclose(f);
                (*IC)++;
                initBitField(bf);
            }
            else
            {
                /* $ERROR MESSAGE TO ADD */
                printf("Error: Invalid operand type\n"); /*This is for debugging only*/
            }
        }
        else if (getSubType(getLSToken(ls, a_tok)) == stop || getSubType(getLSToken(ls, a_tok)) == rts)
        {
            /*do nothing as the line was already coded*/
        }

        else
        {
            /*This is an impossible scenario that shoulve been cought in error handling
            because whenever there is a source operand there is also a dest operand and it is not vice versa*/
            printf("Error: Invalid operand type\n"); /*This is for debugging only*/
        }
    }

    free(bf);
    free(b64);
}
