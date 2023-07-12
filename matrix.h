#ifndef matrix_
#define matrix_

#define COLUMN_COUNT 15
#define ROW_COUNT 5

unsigned char columns[COLUMN_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 18, 19, 20, 21, 22};
unsigned char rows[ROW_COUNT] = {8, 9, 10, 11, 12};

#define no_btn "not_assign"

const char* btn_layout[5][15] = {
    {"esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<-", "home"}, 
    {"tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\", "del"}, 
    {"caps", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "enter", "pgup", no_btn}, 
    {"shift", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "shift", "^", "pgdn", no_btn}, 
    {"Lcrtl", "os", "Lalt", "space", no_btn, no_btn, no_btn, no_btn, "Ralt", "fn", "Rctrl", "<-", "v", "->", no_btn}
};

#endif