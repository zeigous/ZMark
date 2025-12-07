# Compiler
CXX := g++

SRC_DIR := src
INCLUDE_DIR := src/include
OBJ_DIR := obj

# Output executable
TARGET := simulator

LIBS := -llua

CXXFLAGS := -I$(INCLUDE_DIR) -std=c++23 -Wall -Wextra -O2

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")

OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS) | 
	$(CXX) $(OBJS) -o $@ $(LIBS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

.PHONY: all clean
