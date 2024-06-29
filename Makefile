# Compiler
CC = gcc

# Directories
LVGL_DIR = lvgl/src
SRC_DIR = src
INC_DIR = include

# Source files
LVGL_SOURCES = $(wildcard $(LVGL_DIR)/*.c)
PROJECT_SOURCES = $(wildcard $(SRC_DIR)/*.c)
SOURCES = $(LVGL_SOURCES) $(PROJECT_SOURCES)

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Include directories
INCLUDES = -I$(LVGL_DIR) -I$(SRC_DIR) -I$(INC_DIR) -Ilvgl

# Compiler flags
CFLAGS = -Wall -O3 $(INCLUDES)

# Linker flags
LDFLAGS = -lm

# Output executable
TARGET = project

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean