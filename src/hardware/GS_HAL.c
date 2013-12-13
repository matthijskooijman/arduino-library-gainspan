/**
 * @file GS_HAL.c
 *
 * Method implementations for the Hardware Abstraction Layer that are platform independent 
 */

#include "GS_HAL.h"

/** Public Method Implementation **/
void GS_HAL_init(void){

#ifdef GS_HAL_USE_SPI
  GS_HAL_spi_initialize();
#endif
  
#ifdef GS_HAL_USE_UART
  GS_HAL_uart_set_comm_port(115200);
#endif      
 
  MSTimerInit();
}


