TARGET_EXEC ?= Lyx

BUILD_DIR ?= ./build
BUILD_DIR_TEST ?= ./build/test
SRC_DIRS ?= src/
SRC_DIRS_TEST ?= test/
CXX = g++

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -not -name test.cpp )
SRCS_TEST := $(shell find $(SRC_DIRS) $(SRC_DIRS_TEST) -name *.cpp -not -name main.cpp)
# $(info    SRCS_TEST is $(SRCS_TEST))

#OBJS := $(SRCS:%=%.o)
#DEPS := $(OBJS:.o=.d)

DEPS = $(shell find build/ -name *.d)
DEPS_TEST = $(shell find build/test/ -name *.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_DIRS_TEST := $(shell find $(SRC_DIRS) $(SRC_DIRS_TEST) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
INC_FLAGS_TEST := $(addprefix -I,$(INC_DIRS_TEST))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MD -MP -Wall -Wextra -Wfloat-equal -Wundef -Wunreachable-code -Wcast-qual
CPPFLAGS_TEST ?= $(INC_FLAGS_TEST) -MMD -MD -MP -Wall -Wextra -Wfloat-equal -Wundef -Wunreachable-code -Wcast-qual

#
# Debug build settings
#
DBGDIR := $(BUILD_DIR)/debug
DBGEXE := $(DBGDIR)/$(TARGET_EXEC)
DBGOBJS := $(SRCS:%=$(DBGDIR)/%.o)
DBGCFLAGS := $(CPPFLAGS) -g -O0 -ftrapv -DDEBUG

DBGDIR_TEST := $(BUILD_DIR_TEST)/debug
DBGEXE_TEST := $(DBGDIR_TEST)/$(TARGET_EXEC)
DBGOBJS_TEST := $(SRCS_TEST:%=$(DBGDIR_TEST)/%.o)
DBGCFLAGS_TEST := $(CPPFLAGS_TEST) -g -O0 -ftrapv -DDEBUG

#
# Release build settings
#
RELDIR := $(BUILD_DIR)/release
RELEXE := $(RELDIR)/$(TARGET_EXEC)_test
RELOBJS := $(SRCS:%=$(RELDIR)/%.o)
RELCFLAGS := $(CPPFLAGS) -O3 -Ofast -DRELEASE -DNDEBUG

RELDIR_TEST := $(BUILD_DIR_TEST)/release
RELEXE_TEST := $(RELDIR_TEST)/$(TARGET_EXEC)_test
RELOBJS_TEST := $(SRCS_TEST:%=$(RELDIR_TEST)/%.o)
RELCFLAGS_TEST := $(CPPFLAGS_TEST) -O3 -Ofast -DRELEASE -DNDEBUG

.PHONY: clean release debug run rund all remake test testd valgrind

all: release debug
remake: clean all

release: $(RELEXE)

$(RELEXE): $(RELOBJS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(RELOBJS) -o $@ $(LDFLAGS)

$(RELDIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(RELCFLAGS) -c $< -o $@

$(RELEXE_TEST): $(RELOBJS_TEST)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(RELOBJS_TEST) -o $@ $(LDFLAGS)

$(RELDIR_TEST)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(RELCFLAGS_TEST) -c $< -o $@


debug: $(DBGEXE)

$(DBGEXE): $(DBGOBJS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(DBGOBJS) -o $@ $(LDFLAGS)

$(DBGDIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(DBGCFLAGS) -c $< -o $@

$(DBGEXE_TEST): $(DBGOBJS_TEST)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(DBGOBJS_TEST) -o $@ $(LDFLAGS)

$(DBGDIR_TEST)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(DBGCFLAGS_TEST) -c $< -o $@


clean:
	$(RM) -r $(BUILD_DIR)

run: $(RELEXE)
	$(RELEXE)

rund: $(DBGEXE)
	$(DBGEXE)

test: $(RELEXE_TEST)
	$(RELEXE_TEST)

testd: $(DBGEXE_TEST)
	$(DBGEXE_TEST)

valgrind:
	valgrind --leak-check=full --undef-value-errors=no -v $(DBGEXE)

-include $(DEPS)

MKDIR_P ?= mkdir -p
