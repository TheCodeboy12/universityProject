struct lineStructNode;
struct bitField;
struct labelTable;
/*======FUNCTIONS======*/

void codeIt(struct lineStructNode *ls ,unsigned int (*IC) ,unsigned int *DC , struct labelTable *lt, struct labelTable *ltExterns , struct labelTable *ltEntries ,const char *objectFileName, const char *externalFileName , const char *entriesFileName);
