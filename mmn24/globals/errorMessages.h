#define INCORRECT_OPERAND(row, col) \
    do { \
        printf("ERROR: in row %d col %d Incorrect operand provided.\n", (row), (col)); \
    } while (0)

#define LABEL_EXISTS(row, col) \
    do { \
        printf("ERROR: in row %d col %d Label already exists.\n", (row), (col)); \
    } while (0)

#define UNEXPECTED_OPERAND(row, col) \
    do { \
        printf("ERROR: in row %d col %d Unexpected operand encountered.\n", (row), (col)); \
    } while (0)


#define EXTERNOUS_TEXT(row, col) \
    do { \
        printf("ERROR: in row %d col %d Externous text after command.\n", (row), (col)); \
    } while (0)

#define LABEL_IN_FRONT_OF_ENTRY(row, col) \
    do { \
        printf("ERROR: in row %d col %d Unexpected label in front of ENTRY directive.\n", (row), (col)); \
    } while (0)

#define LABEL_ALNUM(row, col) \
    do { \
        printf("ERROR: in row %d col %d Label contains non-alphanumeric characters.\n", (row), (col)); \
    } while (0)

#define REACHED_END_OF_LINE(row, col) \
    do { \
        printf("ERROR: in row %d col %d Unexpected end of line. Missing string content.\n", (row), (col)); \
    } while (0)

#define UNEXPECTED_CHAR_FOUND(row, col) \
    do { \
        printf("ERROR: in row %d col %d Unexpected character found.\n", (row), (col)); \
    } while (0)

#define TWO_CONTINUOUS_COMMAS(row, col) \
    do { \
        printf("ERROR: in row %d col %d Two consecutive commas found.\n", (row), (col)); \
    } while (0)

#define SUBTYPE_NOT_FOUND(row, col) \
    do { \
        printf("ERROR: in row %d col %d Subtype not found for the NUMBER token.\n", (row), (col)); \
    } while (0)


#define INSUFFICIENT_NUMBER_OF_OPERANDS(row, col) \
    do { \
        printf("ERROR: in row %d col %d Insufficient number of operands provided.\n", (row), (col)); \
    } while (0)

#define LINE_TOO_LONG(row) \
    do { \
        printf("ERROR: in row %d Line too long.\n", (row)); \
    } while (0)


