# Compiler settings
CC = gcc
CFLAGS = -g -Wall

# Directories for source, build, and object files
SRC_DIR = src
BUILD_DIR = build

# Sources
SRC = $(SRC_DIR)/ECB.c $(SRC_DIR)/AES.c  # Add AES.c to the source files

# Object files - specify the build directory for the object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Executable
EXEC = $(BUILD_DIR)/aes

# Compilation rules
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Rule for creating object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(BUILD_DIR)/*.o $(EXEC)
