#include <stdio.h>
#include <stdlib.h>
#include "token.h"

struct lineStructNode
{
    Token *label , *action , *source, *dest;
    int type;
    int rowNum;
    struct lineStructNode *next;
};

struct lineStructArray
{
    struct lineStructNode *head;
    struct lineStructNode *tail;
    int size;
};



/*========LINESTRUCT FUNCTIONS ====== */
struct lineStructArray *newLineStructArray(void)
{
    struct lineStructArray *lsArray = (struct lineStructArray*)malloc(sizeof(struct lineStructArray));
    if (lsArray == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    lsArray->head = NULL;
    lsArray->tail = NULL;
    lsArray->size = 0;
    return lsArray;
}
struct lineStructNode *newLineStructNode(void)
{
    struct lineStructNode *lsNode = (struct lineStructNode*)malloc(sizeof(struct lineStructNode));
    if (lsNode == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    lsNode->label = NULL;
    lsNode->action = NULL;
    lsNode->source = NULL;
    lsNode->dest = NULL;
    lsNode->type = 0;
    lsNode->rowNum = 0;
    lsNode->next = NULL;
    return lsNode;
}

int insertLSNodeToArray(struct lineStructArray *lsArray , struct lineStructNode *lsNode)
{
    if (lsArray == NULL)
    {
        printf("lineStructArray is null\n");
        return 0 ;
    }
    if (lsNode == NULL)
    {
        printf("lineStructNode is null\n");
        return 0 ;
    }
    if (lsArray->head == NULL)
    {
        lsArray->head = lsNode;
        lsArray->tail = lsNode;
        lsArray->size++;
        return 1;
    }
    lsArray->tail->next = lsNode;
    lsArray->tail = lsNode;
    lsArray->size++;
    return 1; 
}

int setLSToken(struct lineStructNode *ls , Token *tok ,const int type)
{
    if (ls == NULL)
    {
        printf("lineStructNode is null\n");
        return 0 ;
    }
    if (tok == NULL)
    {
        /*printf("token is null\n");*/
        return 0 ;
    }
    switch (type)
    {
    case l_tok:
        ls->label = tok;
        break;
    case (a_tok):
        ls->action = tok;
        break;
    case (s_tok):
        ls->source = tok;
        break;
    case (d_tok):
        ls->dest = tok;
        break;
    default:
    printf("Error in insertTokenToLS: type is not valid\n");
        return 0;
        break;
    }
    return 1;
}

Token *getLSToken(struct lineStructNode *ls , const int type)
{
    if (ls == NULL)
    {
        printf("lineStructNode is null\n");
        return NULL ;
    }
    switch (type)
    {
    case l_tok:
        return ls->label;
        break;
    case (a_tok):
        return ls->action;
        break;
    case (s_tok):
        return ls->source;
        break;
    case (d_tok):
        return ls->dest;
        break;
    default:
    printf("Error in insertTokenToLS: type is not valid\n");
        break;
    }
    return NULL;
}

int setLSRowNum(struct lineStructNode *lsNode , const int rowNum)
{
    if (lsNode == NULL)
    {
        printf("lineStructNode is null\n");
        return 0 ;
    }
    lsNode->rowNum = rowNum;
    return 1;
}
int setNextLSNode(struct lineStructNode *lsNode , struct lineStructNode *next)
{
    if (lsNode == NULL)
    {
        printf("lineStructNode is null\n");
        return 0 ;
    }
    lsNode->next = next;
    return 1;
}

struct lineStructNode *getNextLSNode(struct lineStructNode *lsNode)
{
    if (lsNode == NULL)
    {
        printf("lineStructNode is null\n");
        return NULL ;
    }
    return lsNode->next;
}

int freeLineStructNode(struct lineStructNode **lsNode)
{
    if ((*lsNode) == NULL)
    {
        printf("lineStructNode is null\n");
        return 0 ;
    }
    if ((*lsNode)->label != NULL)
    {
        freeToken(&((*lsNode)->label));
    }
    if ((*lsNode)->action != NULL)
    {
        freeToken(&((*lsNode)->action));
    }
    if ((*lsNode)->source != NULL)
    {
        freeToken(&((*lsNode)->source));
    }
    if ((*lsNode)->dest != NULL)

    {
        freeToken(&(((*lsNode)->dest)));
    }

    free((*lsNode));
    (*lsNode) = NULL;
    return 1;
}
int freeLineStructArray(struct lineStructArray **lsArray)
{
    struct lineStructNode *lsNode , *lsNodeNext;
    if ((*lsArray) == NULL)
    {
        printf("\n");
        return 0 ;
    }
    lsNode = (*lsArray)->head;
    while (lsNode != NULL)
    {
        lsNodeNext = lsNode->next;
        freeLineStructNode(&lsNode);
        lsNode = lsNodeNext;
    }
    free((*lsArray));
    (*lsArray) = NULL;
    return 1;
}

struct lineStructNode *getLSNodeByIndex(struct lineStructArray *lsArray , int index)
{
    struct lineStructNode *lsNode;
    int i;
    if (lsArray == NULL)
    {
        printf("lineStructArray is null\n");
        return NULL ;
    }
    if (index < 0 || index >= lsArray->size)
    {
        printf("index out of bounds\n");
        return NULL ;
    }
    lsNode = lsArray->head;
    for (i = 0; i < index; i++)
    {
        lsNode = lsNode->next;
    }
    return lsNode;
}

struct lineStructNode *getLSNodeTail(struct lineStructArray *lsArray)
{
    if (lsArray == NULL)
    {
        printf("lineStructArray is null\n");
        return NULL ;
    }
    return lsArray->tail;
}

struct lineStructNode *getLSNodeHead(struct lineStructArray *lsArray)
{
    if (lsArray == NULL)
    {
        printf("lineStructArray is null\n");
        return NULL ;
    }
    return lsArray->head;
}


int getLSType(struct lineStructNode *lsNode)
{
    if (lsNode == NULL)
    {
        printf("lineStructNode is null\n");
        return -1;
    }
    return lsNode->type;
}


int getLsRowNum(struct lineStructNode *lsNode)
{
    if (lsNode == NULL)
    {
        printf("lineStructNode is null\n");
        return -1;
    }
    return lsNode->rowNum;
}



int setLsType(struct lineStructNode *lsNode , int type)
{
    if (lsNode == NULL)
    {
        printf("lineStructNode is null\n");
        return 0;
    }
    lsNode->type = type;
    return 1;
}



/**
 * This function will create a  new linestruct Node and insert it to the end of the array and then return it
 * @param lsArray - a pointer to a lineStructArray
 * @param lineNumber - the line number of the lineStructNode
 * @return a pointer to the new lineStructNode
 * @return NULL if lsArray is NULL
 * @return NULL if memory allocation failed
 */
struct lineStructNode *createNewLineStructNode(struct lineStructArray *lsArray , int lineNumber)
{
    struct lineStructNode *lsNode;
    lsNode = newLineStructNode();
    if (lsNode == NULL)
    {
        printf("memory allocation failed\n");
        return NULL;
    }
    setLSRowNum(lsNode , lineNumber);
    insertLSNodeToArray(lsArray , lsNode);
    return lsNode;
}




/**
 * the function will print linestruct along with subtypes and types of all of its tokens
*/
void printLineStruct(struct lineStructNode *ls)
{
    Token *label, *action, *source, *dest;
    
    if (ls == NULL)
    {
        printf("lineStructNode is null\n");
        return;
    }
    label = getLSToken(ls , l_tok);
    action = getLSToken(ls , a_tok);
    source = getLSToken(ls , s_tok);
    dest = getLSToken(ls , d_tok);
    printf("======LINESTRUCT IS:======\n");
    printf("label: ");
    if (label != NULL)
    {
        printf("label : %s, type: %d, subType: %d\n", getWord(label), getType(label), getSubType(label));

    }
    else
    {
        printf("NULL\n");
    }
    printf("action: ");
    if (action != NULL)
    {
        printf("word : %s, type: %d, subType: %d\n", getWord(action), getType(action), getSubType(action));

    }
    else
    {
        printf("NULL\n");
    }
    printf("source: ");
    if (source != NULL)
    {
        printf("word : %s, type: %d, subType: %d\n", getWord(source), getType(source), getSubType(source));

    }
    else
    {
        printf("NULL\n");
    }
    printf("dest: ");
    if (dest != NULL)
    {
        printf("word : %s, type: %d, subType: %d\n", getWord(dest), getType(dest), getSubType(dest));

    }
    else
    {
        printf("NULL\n");
    }
    printf("type: %d\n", getLSType(ls));
    printf("rowNum: %d\n", getLsRowNum(ls));
    printf("next: %p\n", (void *)ls->next);
    printf("\n");
}
