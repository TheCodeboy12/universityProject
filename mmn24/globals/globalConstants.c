#include <stdio.h>
#include <stdlib.h>
#include "./globalEnums.h"



const char *operationStrings[NUM_OPS] = {
    "mov",
    "cmp",
    "add",
    "sub",
    "not",
    "clr",
    "lea",
    "inc",
    "dec",
    "jmp",
    "bne",
    "red",
    "prn",
    "jsr",
    "rts",
    "stop",
    "mcro"
};

const char *registersStrings[NUM_REGS]= {
    "@r0",
    "@r1",
    "@r2",
    "@r3",
    "@r4",
    "@r5",
    "@r6",
    "@r7",
};

const char *instructionsArr[] = {
    "data",
    "string",
    "entry",
    "extern"
};
