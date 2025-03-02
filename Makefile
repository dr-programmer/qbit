TARGET_EXEC := qbit

SRC_DIR := .
BUILD_DIR := ./build

SRCS := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.s' -or -name '*.l' -or -name '*.y')
SRCS += $(shell find $(SRC_DIR) -name '*.cu')
SRCS := $(filter-out $(SRC_DIR)/%.l.c $(SRC_DIR)/%.y.c, $(SRCS))
SRCS := $(filter-out $(SRC_DIR)/%.qsm.c, $(SRCS))
SRCS := $(sort $(SRCS))

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.c.o)
OBJS := $(OBJS:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.s.o)
OBJS := $(OBJS:$(SRC_DIR)/%.l=$(BUILD_DIR)/%.l.c.o)
OBJS := $(OBJS:$(SRC_DIR)/%.y=$(BUILD_DIR)/%.y.c.o)
OBJS := $(OBJS:$(SRC_DIR)/%.cu=$(BUILD_DIR)/%.cu.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) -lm -lcudart

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.s.o: $(SRC_DIR)/%.s
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.l.c.o: $(SRC_DIR)/%.l
	mkdir -p $(dir $@)
	flex -o $<.c $<
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<.c -o $@

$(BUILD_DIR)/%.y.c.o: $(SRC_DIR)/%.y
	mkdir -p $(dir $@)
	bison --defines=$(dir $<)token.h --output=$<.c --graph=$<.dot -v $<
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<.c -o $@

$(BUILD_DIR)/%.cu.o: $(SRC_DIR)/%.cu
	mkdir -p $(dir $@)
	-nvcc $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean clean-all build-lib clean-lib run-tests
clean:
	rm -f -r $(BUILD_DIR)

CLEAN_FILES := $(shell find $(SRC_DIR) -name '*.l.c' -or -name '*.y.c')
CLEAN_FILES += $(shell find $(SRC_DIR) -name '*.dot' -or -name '*.output')
CLEAN_FILES += $(shell find $(SRC_DIR) -name 'token.h')

clean-all:
	rm -f -r $(BUILD_DIR)
	rm -f $(CLEAN_FILES)

LIB_OBJ := $(shell find $(BUILD_DIR)/simulator -name '*.o')
LIB_OBJ += $(shell find $(BUILD_DIR)/smart_allocation -name '*.o')

LIB := $(BUILD_DIR)/lib$(TARGET_EXEC).a

build-lib: $(LIB)

$(LIB): $(LIB_OBJ)
	ar rcs $(LIB) $(LIB_OBJ)

clean-lib:
	rm -f $(LIB)

TESTS := $(shell find $(SRC_DIR)/q_assembly/test_cases -name '*.qsm')
TESTS := $(subst $(SRC_DIR)/q_assembly/test_cases/,,$(TESTS))
TESTS := $(sort $(TESTS))

CUDA_REQ := test_8.qsm

TEST_FLAGS := --cuda

ifeq ($(TEST_FLAGS),)
	TESTS := $(filter-out $(CUDA_REQ), $(TESTS))
endif

run-tests:
	cd $(SRC_DIR)/q_assembly/test_cases; \
	for test in $(TESTS); do \
		../../$(BUILD_DIR)/$(TARGET_EXEC) $$test $(TEST_FLAGS); \
	done

-include $(DEPS)