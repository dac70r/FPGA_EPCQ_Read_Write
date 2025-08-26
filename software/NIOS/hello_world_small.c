
#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "stdint.h"
#include "sys/alt_sys_init.h"
#include "sys/alt_flash.h"
#include "peripheral/peripheral_linker.h"

uint8_t on_off = 1;		// For Toggling the LED

int main()
{ 
  alt_putstr("------- Welcome to EPCQ Read/ Write Programme! -------\n");
  alt_putstr("Please refer to the memory range for your EPCQ Device\n");

  // Perform Sanity Check on the EPCQ Controller
  epcq_controller_sanity_check();

  /* Event loop never exits. */
  while (1){
		IOWR(LED_BASE, 0, on_off);
		on_off = ~on_off;
		alt_busy_sleep(1000000);
  }

  return 0;
}

