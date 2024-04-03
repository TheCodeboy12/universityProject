#include "token.h"

typedef struct lineStructNode lineStructNode;
typedef struct lineStructArray lineStructArray;



/**
 * @brief create a new lineStructArray and returns is
 * @return a pointer to the new lineStructArray
 * @return NULL if memory allocation failed
*/
struct lineStructArray *newLineStructArray(void);

/**
 * @brief create a new lineStructNode and returns is
 * @return a pointer to the new lineStructNode
 * @return NULL if memory allocation failed
*/
struct lineStructNode *newLineStructNode(void);







/**
 * @brief set the row number of the lineStructNode
 * @param lsNode the lineStructNode to set the row number of
 * @param rowNum the row number to set
 * @return 1 if the row number was set
*/
int setLSRowNum(lineStructNode *lsNode , int rowNum);
int setNextLSNode(lineStructNode *lsNode , lineStructNode *next);

int setLSToken(struct lineStructNode *ls , Token *tok ,const int type);
Token *getLSToken(struct lineStructNode *ls , const int type);

struct lineStructNode *getNextLSNode(lineStructNode *lsNode);
struct lineStructNode *getNextLSNode(struct lineStructNode *lsNode);

int freeLineStructNode(lineStructNode **lsNode);
int freeLineStructArray(lineStructArray **lsArray);

lineStructNode *getLSNodeByIndex(lineStructArray *lsArray , int index);

lineStructNode *getLSNodeTail(lineStructArray *lsArray);

lineStructNode *getLSNodeHead(lineStructArray *lsArray);



int getLSType(struct lineStructNode *lsNode);
int getLsRowNum(struct lineStructNode *lsNode);


int setLsType(struct lineStructNode *lsNode , int type);
int setLSRowNum(struct lineStructNode *lsNode , int rowNum);


/**
 * This function will create a  new linestruct Node and insert it to the end of the array and then return it
 * @param lsArray - a pointer to a lineStructArray
 * @param lineNumber - the line number of the lineStructNode
 * @return a pointer to the new lineStructNode
 * @return NULL if lsArray is NULL
 * @return NULL if memory allocation failed
 */
struct lineStructNode *createNewLineStructNode(struct lineStructArray *lsArray , int lineNumber);








void printLineStruct(struct lineStructNode *ls);
