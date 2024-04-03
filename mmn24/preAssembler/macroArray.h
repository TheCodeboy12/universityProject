#include <stdio.h>


typedef struct macroArray macroArray;
/**
 * create a new macroArray with a capacity of parameter initialCapacity
 * @param initialCapacity the initial capacity of the macroArray
 * @return a pointer to the new macroArray
 * @return NULL if memory allocation failed
*/
struct macroArray *newMacroArray(size_t initialCapacity);
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
struct charList *searchMacroArray(struct macroArray *ma , char *name);

/**
 * insert line to the end of a charList with a macroName of parameter name
 * @param ma the macroArray to search in
 * @param name the name of the macro
 * @param line the line to insert
*/
void insertLineToCharList(struct macroArray *ma , char *name , char *line);

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
int writeMacroToFile(struct macroArray *ma , char *name , FILE *fp);

/**
 * Free all the memory allocated for the macroArray
 * @param ma the macroArray to free
 * @return 1 if the macroArray was freed
 * @return 0 if the macroArray was not freed
 * @return -1 if ma is NULL
*/
int freeMacroArray(struct macroArray *ma);

int insertMacroNameToMacroArray(struct macroArray **ma , char *name);

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
int insertLineToMacroArray(struct macroArray *ma , char *name , char *line);



