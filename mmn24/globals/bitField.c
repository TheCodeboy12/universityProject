#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../secondRun/intLinkedList.h"
#include "../globals/criticalNumbers.h"
#include "../firstRun/enums.h"
#include "../globals/globalEnums.h"
#include "../firstRun/lineStructs.h"
#include "../firstRun/helperFunctions.h"

struct bitField
{
    unsigned int bit1 : 1 ;
    unsigned int bit2 : 1 ;
    unsigned int bit3 : 1 ;
    unsigned int bit4 : 1 ;
    unsigned int bit5 : 1 ;
    unsigned int bit6 : 1 ;
    unsigned int bit7 : 1 ;
    unsigned int bit8 : 1 ;
    unsigned int bit9 : 1 ;
    unsigned int bit10 : 1 ;
    unsigned int bit11 : 1 ;
    unsigned int bit12 : 1 ;
};

/*I need function to support this bitfield*/

struct bitField *newBitField(void)
{
    struct bitField *bf;
    bf = malloc(sizeof(struct bitField));
    if (bf == NULL)
    {
        printf("Error allocating memory for bitfield\n");
        return NULL;
    }
    bf->bit1 = 0;
    bf->bit2 = 0;
    bf->bit3 = 0;
    bf->bit4 = 0;
    bf->bit5 = 0;
    bf->bit6 = 0;
    bf->bit7 = 0;
    bf->bit8 = 0;
    bf->bit9 = 0;
    bf->bit10 = 0;
    bf->bit11 = 0;
    bf->bit12 = 0;
    return bf;
}



int initBitField(struct bitField *bf)
{
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }
    bf->bit1 = 0;
    bf->bit2 = 0;
    bf->bit3 = 0;
    bf->bit4 = 0;
    bf->bit5 = 0;
    bf->bit6 = 0;
    bf->bit7 = 0;
    bf->bit8 = 0;
    bf->bit9 = 0;
    bf->bit10 = 0;
    bf->bit11 = 0;
    bf->bit12 = 0;
    return 1;
}
void printBitField(struct bitField *bf)
{
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return;
    }
    printf("%d", bf->bit12);
    printf("%d", bf->bit11);
    printf("%d", bf->bit10);
    printf("%d", bf->bit9);
    printf("%d", bf->bit8);
    printf("%d", bf->bit7);
    printf("%d", bf->bit6);
    printf("%d", bf->bit5);
    printf("%d", bf->bit4);
    printf("%d", bf->bit3);
    printf("%d", bf->bit2);
    printf("%d", bf->bit1);
    printf("\n");
}

/* CODING FUNCTIONS*/

int codeNumberToBitField(struct bitField *b , const int num)
{
    int n = num;
    if (b == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }

    if (n < 0 )
    {
        n+=(MAX_UNSIGNED(MAX_BITS_DATA_NUMBER) +1);
    }
    b->bit1 = num & 1;
    b->bit2 = (num >> 1) & 1;
    b->bit3 = (num >> 2) & 1;
    b->bit4 = (num >> 3) & 1;
    b->bit5 = (num >> 4) & 1;
    b->bit6 = (num >> 5) & 1;
    b->bit7 = (num >> 6) & 1;
    b->bit8 = (num >> 7) & 1;
    b->bit9 = (num >> 8) & 1;
    b->bit10 = (num >> 9) & 1;
    b->bit11 = (num >> 10) & 1;
    b->bit12 = (num >> 11) & 1;
    return 1;
}


int codeTwoRegisters(struct bitField *bf , int sourceReg , int destReg)
{
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }
    if (sourceReg < 0 || sourceReg > 7)
    {
        printf("sourceReg is not valid\n");
        return 0;
    }
    if (destReg < 0 || destReg > 7)
    {
        printf("destReg is not valid\n");
        return 0;
    }
    /*This is for ARE*/
    bf->bit1 =0;
    bf->bit2 =0;

    /*Source register*/
    bf->bit8 = ((sourceReg) & 1) ? 1 : 0 ;
    bf->bit9 = ((sourceReg) & 2) ? 1 : 0 ;
    bf->bit10 = ((sourceReg) & 4) ? 1 : 0 ;
    bf->bit11 = ((sourceReg) & 8) ? 1 : 0 ;
    bf->bit12 = ((sourceReg) & 16) ? 1 : 0 ;
   
    /*dest register*/
    bf->bit3 = ((destReg) & 1) ? 1 : 0 ;
    bf->bit4 = ((destReg) & 2) ? 1 : 0 ;
    bf->bit5 = ((destReg) & 4) ? 1 : 0 ;
    bf->bit6 = ((destReg) & 8) ? 1 : 0 ;
    bf->bit7 = ((destReg) & 16) ? 1 : 0 ;
    return 1;
}

int codeActionLineNumber(struct bitField *bf , int num) 
{
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }
    
    if ((num < MIN_SIGNED(MAX_BITS_ACTION_NUMBER) ) || num > MAX_SIGNED(MAX_BITS_ACTION_NUMBER))
    {
        printf("num is not valid\n");
        return 0;
    }

    
    /*This is for ARE*/
    bf->bit1 =0;
    bf->bit2 =0;

    /*code the number*/
    bf->bit3  = (num >> 0)  & 1;
    bf->bit4  = (num >> 1)  & 1;
    bf->bit5  = (num >> 2)  & 1;
    bf->bit6  = (num >> 3)  & 1;
    bf->bit7  = (num >> 4)  & 1;
    bf->bit8  = (num >> 5)  & 1;
    bf->bit9  = (num >> 6)  & 1;
    bf->bit10 = (num >> 7)  & 1;
    bf->bit11 = (num >> 8)  & 1;
    bf->bit12 = (num >> 9)  & 1;
    return 1;
}

int codeOneSourceOperand(struct bitField *bf , int sourceSubType)
{

    if (bf == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }
    
    /*This is for ARE*/
    bf->bit1 =0;
    bf->bit2 =0;

    /*Source register*/
    bf->bit8 = ((sourceSubType) & 1) ? 1 : 0 ;
    bf->bit9 = ((sourceSubType) & 2) ? 1 : 0 ;
    bf->bit10 = ((sourceSubType) & 4) ? 1 : 0 ;
    bf->bit11 = ((sourceSubType) & 8) ? 1 : 0 ;
    bf->bit12 = ((sourceSubType) & 16) ? 1 : 0 ;

    return 1;
}


int codeOneRegister(struct bitField *bf , int reg, const int isSource)
{
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }
    if (reg < 0 || reg > 7)
    {
        printf("reg is not valid\n");
        return 0;
    }
   
    /*This is for ARE*/
    bf->bit1 =0;
    bf->bit2 =0;

    if(isSource)
    {
        /*Source register*/
        bf->bit8 = ((reg) & 1) ? 1 : 0 ;
        bf->bit9 = ((reg) & 2) ? 1 : 0 ;
        bf->bit10 = ((reg) & 4) ? 1 : 0 ;
        bf->bit11 = ((reg) & 8) ? 1 : 0 ;
        bf->bit12 = ((reg) & 16) ? 1 : 0 ;
        return 1;
    }
    else
    {
        /*dest register*/
        bf->bit3 = ((reg) & 1) ? 1 : 0 ;
        bf->bit4 = ((reg) & 2) ? 1 : 0 ;
        bf->bit5 = ((reg) & 4) ? 1 : 0 ;
        bf->bit6 = ((reg) & 8) ? 1 : 0 ;
        bf->bit7 = ((reg) & 16) ? 1 : 0 ;
        return 1;

    }
}

int codeLabelOperand (struct bitField *bf , const unsigned int lableAddr, unsigned int external)
{
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }
    if (external)
    {
        /*Code ARE as external*/
        bf->bit1 =1;
        bf->bit2 =0;
    }
    else
    {
        /*Code ARE as relocatable*/
        bf->bit1 =0;
        bf->bit2 =1;
    }
    /*code the lable addrs*/
    bf->bit3  = (lableAddr >> 0)  & 1;
    bf->bit4  = (lableAddr >> 1)  & 1;
    bf->bit5  = (lableAddr >> 2)  & 1;
    bf->bit6  = (lableAddr >> 3)  & 1;
    bf->bit7  = (lableAddr >> 4)  & 1;
    bf->bit8  = (lableAddr >> 5)  & 1;
    bf->bit9  = (lableAddr >> 6)  & 1;
    bf->bit10 = (lableAddr >> 7)  & 1;
    bf->bit11 = (lableAddr >> 8)  & 1;
    bf->bit12 = (lableAddr >> 9)  & 1;
    return 1;
}


int intToFullBitField(struct bitField *bf , int num)
{
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }
    if (num < MIN_SIGNED(MAX_BITS_DATA_NUMBER) || num > MAX_SIGNED(MAX_BITS_DATA_NUMBER) )
    {
        printf("num is not valid\n");
        return 0;
    }
    /*This is for ARE*/
    bf->bit1 =0;
    bf->bit2 =0;

    /*code the number*/
    bf->bit3  = (num >> 0)  & 1;
    bf->bit4  = (num >> 1)  & 1;
    bf->bit5  = (num >> 2)  & 1;
    bf->bit6  = (num >> 3)  & 1;
    bf->bit7  = (num >> 4)  & 1;
    bf->bit8  = (num >> 5)  & 1;
    bf->bit9  = (num >> 6)  & 1;
    bf->bit10 = (num >> 7)  & 1;
    bf->bit11 = (num >> 8)  & 1;
    bf->bit12 = (num >> 9)  & 1;
    return 1;
}


int codeLine(struct bitField *bf , lineStructNode *ls)
{

    Token *source , *dest;
    int sourceAddr , destAddr , lsSubType;
    source = getLSToken(ls , s_tok);
    dest = getLSToken(ls , d_tok);
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return 0;
    }

    if (getLSType(ls) != ACTION)
    {
        return 0;
    }
    /*This is for ARE*/
    
    bf->bit1 =0;
    bf->bit2 =0;

    lsSubType = getSubType(getLSToken(ls , a_tok));
    /*Insert the opCode bits*/
    bf->bit6 =  ((lsSubType) & 1) ? 1 : 0 ;
    bf->bit7 =  ((lsSubType) & 2) ? 1 : 0 ;
    bf->bit8 =  ((lsSubType) & 4) ? 1 : 0 ;
    bf->bit9 =  ((lsSubType) & 8) ? 1 : 0 ;
    

    source= getLSToken(ls , s_tok);
    if (source != NULL) {
        sourceAddr = calcOpAddr(source);
        bf->bit10 = ((sourceAddr) & 1) ? 1 : 0 ;
        bf->bit11 = ((sourceAddr) & 2) ? 1 : 0 ;
        bf->bit12 = ((sourceAddr) & 4) ? 1 : 0 ;
        
    }
    dest = getLSToken(ls , d_tok);
    if (dest != NULL) 
    {
        destAddr = calcOpAddr(dest);
        bf->bit3 = ((destAddr) & 1) ? 1 : 0 ;
        bf->bit4 = ((destAddr) & 2) ? 1 : 0 ;
        bf->bit5 = ((destAddr) & 4) ? 1 : 0 ;
    }

    

    return 1;
}


static char getBase64For6Bits(unsigned int bits ) {
    const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    return base64chars[bits];
}

char *bitfieldToBase64(struct bitField *bf , char *encoded) {
    unsigned int first6Bits ,second6Bits;
    if (bf == NULL)
    {
        printf("bitField is null\n");
        return NULL;
    }
    if (encoded == NULL)
    {
        printf("encoded is null\n");
        return NULL;
    }
    if (sizeof(encoded) < 3)
    {
        printf("encoded is not big enough\n");
        return NULL;
    }
    
    
    
    first6Bits = bf->bit1 | (bf->bit2 << 1) | (bf->bit3 << 2) | (bf->bit4 << 3) | 
                 (bf->bit5 << 4) | (bf->bit6 << 5);

    second6Bits = bf->bit7 | (bf->bit8 << 1) | (bf->bit9 << 2) | (bf->bit10 << 3) | 
                               (bf->bit11 << 4) | (bf->bit12 << 5);

   
    if (!encoded) return NULL;

    encoded[0] = getBase64For6Bits(second6Bits);
    encoded[1] = getBase64For6Bits(first6Bits);
    encoded[2] = '\0';


    return encoded;
}
