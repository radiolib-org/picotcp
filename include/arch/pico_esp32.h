#ifndef _INCLUDE_PICO_ESP32
#define _INCLUDE_PICO_ESP32

#include <stdio.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pico_constants.h"

#include "freertos/FreeRTOS.h"
#include "esp_timer.h"

/* -------------- DEBUG ------------- */

#define dbg(...)
//#define dbg             printf

/* -------------- MEMORY ------------- */
extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv );

#define pico_free   vPortFree
//#define pico_free   free

static inline void *pico_zalloc(size_t size)
{
    void *ptr = (void *)pvPortMalloc(size);
    //void *ptr = (void *)malloc(size);

    if(ptr)
        memset(ptr, 0u, size);

    return ptr;
}

/* -------------- TIME ------------- */

static inline pico_time PICO_TIME_MS(void)
{
    return((unsigned long)(esp_timer_get_time() / 1000ULL));
}

static inline pico_time PICO_TIME(void)
{
    return PICO_TIME_MS() / 1000;
}

static inline void PICO_IDLE(void)
{
    uint32_t now = PICO_TIME_MS();
    while (now == PICO_TIME_MS())
        ;
}

#endif
