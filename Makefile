.PHONY:all clean rebuild

CC := g++
MKDIR := mkdir 
RM := rm -fr

DIR_BUILD := build
DIR_INC := ./
DIR_OBJS := $(DIR_BUILD)/objs
DIR_DEPS := $(DIR_BUILD)/deps
DIR_TARGET := $(DIR_BUILD)/target
DIRS := $(DIR_OBJS) $(DIR_TARGET) $(DIR_DEPS)

TYPE_SRC := .cpp
TYPE_OBJ := .o
TYPE_DEP := .dep

TARGET := $(DIR_TARGET)/exe.out
MAKEFILE := Makefile

SRCS := $(wildcard *$(TYPE_SRC))
OBJS := $(SRCS:%$(TYPE_SRC)=%$(TYPE_OBJ))
OBJS := $(addprefix $(DIR_OBJS)/,$(OBJS))
DEPS := $(SRCS:%$(TYPE_SRC)=%$(TYPE_DEP))
DEPS := $(addprefix $(DIR_DEPS)/,$(DEPS))

$(TARGET): $(DIRS) $(OBJS) 
	$(CC) -o $@ $(OBJS)

include $(DEPS)
ifeq ("$(wildcard $(DIRS))","")
$(DIR_DEPS)/%$(TYPE_DEP):$(DIRS) %$(TYPE_SRC) $(MAKEFILE)
else
$(DIR_DEPS)/%$(TYPE_DEP):%$(TYPE_SRC) $(MAKEFILE)
endif
	$(CC) -I $(DIR_INC) -MM -E $(filter %$(TYPE_SRC), $^) | sed 's,\(.*\)\.o[ :]*,$(DIR_DEPS)/\1.o $@:,g' > $@

$(DIR_OBJS)/%$(TYPE_OBJ):%$(TYPE_SRC)
	$(CC) -o $@ -c $(filter %$(TYPE_SRC), $^)

$(DIRS):
	$(MKDIR) -p $@

rebuild: clean $(TARGET)

clean:
	$(RM) $(DIR_BUILD)



