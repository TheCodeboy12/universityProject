#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token
{
    char *word;
    int type;
    int subType;
};

/*========TOKEN FUNCTIONS ====== */
int setWord(struct token *t , char *word)
{
    if (t == NULL)
    {
        /*printf("token is null\n");*/
        return -1;
    }
    if (word == NULL)
    {
        return -1;
        printf("tried inserting a NULL word into token is not allowed null\n");
    }
    else
    {
        t->word = word;
    }
    return 1;
    
}
int setType(struct token *tok,  const int type )
{
    if (tok == NULL)
    {
        /*printf("token is null\n");*/
        return 0;
    }
    tok->type = type;
    return 1;
}
int setSubType(struct token *tok,  const int subType )
{
    if (tok == NULL)
    {
        /*printf("token is null\n");*/
        return 0;
    }
    tok->subType = subType;
    return 1;
}
struct token  *newToken(void)
{
    struct token *t = (struct token*)malloc(sizeof(struct token));
    if (t == NULL)
    {
        printf("memory allocation failed\n");
        return NULL;
    }
    t->word = NULL;
    t->type = 0;
    t->subType = 0;
    return t;
}
int freeToken(struct token **tok)
{
    if (tok == NULL)
    {
        /*printf("token is null\n");*/
        return 0;
    }
    if ((*tok)->word != NULL)
    {
        
        free((*tok)->word);
        (*tok)->word = NULL;
        
    }
    free((*tok));
    (*tok)=NULL;
    return 1;
}
int getType(const struct token *t)
{
    if (t == NULL)
    {
        /*printf("token is null\n");*/
        return -1;
    }
    return t->type;
}
int getSubType(const struct token *t)
{
    if (t == NULL)
    {
        /*printf("token is null\n");*/
        return -1;
    }
    return t->subType;
}
char *getWord(const struct token *t)
{
    if (t == NULL)
    {
        /*printf("token is null\n");*/
        return NULL;
    }
    return t->word;
}

/*========END TOKEN FUNCTIONS ====== */
