.PHONY: all clean

SRCS := $(wildcard $(DIR_SRC)/*$(TYPE_SRC))
SRCS := $(notdir $(SRCS))
OBJS := $(SRCS:$(TYPE_SRC)=$(TYPE_OBJ))
DEPS := $(SRCS:$(TYPE_SRC)=$(TYPE_DEP))
OBJS := $(addprefix $(DIR_BUILD)/,$(OBJS))
DEPS := $(addprefix $(DIR_BUILD)/,$(DEPS))

all: $(DIR_BUILD) $(APP)

$(APP):$(OBJS)
	$(CC) -o $@ $^

-include $(DEPS)
ifeq ("$(wildcard $(DIR_BUILD))","")
$(DIR_BUILD)/%$(TYPE_DEP):$(DIR_BUILD) %$(TYPE_SRC)
else
$(DIR_BUILD)/%$(TYPE_DEP):%$(TYPE_SRC)
endif
	$(CC) $(CFLAGS) -MM -E $(filter %$(TYPE_SRC), $^) | sed 's,\(.*\)\.o[ :]*,$(DIR_BUILD)/\1.o $@:,g' > $@

$(DIR_BUILD)/%$(TYPE_OBJ):%$(TYPE_SRC)
	$(CC) $(CFLAGS) -o $@ -c $(filter %$(TYPE_SRC), $^)

$(DIR_BUILD):
	$(MKDIR) $@

clean:
	$(RM) $(DIR_BUILD)
