#include <stdio.h>
struct Token;
struct tokenErrors;
struct lineStruct;
struct tokenArr;
struct lineStructure;
struct labelTable;
struct bitField;
struct lineStructArray;
struct lineStructNode;
unsigned int firstRun(FILE *f, unsigned int *IC, unsigned int *DC ,struct labelTable **lt , struct labelTable **ltExterns , struct labelTable **ltEntries , struct lineStructArray *lsa, struct lineStructArray *lsd);
char *decimalToBinary(int decimal, int fillNumber);
int checkIfRegister(const char *buffer);
void classifyRunLine(struct lineStruct *ls);
int checkIfLabelIsAction(char *label);
int checkIfLabelExistsInLabelTable(const char *label);
int checkIfLabelExistsInExterns(const char *label);
char *skipWhites(char *p);
int checkIfExternousText(char *cursor);
void checkLineStructErrors(struct lineStructure *l);
int checkNumbers(char *buffer,unsigned int *errorFound, int rowNum);
unsigned int calcOpAddr(struct Token *tok);
unsigned int countNumbers(const struct Token *numbers);

int checkActionLinestructsForErrors(struct lineStructNode *ls);



