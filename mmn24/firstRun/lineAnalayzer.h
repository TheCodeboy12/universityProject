
char *getLabel(char *cursor , int rowNum ,unsigned int *errorsInFile ,unsigned int *labelFound );

int getLineType(char *line ,int *AItype , int *AIsubType);


int getOperandType(char *operand, int *type, int *subType);

char *getActionOperand(char *cursor, char *endOfLine);

int getNumberFromString(char *buffer);
