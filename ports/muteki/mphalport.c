#include <unistd.h>
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

