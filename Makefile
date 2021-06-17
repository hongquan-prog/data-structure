.PHONY:all clean

BUILD_DIR := build
SRC_DIR := .
INC_DIR := .
DEP_DIR := $(BUILD_DIR)

TARGET := obj
TARGET := $(addprefix $(BUILD_DIR)/, $(TARGET))

SRC_TYPE := .cpp
INC_TYPE := .h
OBJ_TYPE := .o
DEP_TYPE := .dep

SRCS := $(wildcard $(SRC_DIR)/*$(SRC_TYPE))
OBJS := $(SRCS:$(SRC_TYPE)=$(OBJ_TYPE))
OBJS := $(notdir $(OBJS))
OBJS := $(addprefix $(BUILD_DIR)/, $(OBJS))
DEPS := $(OBJS:$(OBJ_TYPE)=$(DEP_TYPE))

CC := g++
MKDIR := mkdir -p
RM := rm -fr

vpath $(SRC_TYPE) $(SRC_DIR)
vpath $(INC_TYPE) $(INC_DIR)

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) -I $(INC_DIR) -o $@ $^

$(BUILD_DIR)/%$(OBJ_TYPE):%$(SRC_TYPE)
	$(CC) -I $(INC_DIR) -o $@ -c $(filter %$(SRC_TYPE), $^)

$(BUILD_DIR):
	$(MKDIR) $@
	
include $(DEPS)
ifeq ("$(wildcard $(BUILD_DIR))","")
$(BUILD_DIR)/%$(DEP_TYPE):$(BUILD_DIR) %$(SRC_TYPE)
else
$(BUILD_DIR)/%$(DEP_TYPE):%$(SRC_TYPE)
endif
	$(CC) -I $(INC_DIR) -MM -E $(filter %$(SRC_TYPE), $^) | sed 's,\(.*\)\.o[ :]*,$(BUILD_DIR)/\1.o $@ :,g' > $@

clean:
	$(RM) $(BUILD_DIR)



