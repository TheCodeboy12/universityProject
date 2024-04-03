typedef struct bitField bitField;
bitField *newBitField(void);
int initBitField(struct bitField *bf);
void printBitField(struct bitField *bf);

/**
 * @brief the function takes in a bitField and a number and encodes the 12 bits of bitField
 * @param b the bitField to encode
 * @param num the number to encode
 * @return 1 if successful, 0 if not
 * @note b must not be null
 * @note num must be between -2048 and 2047
 * @note if num is out of bounds, returns 0
 * @note if b is null, returns 0
 */
int codeNumberToBitField(struct bitField *b , const int num);
int codeTwoRegisters(struct bitField *bf , int sourceReg , int destReg);
int codeActionLineNumber(struct bitField *bf , int num) ;
int codeOneSourceOperand(struct bitField *bf , int sourceSubType );
int codeOneRegister(struct bitField *bf , int reg ,const int isSource);
int codeLabelOperand (struct bitField *bf , const unsigned int lableAddr, unsigned int external);
int intToFullBitField(struct bitField *bf , int num);
int codeLine(struct bitField *bf ,struct lineStructNode *ls);

char *bitfieldToBase64(struct bitField *bf , char *encoded);
