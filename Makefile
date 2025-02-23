# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Directories
SRC_DIR = src
BUILD_DIR = build
HEADERS_DIR = headers
OUTPUT_DIR = output

# Source and Object Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = main  # This is the final output binary

# Build the executable
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE) $(OUTPUT_DIR)/enc_image.pgm

.PHONY: all clean
