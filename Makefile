TARGET_EXEC := sudoku_mpi

BUILD_DIR ?= ./build
INC_DIRS := ./include
SRC_DIRS ?= ./src

CC := mpicc

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_FLAGS := $(addprefix -I , $(INC_DIRS))
LDFLAGS := $(shell $(CC) -showme:link)

CFLAGS := $(INC_FLAGS) --std=c99 -g -Wall

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
		$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
