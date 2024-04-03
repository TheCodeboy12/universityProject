int checkIfEmpty(const char* str) ;


/**
 * This function will take in two strings and return a pointer to the connected string
*/
char* concat(const char *s1, const char *s2);
int checkIfOP(char *str);
int checkIfInstruction(char *str);
int checkFirstChar(const char *str, const char arg);
/**
 * This function takes in a pointer to a string and will return a pointer to the same string after it skipped all the white charecters
 * @param p a pointer to a string
 * @return char * type - a pointer after skipping the white charecters
 */
char *skipWhites(char *p);

/**
 * This function takes in a pointer to a string and will check if there exists any externous text after it
 * @param cursor -  a char* type
 */
int checkIfExternousText(char *cursor);

/**
 * Will attemp to get the word until a certain char is found or until the word is not alphanumeric
 * if the char was not found but end of line or EOF is found itll default to return the word still
 * will autmatically put '\0' at the end of the word
 * @param word is the word to get
 * @param c is the char to stop at
 * @return a pointer to the word or null if not found
 */
char *getWordUntil(char *word, char c);

/**
 * Will return a pointer to a charecter as so:
 * *p != c && *p != '\0' && *p != '\n'
 * @return if found that charecter NULL otherwise
 */
char *skipUntil(char *word, char c);

/**
 * This function will get the first word form a given pointer to a string
 * @param str the pointer to the string
 * @return a pointer to the first word
*/
char *getFirstWord(char *str);

/**
 * This function will search how many times a char appears in a string
 * @param str is the string to search in
 * @param c is the char to search for
 * @return the number of times c appears in str
 */
int countCharInString(char *str, char c);


char *skipUntilOrEOF(char *word, char c);




