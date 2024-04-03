#include <stdio.h>
#include "hashTable.h"
#include <stdlib.h>
#include <string.h>
#include "../globals/hashFunction.h"
#define LOAD_FACTOR 0.7



struct labelTableNode
{
    char *label;
    size_t memAddr;
    struct labelTableNode *next;

};

struct labelTable
{
    struct labelTableNode **arr;
    size_t numOfElements;
    unsigned int capacity;

};


static unsigned int checkIfExceedsLoadFactor(struct labelTable *lt)
{
    if (lt ==NULL)
    {
        printf("Label is empty\n");
        return 0;
    }
    if (lt->numOfElements / lt->capacity >LOAD_FACTOR)
    {
        return 1;
    }
    else return 0;
    
}

/**
 * This function will check if the hashtable needs resizing depending on its load factor and capacity
 * @return 1 if it needs to
 * @return 0 if it does not
*/
static unsigned int checkIfNeedResizing(struct labelTable *lt)
{
    if (lt ==NULL)
    {
        printf("Label is empty\n");
        return 0;
    }
    if (checkIfExceedsLoadFactor(lt) || lt->numOfElements +1 > lt->capacity)
    {
        return 1;
    }
    else return 0;
    /*The table will need resizing if 
    1. The table exceeds its capacity
    2. The table's load factor will go above its limit*/
}




static struct labelTable *resizeRehash(struct labelTable *lt)
{
    struct labelTable *new;
    size_t i;
    struct labelTableNode *p;
    if (lt == NULL)
    {
        return NULL;
    }
    new = newTable(lt->capacity * 2);
    for (i = 0; i < lt->capacity; i++)
    {
        p = lt->arr[i];
        while (p != NULL)
        {
            insertLabelNode(&new , p->label , p->memAddr);
            p=p->next;
        }
    }
    freeTable(&lt);
    return new;
}




/* ============New FUNCTIONS ==============*/
struct labelTableNode *newTlNode(void)
{
    struct labelTableNode *node;

    node = (struct labelTableNode*)(malloc(sizeof(labelTableNode)));
    if (node ==NULL)
    {
        return NULL;
    }
    node->memAddr=0;
    node->next=NULL;
    node->label =NULL;
    return node;
}

struct labelTable *newTable(const size_t initCapacity)
{
    struct labelTable *lt;
    size_t i;
    lt= (struct labelTable*)malloc(initCapacity* sizeof(labelTable));
    if (lt==NULL)
    {
        printf("memory allocation failed\n");
        return NULL;
    }

    lt->arr = malloc(initCapacity * sizeof(labelTableNode));
    if (lt->arr == NULL)
    {
        printf("memory allocation failed\n");
        return NULL;
    }
   
    

    lt->capacity=initCapacity;
    lt->numOfElements=0;
    for ( i = 0; i < lt->capacity; i++)
    {
        lt->arr[i] = NULL;
    }
    return lt;
}

int freeTable(struct labelTable **lt)
{
    size_t i;
    struct labelTableNode *p , *q;

    if ((*lt) == NULL)
    {
        return 0;
    }

    for (i = 0; i < (*lt)->capacity; i++)
    {
        p = (*lt)->arr[i];
        while (p != NULL)
        {
            q = p;
            p = p->next;

            free(q->label);
            free(q);
        }
    }
    free((*lt)->arr);
    free(*lt);
    *lt = NULL;  /* Set the pointer to NULL to avoid any dangling references.*/
    return 1;
}


int insertLabelNode(struct labelTable **lt , char *label , unsigned int memAddr)
{
    size_t index;
    struct labelTableNode *new;
    struct labelTable *newT;
    if ((*lt) == NULL)
    {
        /*printf("labelTable is null\n");*/
        return 0 ;
    }
    if (label == NULL)
    {
        printf("label is null\n");
        return 0 ;
    }
    if (memAddr < 0)
    {
        printf("memAddr is negative\n");
        return 0 ;
    }
    if (checkIfNeedResizing((*lt)))
    {
        newT =  resizeRehash((*lt));
        if (newT == NULL)
        {
            printf("resizing failed\n");
            return 0;
        }
        (*lt) = newT;
    }
    index = hash(label , (*lt)->capacity);
    new = newTlNode();
    new->label = (char*)malloc(strlen(label) + 1);
    if (new->label == NULL)
    {
        printf("memory allocation failed\n");
        return 0;
    }
    new->label[strlen(label)] = '\0';
    strcpy(new->label , label);
    new->memAddr = memAddr;
    new->next = (*lt)->arr[index];
    (*lt)->arr[index] = new;
    (*lt)->numOfElements++;
    return 1;
}

int search(struct labelTable *lt , char * word)
{
    size_t index;
    struct labelTableNode *p;
    if (lt == NULL)
    {
        return 0;
    }
    index = hash(word , lt->capacity);
    p = lt->arr[index];

    while (p != NULL)
    {
        if (strcmp (word , p->label) == 0)
        {
            return 1;
        }
        p=p->next;
    }

    return 0;
}

struct labelTableNode *searchAndGetNode(struct labelTable *lt , char * word)
{
    size_t index;
    struct labelTableNode *p;
    if (lt == NULL)
    {
        return NULL;
    }
    index = hash(word , lt->capacity);
    p = lt->arr[index];

    while (p != NULL)
    {
        if (strcmp (word , p->label) == 0)
        {
            return p;
        }
        p=p->next;
    }

    return NULL;
}

char *getLableFromNode(struct labelTableNode *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    return node->label;
}

unsigned int getMemAddrFromNode(struct labelTableNode *node)
{
    if (node == NULL)
    {
        return -1;
    }
    return node->memAddr;
}

unsigned int setMemAddrOfNode(struct labelTableNode *node , unsigned int memAddr)
{
    if (node == NULL)
    {
        return 0;
    }
    node->memAddr = memAddr;
    return 1;
}

struct labelTableNode *getNextNode(struct labelTableNode *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    return node->next;
}

unsigned int getCapacity(struct labelTable *lt)
{
    if (lt == NULL)
    {
        return 0;
    }
    return lt->capacity;
}

int searchAndGetMemAddr(struct labelTable *lt , char * word)
{
    size_t index;
    struct labelTableNode *p;
    if (lt == NULL)
    {
        printf("searchAndGetMemAddr does not support null pointers\n");
        return -1;
    }
    if (word == NULL)
    {
        printf("searchAndGetMemAddr does not support null pointers\n");
        return -1;
    }
    

    index = hash(word , lt->capacity);
    p = lt->arr[index];

    while (p != NULL)
    {
        if (strcmp (word , p->label) == 0)
        {
            return p->memAddr;
        }
        p=p->next;
    }

    return -1;
}

