#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "matrix.h"

#define MASK(BIT) 1 << BIT

uint gpio_init_in_bitfield = 0x0;
uint gpio_init_out_bitfield = 0x0;

void initialize_gpio() {
  for (uint i = 0; i < COLUMN_COUNT; i++) {
    gpio_init_in_bitfield |= MASK(columns[i]);
  }
  printf("input mask: %x\n", gpio_init_in_bitfield);

  for (uint i = 0; i < ROW_COUNT; i++) {
    gpio_init_out_bitfield |= MASK(rows[i]);
  }
  printf("output mask: %x\n", gpio_init_out_bitfield);

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

/*------------- MAIN -------------*/
int main() {
  stdio_init_all();
	initialize_gpio();

	while(true) {

    /*---- TASK ----*/
		for (uint i = 0; i < ROW_COUNT; i++) {
      gpio_put_masked(gpio_init_out_bitfield, gpio_init_out_bitfield ^ MASK(rows[i]));

      uint bit_field;
      uint tmp = bit_field = gpio_get_all();

      // debounce
      do { 
        tmp = bit_field;
        sleep_ms(5);
        bit_field = gpio_get_all();
      } while (tmp != bit_field);
      

      uint result = ~bit_field & gpio_init_in_bitfield;

      if (!result)
        continue;
      
      for (uint j = 0; j < COLUMN_COUNT; j++) {
        if (MASK(columns[j]) & result) {
          printf("%s\n", btn_layout[i][j]);
        }
      }
    }
    printf("-------\n");
		sleep_ms(1000);
    
	}
	return 0;
}