#include <stdlib.h>
#include <mutekix/console.h>

#include "py/builtin.h"
#include "py/compile.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "py/stackctrl.h"

#include "extmod/vfs.h"
#include "extmod/vfs_posix.h"

#include "shared/runtime/gchelper.h"
#include "shared/runtime/pyexec.h"

#define HEAP_SIZE_MIN (1*1024*1024)

int main(int argc, char **argv) {
    mutekix_console_init(NULL);
    atexit(&mutekix_console_fini);

    // Allocate memory for the MicroPython GC heap.
    char *heap = malloc(HEAP_SIZE_MIN);
    if (heap == NULL) {
        return 1;
    }

    // Initialise the MicroPython runtime.
    mp_stack_ctrl_init();
    gc_init(heap, heap + HEAP_SIZE_MIN);
    mp_init();

    #if MICROPY_VFS_POSIX
    {
        // Mount the host FS at the root of our internal VFS
        mp_obj_t args[2] = {
            mp_type_vfs_posix.make_new(&mp_type_vfs_posix, 0, 0, NULL),
            MP_OBJ_NEW_QSTR(MP_QSTR__slash_),
        };
        mp_vfs_mount(2, args, (mp_map_t *)&mp_const_empty_map);
        MP_STATE_VM(vfs_cur) = MP_STATE_VM(vfs_mount_table);
    }
    #endif

    // Start a normal REPL; will exit when ctrl-D is entered on a blank line.
    pyexec_friendly_repl();

    // Deinitialise the runtime.
    gc_sweep_all();
    mp_deinit();

    free(heap);
    return 0;
}

// Handle uncaught exceptions (should never be reached in a correct C implementation).
void nlr_jump_fail(void *val) {
    for (;;) {
    }
}

// Do a garbage collection cycle.
void gc_collect(void) {
    gc_collect_start();
    gc_helper_collect_regs_and_stack();
    gc_collect_end();
}
