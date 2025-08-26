/*
 * Library for EPCQ Memory Management .c file
 *
 * Author: Dennis Wong Guan Ming
 * Date: 25/8/2025
 *
 * EPCQ128A = 256 Sectors -> 16 Sub-sectors -> 4096 Bytes/ Sub-sector
 * 			= 256 * 16 * 4096 Bytes = 16.384 KiloBytes
 *
 *
 * */

#include "peripheral_linker.h"


// Variable Declaration
 uint8_t subsector_buffer[4096]; 									// Define buffer to store data for a single sector
 int mem_read_offset = 0x0000;											// Selects the Sub-sector to Read
 int  erase_offset = 0x000000;												// Selects the Sector to Erase (Only Erases a Single Sector)
 int length = sizeof(subsector_buffer);

// Function Definition

/**
 * @brief Reads the Memory Contents Read back from the EPCQ of the FPGA
 *
 * @param subsector_buffer_array	- This pointer points to the buffer array storing the Read back data from EPCQ
 * @param mem_read_offset			- Offset on the BASE Address of the EPCQ memory (e.g. Offset = 0x000001 means read from the second data of the EPCQ)
 * @param sizeof_subsector_buffer	- Size of the EPCQ Buffer
 *
 * @return N/A
 *
 */

void print_read_epcq_mem(uint8_t *subsector_buffer_array, int mem_read_offset, int sizeof_subesector_buffer){
	for (int i = 0; i < sizeof_subesector_buffer - mem_read_offset; i++) {
		printf("%02X ", subsector_buffer_array[i]);
		if ((i + 1) % 16 == 0) printf("\n");
	}

}

/**
 * @brief Erases a sector of the EPCQ memory based on the OFFSET
 *
 * @param erase_offset				- Offset on the BASE Address of the EPCQ memory (e.g. Offset = 0x000001 means read from the second data of the EPCQ)
 *
 * @return 0: Erase Success, 9: Erase Failed.
 *
 */

uint8_t erase_epcq_sector(int erase_offset){

	if (alt_epcq_controller2_erase_block(&epcq_dev_ptr->dev, erase_offset) == 0){
		return 0;
	}
	else
		return 9;
}

/**
 * @brief Erases the entire EPCQ Memory
 *
 * @param N/A
 *
 * @return 0: Erase Success, 9: Erase Failed.
 *
 */

uint8_t erase_epcq_all_sector(void ){

	uint8_t response = 0;
	for (uint32_t addr = 0x000000; addr <= 0xEF0000; addr += 0x10000) {
	    response = alt_epcq_controller2_erase_block(&epcq_dev_ptr->dev, addr);
	    if (response != 0) {
	        printf("Erase failed at address 0x%06X\n", addr);
	        break;
	    }
	}
	return 0;
}

/**
 * @brief Reads First Sub-sector And Prints In Console
 *
 * @param N/A
 *
 * @return N/A
 *
 */

void epcq_controller_sanity_check(void ){

	if(alt_epcq_controller2_read(&epcq_dev_ptr->dev, mem_read_offset, subsector_buffer, length) == 0) {
			  printf("Read successful!\n");
			  print_read_epcq_mem(subsector_buffer, mem_read_offset, length);
		  } else {
			  printf("Read failed!\n");
		  }

		  // Checks if "dennis" is detected, if so erase memory, else write "dennis"
		  if (IORD_8DIRECT(EPCQ_CONTROLLER, 0x000000) == 0x64 \
				  && IORD_8DIRECT(EPCQ_CONTROLLER, 0x000001) == 0x65 \
				  && IORD_8DIRECT(EPCQ_CONTROLLER, 0x000002) == 0x6E \
				  && IORD_8DIRECT(EPCQ_CONTROLLER, 0x000003) == 0x6E \
				  && IORD_8DIRECT(EPCQ_CONTROLLER, 0x000004) == 0x69 \
				  && IORD_8DIRECT(EPCQ_CONTROLLER, 0x000005) == 0x73 ){

			  if(erase_epcq_sector(0x000000) == 0) {
				  printf("Erase successful!\n");
			  } else {
				  printf("Erase failed!\n");
			  }
		  }
		  else{
			  /* A Very Simple and Crude Method to Write Information into EPCQ Memory */
			  // At the offset from Base Address, Write the Value into Flash, provided the location has not been written before
				IOWR_8DIRECT(EPCQ_CONTROLLER, 0x000000 + 0, 0x64); // d
				IOWR_8DIRECT(EPCQ_CONTROLLER, 0x000000 + 1, 0x65); // e
				IOWR_8DIRECT(EPCQ_CONTROLLER, 0x000000 + 2, 0x6E); // n
				IOWR_8DIRECT(EPCQ_CONTROLLER, 0x000000 + 3, 0x6E); // n
				IOWR_8DIRECT(EPCQ_CONTROLLER, 0x000000 + 4, 0x69); // i
				IOWR_8DIRECT(EPCQ_CONTROLLER, 0x000000 + 5, 0x73); // s
		  }

		  // Reads First Sub-sector And Prints In Console
		  if(alt_epcq_controller2_read(&epcq_dev_ptr->dev, mem_read_offset, subsector_buffer, length) == 0) {
			  printf("Read successful!\n");
			  print_read_epcq_mem(subsector_buffer, mem_read_offset, length);
		  } else {
			  printf("Read failed!\n");
		  }

		  // Performs a Complete Erase of the EPCQ Memory
		  if(erase_epcq_all_sector() == 0 )
			  printf("Erased all EPCQ Sectors\n");
		  else
			  printf("Erase all EPCQ Sectors Failed\n");

}


/* A Very Simple and Crude Method to Write Information into EPCQ Memory */
// At the offset from Base Address, Write the Value into Flash, provided the location has not been written before
/*
	IOWR_8DIRECT(EPCQ_AVL_MEM_BASE, 0x000000 + 0, 0x64); // d
	IOWR_8DIRECT(EPCQ_AVL_MEM_BASE, 0x000000 + 1, 0x65); // e
	IOWR_8DIRECT(EPCQ_AVL_MEM_BASE, 0x000000 + 2, 0x6E); // n
	IOWR_8DIRECT(EPCQ_AVL_MEM_BASE, 0x000000 + 3, 0x6E); // n
	IOWR_8DIRECT(EPCQ_AVL_MEM_BASE, 0x000000 + 4, 0x69); // i
	IOWR_8DIRECT(EPCQ_AVL_MEM_BASE, 0x000000 + 5, 0x73); // s
*/


