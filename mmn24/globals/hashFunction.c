#include <stdio.h>


/* modified Hash function  djb2 credits http://www.cse.yorku.ca/~oz/hash.html*/
size_t hash(char *str , size_t arrSize)
{
    unsigned long hash = 5381;
    char *p;
    int c;
    p=str;
    while ((c = *p++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    /*printf("The hash of %s is %ld \n", str , hash %arrSize);*/
    return (size_t)(hash % arrSize);
}
