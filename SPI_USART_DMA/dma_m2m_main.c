#include "atmel_start.h"
#include "dma_m2m_main.h"
#include "dma_memory.h"
#include <stdint.h>

#define MAX_BUF 50

static volatile uint8_t dma_complete_flag;
static void             M2M_DMA_0_complete_cb(void)
{
  dma_complete_flag = 1;
}

int32_t write_to_usart(const uint8_t *buf){
  struct io_descriptor *io;
  usart_sync_get_io_descriptor(&USART_0, &io);
  usart_sync_enable(&USART_0);

  return io_write(io, buf, strlen(buf));
}

int32_t  dma_write_memory(void *dst, const uint8_t *str){
  int32_t err;
  size_t len = strlen(str);
  for(int i = 0; i < len; i++){
    err = dma_memset(dst, str[i], sizeof(uint8_t));
    if(err){
      printf("dma_memset() failed: %s\n", strerror(errno));
      return DMA_MEMORY_ERROR_CB;
    }
    dst++;
  }
  return ERR_NONE;
}

int32_t  dma_usart_copy(){
  int32_t err;
  err = dma_memory_init();
  if(err){
    printf("dma_memory_init() failed: %s\n", strerror(errno));
  }

  uint8_t *buf1 = malloc(MAX_BUF * sizeof(uint8_t));
  uint8_t *buf2 = malloc(MAX_BUF * sizeof(uint8_t));
  
  err = dma_write_memory(buf1, (uint8_t *)"hello world!");
  if(err){
    return DMA_MEMORY_ERROR_CB;
  }
  
  err = dma_memcpy(buf2, buf1, 12);
  if(err){
    printf("dma_memcpy() failed: %s\n", strerror(errno));
    return DMA_MEMORY_ERROR_CB;
  }
  
  M2M_DMA_0_complete_cb();

  write_to_usart(buf2);
  return ERR_NONE;
}