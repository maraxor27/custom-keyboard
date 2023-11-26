#include <stdio.h>
#include "matrix.h"

/*------------- MAIN -------------*/
int main() {
  stdio_init_all();
	initialize_gpio();

	while(true) {

    /*---- TASK ----*/
		// for (uint i = 0; i < ROW_COUNT; i++) {
    //   gpio_put_masked(gpio_init_out_bitfield, gpio_init_out_bitfield ^ MASK(rows[i]));

    //   uint bit_field;
    //   uint tmp = bit_field = gpio_get_all();

    //   // debounce
    //   do {
    //     tmp = bit_field;
    //     sleep_ms(5);
    //     bit_field = gpio_get_all();
    //   } while (tmp != bit_field);


    //   uint result = ~bit_field & gpio_init_in_bitfield;

    //   if (!result)
    //     continue;
      
    //   for (uint j = 0; j < COLUMN_COUNT; j++) {
    //     if (MASK(columns[j]) & result) {
    //       printf("%s\n", btn_layout[i][j]);
    //     }
    //   }
    // }
    printf("--- State ---\n");
    update_state();
    for (uint i = 0; i < ROW_COUNT; i++) {
      printf("state: 0x%02x, debounced_state: 0x%02x\n", state[i], debounced_state[i]);
    }
    printf("--- Key Codes ---\n");
    uint8_t keycodes[6] = {0,0,0,0,0,0};
    set_pressed(keycodes);
    for (uint i= 0; i < 6; i++) {
      printf("keycode[%d]: %x\n", i, keycodes[i]);
    }
    
		sleep_ms(1000);
	}
	return 0;
}