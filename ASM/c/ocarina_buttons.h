#include "z64.h"

typedef enum {
    /*  0 */ A,
    /*  1 */ C_DOWN,
    /*  2 */ C_LEFT,
    /*  3 */ C_UP,
    /*  4 */ C_RIGHT,
} ButtonType;

uint8_t c_block_ocarina();
void unlock_button(ButtonType button);
