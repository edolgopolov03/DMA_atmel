#include "dma_m2m_main.h"
#include "atmel_start.h"
#include "atmel_start_pins.h"
#include "driver_examples.h"

int main(void)
{

  atmel_start_init();

  dma_usart_copy();
  //write_to_usart("hello world!");
  //USART_0_example();
}
