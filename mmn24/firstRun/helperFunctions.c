#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../globals/globalConstants.h"
#include "../globals/helperFuncs.h"
#include "../globals/globalEnums.h"
#include "../globals/criticalNumbers.h"
#include "./helperFunctions.h"

#include "./enums.h"
#include "./firstRunConstants.h"
#include "../globals/helperFuncs.h"
#include "lineStructs.h"




int checkIfRegister(const char *buffer)
{
  int i;
  for (i = 0; i < NUM_REGS; i++)
  {
    if (strcmp(buffer, registersStrings[i]) == 0 || strcmp(buffer , registersStrings[i] + 1) == 0)
    {
      return i;
    }
  }
  return -1;
}

/**
 * This function takes a token and tells me what its "maan" is
 * @param tok - a pointer to a token
 * @return int - the maan of the token
 */

unsigned int calcOpAddr(struct Token *tok)
{
  if (getType(tok) == LABEL)
  {
    return 3;
  }
  else if (getType(tok) == NUMBER)
  {
    return 1;
  }
  else if (getType(tok) == REGISTER)
  {
    return 5;
  }
  return 0;
}

int checkActionLinestructsForErrors(lineStructNode *ls)
{

  int actionSubtype, sourceAddr, destAddr;
  Token *source, *dest;
  if (ls == NULL)
  {
    printf("lineStruct is null\n");
    return 1;
  }

  actionSubtype = getSubType(getLSToken(ls, a_tok));
  if (actionSubtype == mov ||
      actionSubtype == cmp ||
      actionSubtype == add ||
      actionSubtype == sub)
  {
    source = getLSToken(ls, s_tok);
    dest = getLSToken(ls, d_tok);
    sourceAddr = calcOpAddr(source);
    destAddr = calcOpAddr(dest);
    if (sourceAddr == 3 || sourceAddr == 1 || sourceAddr == 5)
    {
      if (destAddr == 3 || destAddr == 5)
      {
        return 0;
      }
      else
      {
        printf("Error in line %d: destination operand type mismatch - expected register or label but got number\n", getLsRowNum(ls));
        return 1;
      }
    }
    return 0;
  }
  else if (actionSubtype == lea)
  {

    source = getLSToken(ls, s_tok);
    dest = getLSToken(ls, d_tok);
    sourceAddr = calcOpAddr(source);
    destAddr = calcOpAddr(dest);
    if (sourceAddr == 3)
    {
      if (destAddr == 3 || destAddr == 5)
      {
        return 0;
      }
      else
      {
        printf("Error in line %d: destination operand type mismatch - expected register or label but got number\n", getLsRowNum(ls));
        return 1;
      }
    }
    else
    {
      printf("Error in line %d: source operand type mismatch - expected label but got number or register\n", getLsRowNum(ls));
      return 0;
    }
  }

  else if (
      actionSubtype == not ||
      actionSubtype == clr ||
      actionSubtype == inc ||
      actionSubtype == dec ||
      actionSubtype == jmp ||
      actionSubtype == bne ||
      actionSubtype == red ||
      actionSubtype == jsr)
  {
    dest = getLSToken(ls, d_tok);
    destAddr = calcOpAddr(dest);
    if (destAddr == 3 || destAddr == 5)
    {
      return 0;
    }
    else
    {
      printf("Error in line %d: destination operand type mismatch - expected register or label but got number\n", getLsRowNum(ls));
      return 1;
    }
  }
  else if (actionSubtype == prn)
  {
    dest = getLSToken(ls, d_tok);
    destAddr = calcOpAddr(dest);
    if (destAddr == 3 || destAddr == 1 || destAddr == 5)
    {
      return 0;
    }
    else
    {
      printf("Error in line %d: destination operand type mismatch - expected register or label or number but got something else\n", getLsRowNum(ls));
      return 1;
    }
  }
  else
  {
    printf("Error in line %d: unknown action\n", getLsRowNum(ls));
    return 1;
  }
}

int checkNumbers(char *buffer, unsigned int *errorFound, int rowNum)
{
  char *p;
  int insidePositiveOrNegative = 0;
  int num = 0, sign=1;
  p = buffer;
  while (*p != '\0' && *p != '\n')
  {
    p = skipWhites(p);
    if (*p == '-' || *p == '+')
    {
      if (insidePositiveOrNegative == 1)
      {
        *errorFound = 1;
        printf("Error in line %d: two continues signs\n", rowNum);
        return 1;
      }
      else
      {
        if (*p == '-')
          sign = -1;
        insidePositiveOrNegative = 1;
      }
    }
    else if (isdigit(*p))
    {
      insidePositiveOrNegative = 1;
      num = num * 10 + (*p - '0');
    }
    else if (*p == ',')
    {
      if (insidePositiveOrNegative == 0)
      {
        *errorFound = 1;
        printf("Error in line %d: two continues commas\n", rowNum);
        return 1;
      }

      else
        insidePositiveOrNegative = 0;
      num = num * sign;
      if (num > (MAX_SIGNED(MAX_BITS_DATA_NUMBER)) || num < MIN_SIGNED(MAX_BITS_DATA_NUMBER) )
      {
        *errorFound = 1;
        printf("Error in line %d: One of the numbers is too big and wont fit 12 bits\n", rowNum);
        return 1;
      }

      num = 0;
      sign = 1;
    }

    else
    {
      *errorFound = 1;
      printf("Error in line %d: illegal charecter found in numbers operands\n", rowNum);
      return 1;
    }

    p++;
    if (num > (MAX_SIGNED(MAX_BITS_DATA_NUMBER)) || num < MIN_SIGNED(MAX_BITS_DATA_NUMBER) )
      {
        *errorFound = 1;
        printf("Error in line %d: One of the numbers is too big and wont fit 12 bits\n", rowNum);
        return 1;
      }
  }
  return 0;
}
