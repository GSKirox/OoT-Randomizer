#include "ocarina_buttons.h"
#include <stdbool.h>

struct buttons_t {
    uint8_t           a;
    uint8_t           c_up;
    uint8_t           c_down;
    uint8_t           c_left;
    uint8_t           c_right;
} buttons = { 
    .a = 1.0,
    .c_up = 1.0,
    .c_down = 1.0,
    .c_left = 1.0,
    .c_right = 1.0
};

uint8_t c_block_ocarina()
{
    uint8_t res = 0;
    if (buttons.a) {
        res |= 1 << 0;
    }
    if (buttons.c_up) {
        res |= 1 << 1;
    }
    if (buttons.c_down) {
        res |= 1 << 2;
    }
    if (buttons.c_left) {
        res |= 1 << 3;
    }
    if (buttons.c_right) {
        res |= 1 << 4;
    }
    return res;
}

void unlock_button(ButtonType button) {
    switch(button) {
        case A :
            buttons.a = 0;
            break;
        case C_DOWN :
            buttons.c_down = 0;
            break;
        case C_LEFT :
            buttons.c_left = 0;
            break;
        case C_UP :
            buttons.c_up = 0;
            break;
        case C_RIGHT :
            buttons.c_right = 0;
            break;
    }
}
