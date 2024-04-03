#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct intLinkedListNode
{
    int data;
    struct intLinkedListNode *next;
};

struct intLinkedList
{
    struct intLinkedListNode *head;
    struct intLinkedListNode *tail;
    int size;
};

struct intLinkedList *newIntLinkedList(void)
{
    struct intLinkedList *list = (struct intLinkedList*)malloc(sizeof(struct intLinkedList));
    if (list == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int getNumberFromNode(struct intLinkedListNode *node)
{
    if (node == NULL)
    {
        printf("intLinkedListNode is null\n");
        return 0;
    }
    return node->data;
}

struct intLinkedListNode *getILLHead(struct intLinkedList *list)
{
    if (list == NULL)
    {
        printf("intLinkedList is null\n");
        return NULL;
    }
    return list->head;
}

struct intLinkedListNode *getILLNextNode(struct intLinkedListNode *node)
{
    if (node == NULL)
    {
        printf("intLinkedListNode is null\n");
        return NULL;
    }
    return node->next;
}

struct intLinkedListNode *newIntLinkedListNode(int data)
{
    struct intLinkedListNode *node = (struct intLinkedListNode*)malloc(sizeof(struct intLinkedListNode));
    if (node == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int insertIntToLinkedList(struct intLinkedList *list , int data)
{
    struct intLinkedListNode *node;
    if (list == NULL)
    {
        printf("intLinkedList is null\n");
        return 0 ;
    }
    node = newIntLinkedListNode(data);
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->size++;
        return 1;
    }
    list->tail->next = node;
    list->tail = node;
    list->size++;
    return 1;
}

int extractNumbersFromString(char *str , struct intLinkedList *list)
{
    int sign = 1;
    int num =0 ;
    char *p;

    
    if (str == NULL)
    {
        printf("string is null\n");
        return 0;
    }
    if (list == NULL)
    {
        printf("intLinkedList is null\n");
        return 0;
    }
    p = str;
    while (*p != '\0')
    {
        if (*p == '-')
        {
            sign = -1;
            p++;
            continue;
        }
        if (*p >= '0' && *p <= '9')
        {
            while (*p >= '0' && *p <= '9')
            {
                num = num * 10 + (*p - '0');
                p++;
            }
            num *= sign;
            insertIntToLinkedList(list , num);
            sign = 1;
            num =0;
            continue;
        }
        p++;
    }
    return 1;
}

int freeIntLinkedList(struct intLinkedList *list)
{
    struct intLinkedListNode *p , *q;
    if (list == NULL)
    {
        printf("intLinkedList is null\n");
        return 0 ;
    }
    p = list->head;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    free(list);
    return 1;
}   

int convertStringToLinkedList(char *str , struct intLinkedList *list)
{
    int num;
    char *p;
    if (str == NULL)
    {
        printf("string is null\n");
        return 0;
    }
    if (list == NULL)
    {
        printf("intLinkedList is null\n");
        return 0;
    }
    p = str;
    while (*p != '\0')
    {
        num = (int)(*p);
        insertIntToLinkedList(list , num);
        p++;
    }
    return 1;
}
