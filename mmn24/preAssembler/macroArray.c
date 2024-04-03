#include <stdio.h>
#include <stdlib.h>
#include <string.h>




struct charNode
{
    char *line;
    struct charNode *next;
};

struct charList
{
    char *macroName;
    struct charNode *head;
    struct charNode *tail;
    size_t size;
};

struct macroArray
{
    struct charList **arr;
    size_t numOfElements;
    size_t capacity;
};

/**
 * create a new macroArray with a capacity of parameter initialCapacity
 * @param initialCapacity the initial capacity of the macroArray
 * @return a pointer to the new macroArray
 * @return NULL if memory allocation failed
*/
struct macroArray *newMacroArray(size_t initialCapacity)
{
    struct macroArray *ma = (struct macroArray*)malloc(sizeof(struct macroArray));
    if (ma == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    ma->arr = (struct charList**)malloc(sizeof(struct charList*)*initialCapacity);
    if (ma->arr == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    ma->numOfElements = 0;
    ma->capacity = initialCapacity;
    return ma;
}

/**
 * Create a new charList with a macroName of parameter name
 * @param name the name of the macro
 * @return a pointer to the new charList
 * @return NULL if memory allocation failed
 * @return NULL if name is NULL
 * @return NULL if name is empty
*/
struct charList *newCharList(char *name)
{
    struct charList *cl;
    if (name == NULL)
    {
        printf("name is null\n");
        return NULL;
    }
    if (name[0] == '\0')
    {
        printf("name is empty\n");
        return NULL;
    }
    cl = (struct charList*)malloc(sizeof(struct charList));
    if (cl == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    cl->macroName = name;
    cl->head = NULL;
    cl->tail = NULL;
    cl->size = 0;
    return cl;
}

/**
 * Insert a new macro to the macroArray
 * Re allocate memory for the macro array as needed
 * @param ma the macroArray to insert to
 * @param name the name of the macro
 * @return 1 if the macro was inserted
 * @return 0 if the macro was not inserted
 * @return -1 if ma is NULL
 * @return -1 if name is NULL
 * @return -1 if name is empty
*/
int insertMacroArray(struct macroArray **ma , char *name)
{
    struct charList *cl;
    if (ma == NULL)
    {
        printf("macroArray is null\n");
        return -1;
    }
    if (name == NULL)
    {
        printf("name is null\n");
        return -1;
    }
    if (name[0] == '\0')
    {
        printf("name is empty\n");
        return -1;
    }
    if ((*ma)->numOfElements == (*ma)->capacity)
    {
        (*ma)->capacity *= 2;
        (*ma)->arr = (struct charList**)realloc((*ma)->arr , sizeof(struct charList*)*(*ma)->capacity);
        if ((*ma)->arr == NULL)
        {
            printf("memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    cl = newCharList(name);
    (*ma)->arr[(*ma)->numOfElements] = cl;
    (*ma)->numOfElements++;
    return 1;
}


/**
 * Search for a charList with a macroName of parameter name in the macroArray
 * @param ma the macroArray to search in
 * @param name the name of the macro
 * @return a pointer to the charList with a macroName of parameter name
 * @return NULL if ma is NULL
 * @return NULL if name is NULL
 * @return NULL if name is empty
 * @return NULL if the charList with a macroName of parameter name is not found
 * @return NULL if the macroArray is empty
*/
struct charList *searchMacroArray(struct macroArray *ma , char *name)
{
    size_t i;
    struct charList *cl;
    if (ma == NULL)
    {
        printf("macroArray is null\n");
        return NULL;
    }
    if (name == NULL)
    {
        printf("name is null\n");
        return NULL;
    }
    if (name[0] == '\0')
    {
        printf("name is empty\n");
        return NULL;
    }
    if (ma->numOfElements == 0)
    {
        return NULL;
    }
    for ( i = 0; i < ma->numOfElements; i++)
    {
        cl = ma->arr[i];
        if (strcmp(cl->macroName , name) == 0)
        {
            return cl;
        }
    }
    return NULL;
    
}

/**
 * insert line to the end of a charList with a macroName of parameter name
 * @param ma the macroArray to search in
 * @param name the name of the macro
 * @param line the line to insert
*/
void insertLineToCharList(struct macroArray *ma , char *name , char *line)
{
    struct charList *cl;
    struct charNode *cn;
    if (ma == NULL)
    {
        printf("macroArray is null\n");
        return;
    }
    if (name == NULL)
    {
        printf("name is null\n");
        return;
    }
    if (name[0] == '\0')
    {
        printf("name is empty\n");
        return;
    }
    if (line == NULL)
    {
        printf("line is null\n");
        return;
    }
    cl = searchMacroArray(ma , name);
    if (cl == NULL)
    {
        printf("charList not found\n");
        return;
    }
    cn = (struct charNode*)malloc(sizeof(struct charNode));
    if (cn == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    cn->line = malloc(sizeof(char)*(strlen(line)+1));
    if (cn->line == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(cn->line , line); /*Copy the line to the line field*/
    cn->next = NULL;
    if (cl->head == NULL)
    {
        cl->head = cn;
        cl->tail = cn;
        cl->size++;
        return;
    }
    cl->tail->next = cn;
    cl->tail = cn;
    cl->size++;
    return;
}

/**
 * Search for a macro name in the array and if it is found then write all of its lines to the file
 * @param ma the macroArray to search in
 * @param name the name of the macro
 * @param fp the file to write to
 * @return 1 if the macro was found and written to the file
 * @return 0 if the macro was not found
 * @return -1 if ma is NULL
 * @return -1 if name is NULL
 * @return -1 if name is empty
 * @return -1 if fp is NULL
 * @return -1 if the macroArray is empty
 * @return -1 if the macro was not found
 * @return -1 if the macro was found but the file writing failed
*/
int writeMacroToFile(struct macroArray *ma , char *name , FILE *fp)
{
    struct charList *cl;
    struct charNode *cn;
    if (ma == NULL)
    {
        printf("macroArray is null\n");
        return -1;
    }
    if (name == NULL)
    {
        printf("name is null\n");
        return -1;
    }
    if (name[0] == '\0')
    {
        printf("name is empty\n");
        return -1;
    }
    if (fp == NULL)
    {
        printf("fp is null\n");
        return -1;
    }
    if (ma->numOfElements == 0)
    {
        return -1;
    }
    cl = searchMacroArray(ma , name);
    if (cl == NULL)
    {
        printf("charList not found\n");
        return 0;
    }
    cn = cl->head;
    while (cn != NULL)
    {
        if (fprintf(fp , "%s\n" , cn->line) < 0)
        {
            printf("file writing failed\n");
            return -1;
        }
        cn = cn->next;
    }
    return 1;
}


/**
 * Free all the memory allocated for the macroArray
 * @param ma the macroArray to free
 * @return 1 if the macroArray was freed
 * @return 0 if the macroArray was not freed
 * @return -1 if ma is NULL
*/
int freeMacroArray(struct macroArray *ma)
{
    size_t i;
    struct charList *cl;
    struct charNode *cn , *cnNext;
    if (ma == NULL)
    {
        printf("macroArray is null\n");
        return -1;
    }
    for ( i = 0; i < ma->numOfElements; i++)
    {
        cl = ma->arr[i];
        cn = cl->head;
        while (cn != NULL)
        {
            cnNext = cn->next;
            free(cn->line);
            free(cn);
            cn = cnNext;
        }
        free(cl->macroName);
        free(cl);
    }
    free(ma->arr);
    free(ma);
    return 1;
}

int insertMacroNameToMacroArray(struct macroArray **ma , char *name)
{
    struct charList *cl;
    char *toCopy;
    if (ma == NULL)
    {
        printf("macroArray is null\n");
        return -1;
    }
    if (name == NULL)
    {
        printf("name is null\n");
        return -1;
    }
    if (name[0] == '\0')
    {
        printf("name is empty\n");
        return -1;
    }
    toCopy = (char*)malloc(sizeof(char)*(strlen(name)+1));
    if (toCopy == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(toCopy , name);
    cl = newCharList(toCopy);
    if (cl == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    if ((*ma)->numOfElements == (*ma)->capacity)
    {
        (*ma)->capacity *= 2;
        (*ma)->arr = (struct charList**)realloc((*ma)->arr , sizeof(struct charList*)*(*ma)->capacity);
        if ((*ma)->arr == NULL)
        {
            printf("memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    (*ma)->arr[(*ma)->numOfElements] = cl;
    (*ma)->numOfElements++;
    return 1;
}

/**
 * This function will search and return the charList with the macro name
 * @param ma the macroArray to search in
 * @param name the name of the macro
 * @return a pointer to the charList with the macro name
*/
struct charList *searchAndReturnCharList(struct macroArray *ma , char *name)
{
    size_t i;
    struct charList *cl;
    if (ma == NULL)
    {
        printf("macroArray is null\n");
        return NULL;
    }
    if (name == NULL)
    {
        printf("name is null\n");
        return NULL;
    }
    if (name[0] == '\0')
    {
        printf("name is empty\n");
        return NULL;
    }
    if (ma->numOfElements == 0)
    {
        return NULL;
    }
    for ( i = 0; i < ma->numOfElements; i++)
    {
        cl = ma->arr[i];
        if (strcmp(cl->macroName , name) == 0)
        {
            return cl;
        }
    }
    return NULL;
}


/**
 * This function will insert a line to the end of the charList with the macro name
 * @param ma the macroArray to search in
 * @param name the name of the macro
 * @param line the line to insert
 * @return 1 if the line was inserted
 * @return 0 if the line was not inserted
 * @return -1 if ma is NULL
 * @return -1 if name is NULL
*/
int insertLineToMacroArray(struct macroArray *ma , char *name , char *line)
{
    struct charList *cl;
    struct charNode *cn;
    if (ma == NULL)
    {
        printf("macroArray is null\n");
        return -1;
    }
    if (name == NULL)
    {
        printf("name is null\n");
        return -1;
    }
    if (name[0] == '\0')
    {
        printf("name is empty\n");
        return -1;
    }
    if (line == NULL)
    {
        printf("line is null\n");
        return -1;
    }
    cl = searchAndReturnCharList(ma , name);
    if (cl == NULL)
    {
        return 0;
    }
    cn = (struct charNode*)malloc(sizeof(struct charNode));
    if (cn == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    cn->line = malloc(sizeof(char)*(strlen(line)+1));
    if (cn->line == NULL)
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(cn->line , line); /*Copy the line to the line field*/
    /*replace the /n with null terminator*/
    if (cn->line[strlen(cn->line)-1] == '\n')
    {
        cn->line[strlen(cn->line)-1] = '\0';
    }
    cn->next = NULL;
    if (cl->head == NULL)
    {
        cl->head = cn;
        cl->tail = cn;
        cl->size++;
        return 1;
    }
    cl->tail->next = cn;
    cl->tail = cn;
    cl->size++;
    return 1;
}
