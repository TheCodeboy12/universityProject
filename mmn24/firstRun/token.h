typedef struct Token Token;

/**
 * @brief create a new Token and returns is
 * @return a pointer to the new Token
 * @return NULL if memory allocation failed
*/
Token  *newToken(void);


/**
 * @brief set the word of the token
 * @param t the token to set the word of
 * @param word the word to set
 * @return 1 if the word was set
 * @return 0 if t is NULL
 * @return 0 if word is NULL
 * @return 0 if memory allocation failed
 * @return 0 if the word was not set
*/
void setWord(Token *t , char *word);

/**
 * @brief set the type of the token
 * @param tok the token to set the type of
 * @param type the type to set
 * @return 1 if the type was set
 * @return 0 if tok is NULL
 * @return 0 if the type was not set
*/
int setType(Token *tok,  const int type );
/**
 * @brief set the subType of the token
 * @param tok the token to set the subType of
 * @param subType the subType to set
 * @return 1 if the subType was set
 * @return 0 if tok is NULL
 * @return 0 if the subType was not set
 * @return 0 if memory allocation failed
*/
int setSubType(Token *tok,  const int subType );

/**
 * @brief get the type of the token
 * @param t the token to get the type of
 * @return the type of the token
 * @return -1 if t is NULL
 * @return -1 if the type was not found
 * 
*/
int getType(const Token *t);
/**
 * @brief get the subType of the token
 * @param t the token to get the subType of
 * @return the subType of the token
 * @return -1 if t is NULL
 * @return -1 if the subType was not found
 * 
*/
int getSubType(const Token *t);

/**
 * @brief get the word of the token
 * @param t the token to get the word of
 * @return the word of the token
 * @return NULL if t is NULL
 * @return NULL if the word was not found
*/
char *getWord(const Token *t);

/**
 * @brief free the memory of the token
 * @param t the token to free
 * @return 1 if the token was freed
 * @return 0 if t is NULL
 * @return 0 if the token was not freed
*/
int freeToken(Token **t);


/**
 * @brief enum for the token type
 * l_tok - label
 * a_tok - action
 * s_tok - source operand
 * d_tok - destination operand
*/
typedef enum {
    l_tok, 
    a_tok,
    s_tok,
    d_tok
} tokenType;

