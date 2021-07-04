MKDIR := mkdir
RM := rm -r
CC := g++
CFLAGS := $(addprefix -I,$(DIR_INC))

ifeq ($(DEBUG), true)
CFLAGS += -g
endif

LFLAGS := 