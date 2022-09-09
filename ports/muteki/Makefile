# Include the core environment definitions; this will set $(TOP).
include ../../py/mkenv.mk

# Include py core make definitions.
include $(TOP)/py/py.mk
include $(TOP)/extmod/extmod.mk

CROSS_COMPILE ?= arm-none-bestaeabi-

# Set CFLAGS and libraries.
CFLAGS = -I. -I$(BUILD) -I$(TOP) -I$(TOP)/shared/readline
CFLAGS += -Wall -g -O2
CFLAGS += -DMICROPY_USE_READLINE=1
LIBS = -lm -lmutekix

# Define the required source files.
SRC_C = \
	main.c \
	mphalport.c

SHARED_SRC_C = $(addprefix shared/,\
	readline/readline.c \
	runtime/gchelper_generic.c \
	runtime/pyexec.c \
	runtime/stdout_helpers.c \
	)

SRC_QSTR += $(SRC_C) $(SHARED_SRC_C)

# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SHARED_SRC_C:.c=.o))

# Define the top-level target, the main firmware.
all: $(BUILD)/mpy.elf

# Define how to build the firmware.
$(BUILD)/mpy.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(Q)$(SIZE) $@

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk
