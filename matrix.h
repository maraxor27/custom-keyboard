#ifndef matrix_
#define matrix_

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "bsp/board.h"

#define COLUMN_COUNT 15
#define ROW_COUNT 5

#define MASK(BIT) 1 << BIT

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

const unsigned char btn_hid_layout[5][15] = {
    {HID_KEY_ESCAPE, HID_KEY_1, HID_KEY_2, HID_KEY_3, HID_KEY_4, HID_KEY_5, HID_KEY_6, HID_KEY_7, HID_KEY_8, HID_KEY_9, HID_KEY_0, HID_KEY_MINUS, HID_KEY_EQUAL, HID_KEY_BACKSPACE, HID_KEY_HOME}, 
    {HID_KEY_TAB, HID_KEY_Q, HID_KEY_W, HID_KEY_E, HID_KEY_R, HID_KEY_T, HID_KEY_Y, HID_KEY_U, HID_KEY_I, HID_KEY_O, HID_KEY_P, HID_KEY_BRACKET_LEFT, HID_KEY_BRACKET_RIGHT, HID_KEY_BACKSLASH, HID_KEY_DELETE}, 
    {HID_KEY_CAPS_LOCK, HID_KEY_A, HID_KEY_S, HID_KEY_D, HID_KEY_F, HID_KEY_G, HID_KEY_H, HID_KEY_J, HID_KEY_K, HID_KEY_L, HID_KEY_SEMICOLON, HID_KEY_APOSTROPHE, HID_KEY_ENTER, HID_KEY_PAGE_UP, HID_KEY_NONE}, 
    {HID_KEY_SHIFT_LEFT, HID_KEY_Z, HID_KEY_X, HID_KEY_C, HID_KEY_V, HID_KEY_B, HID_KEY_N, HID_KEY_M, HID_KEY_COMMA, HID_KEY_PERIOD, HID_KEY_SLASH, HID_KEY_SHIFT_RIGHT, HID_KEY_ARROW_UP, HID_KEY_PAGE_DOWN, HID_KEY_NONE}, 
    {HID_KEY_CONTROL_LEFT, HID_KEY_NONE, HID_KEY_ALT_LEFT, HID_KEY_SPACE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_NONE, HID_KEY_ALT_RIGHT, HID_KEY_NONE, HID_KEY_CONTROL_RIGHT, HID_KEY_ARROW_LEFT, HID_KEY_ARROW_DOWN, HID_KEY_ARROW_RIGHT, HID_KEY_HOME}
};

uint gpio_init_in_bitfield = 0x0;
uint gpio_init_out_bitfield = 0x0;

void initialize_gpio() {
  for (uint i = 0; i < COLUMN_COUNT; i++) {
    gpio_init_in_bitfield |= MASK(columns[i]);
  }

  for (uint i = 0; i < ROW_COUNT; i++) {
    gpio_init_out_bitfield |= MASK(rows[i]);
  }

  gpio_init_mask(gpio_init_in_bitfield | gpio_init_out_bitfield);
  

  for (uint i = 0; i < COLUMN_COUNT; i++) {
    gpio_set_dir(columns[i], GPIO_IN);
	gpio_pull_up(columns[i]);
  }

  for (uint i = 0; i < ROW_COUNT; i++) {
    gpio_set_dir(rows[i], GPIO_OUT);
	gpio_set_outover(rows[i], GPIO_OVERRIDE_NORMAL);
  }

  gpio_put_masked(gpio_init_out_bitfield, gpio_init_out_bitfield);
}

uint16_t convert_gpio_to_16(uint bitfield) {
    uint16_t value = 0;
    for (uint i = 0; i < COLUMN_COUNT; i++) {
        value |= (!!(bitfield & MASK(columns[i]))) << i; 
    }
    return value;
}

uint16_t state[ROW_COUNT] = {0,0,0,0,0};
uint16_t debounced_state[ROW_COUNT] = {0,0,0,0,0};

void update_state() {
    for (uint i = 0; i < ROW_COUNT; i++) {
        gpio_put_masked(gpio_init_out_bitfield, gpio_init_out_bitfield ^ MASK(rows[i]));
        sleep_us(1); // This sleep is necessary for the read to be valid. Otherwise the read will be off by 1 row.
        uint bit_field = ~gpio_get_all();
        uint16_t converted = convert_gpio_to_16(bit_field);
        
        uint16_t debounced = ~(state[i] ^ converted);
        uint16_t debounced_on = debounced & converted;
        uint16_t debounced_off = debounced & ~converted;

        debounced_state[i] |= debounced_on;
        debounced_state[i] &= ~debounced_off;
        state[i] = converted;
    }
}

#define MAX_KEYCODE_COUNT 6
void set_pressed(uint8_t* keycodes) {
    unsigned char count = 0;
    for (uint i = 0; i < ROW_COUNT; i++) {
        for (uint j = 0; j < COLUMN_COUNT; j++) {
            if (debounced_state[i] & MASK(j)) {
                keycodes[count] = btn_hid_layout[i][j];
                if (++count >= 6) {
                    return;
                }
            }
        }
    }
}

#endif