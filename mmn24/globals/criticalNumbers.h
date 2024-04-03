#include <stdio.h>
#define MAX_BITS_ACTION_NUMBER 10
#define MAX_BITS_DATA_NUMBER 12

#define MAX_UNSIGNED(BITS) ((1 << (BITS)) - 1)
#define MAX_SIGNED(BITS) (((1 << ((BITS)- 1))) -1  )
#define MIN_SIGNED(BITS) (- ((1 << ((BITS) -1)) ))
