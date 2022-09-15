#include <unistd.h>
#include "py/mpconfig.h"

#define MP_HAL_RETRY_SYSCALL(ret, syscall, raise) while (0)

static inline mp_uint_t mp_hal_ticks_cpu(void) { return 0; }
static inline void mp_hal_set_interrupt_char(char c) {}
int mp_hal_stdin_rx_chr(void);
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);
mp_uint_t mp_hal_ticks_ms(void);
mp_uint_t mp_hal_ticks_us(void);
uint64_t mp_hal_time_ns(void);
void mp_hal_delay_ms(mp_uint_t ms);
void mp_hal_delay_us(mp_uint_t us);
