#include <stdio.h>

typedef struct  labelTableNode labelTableNode;
typedef struct  labelTable labelTable;


size_t hash(char *str , size_t arrSize);


/* ============New FUNCTIONS ==============*/
 labelTableNode *newTlNode(void);

 labelTable *newTable(const size_t initCapacity);

int freeTable( labelTable **lt);

int insertLabelNode( labelTable **lt , char *label , unsigned int memAddr);

int search( labelTable *lt , char * word);

labelTableNode *searchAndGetNode(struct labelTable *lt , char * word);

char *getLableFromNode( labelTableNode *node);

unsigned int getMemAddrFromNode( labelTableNode *node);
unsigned int setMemAddrOfNode(struct labelTableNode *node , unsigned int memAddr);

 labelTableNode *getNextNode( labelTableNode *node);
unsigned int getCapacity(struct labelTable *lt);
int searchAndGetMemAddr(struct labelTable *lt , char * word);
