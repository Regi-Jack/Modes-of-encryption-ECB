CC = gcc
CFLAGS = -g
SOURCE_DIR = src
BUILD_DIR = build

# Define the source files
SOURCES = $(SOURCE_DIR)/ECB.c
# Define the object files
OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) aes

# Create build directory
$(BUILD_DIR):
	mkdir -pv $(BUILD_DIR)

# Compile AES binary
aes: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/aes $(OBJECTS)

# Compile individual source files into object files
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
