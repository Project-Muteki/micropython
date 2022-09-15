#include <unistd.h>
#include <sys/time.h>
#include <muteki/threading.h>
#include <mutekix/console.h>

#include "py/mpconfig.h"

// Receive single character, blocking until one is available.
int mp_hal_stdin_rx_chr(void) {
    return mutekix_console_getchar();
}

// Send the string of given length.
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    int r = mutekix_console_write(str, len);
    (void)r;
}

#ifndef mp_hal_ticks_ms
mp_uint_t mp_hal_ticks_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
#endif

#ifndef mp_hal_ticks_us
mp_uint_t mp_hal_ticks_us(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}
#endif

#ifndef mp_hal_time_ns
uint64_t mp_hal_time_ns(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000000ULL + (uint64_t)tv.tv_usec * 1000ULL;
}
#endif

#ifndef mp_hal_delay_ms
void mp_hal_delay_ms(mp_uint_t ms) {
    while (ms > 0x7fff) {
        OSSleep(0x7fff);
        ms -= 0x7fff;
    }
    if (ms > 0) {
        OSSleep(ms);
    }
}
#endif

#ifndef mp_hal_delay_us
void mp_hal_delay_us(mp_uint_t us) {
    mp_hal_delay_ms(us / 1000);
}
#endif
