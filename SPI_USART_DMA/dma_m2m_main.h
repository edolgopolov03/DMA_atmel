#ifndef DMA_M2M_MAIN_H
#define DMA_M2M_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <dma_memory.h>
#include "dma_memory_config.h"
#include "driver_init.h"
#include <stdint.h>
#include <utils_assert.h>
#include <utils.h>
#include <hal_atomic.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t write_to_usart(const uint8_t *buf);

int32_t  dma_write_memory(void *dst, const uint8_t *str);

int32_t dma_usart_copy();


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DMA_M2M_MAIN_H */
