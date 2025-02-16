# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Iheaders

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = .
HEADER_DIR = headers

# Source and Object files
SRC_FILES = $(SRC_DIR)/AES.c $(SRC_DIR)/ECB.c $(SRC_DIR)/main.c $(SRC_DIR)/IMG.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ -ljpeg

# Compile the source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
