typedef enum{
DATA,
STRING,
ENTRY,
EXTERN,
NUM_INSTRUCTIONS
}instructions;


typedef enum{
    REGISTER,
    NUMBER,
    STR,
    LABEL ,
    INSTRUCTION,
    ACTION,
    NUM_TYPE_OF_OPERANDS
}mainTypes;


typedef enum{
    COLON,
    DOT,
    PARAN,
    COMMA,
    AT_SIGN,
    SPACE,
    PLUS,
    NUM_OF_DELIMS
}delimNumbers;
