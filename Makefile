# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -lrt -g
TARGET = concurrent-http-server

# Source files (update these as you create more files)
SOURCES = src/main.c \
          src/master.c \
          src/worker.c \
          src/http.c \
          src/config.c \
          src/thread_pool.c \
          src/cache.c \
          src/logger.c \
          src/stats.c

# Object files (will be in current directory)
OBJECTS = $(SOURCES:src/%.c=%.o)

# Default target - build the server
all: $(TARGET)

# Create the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(CFLAGS)
	@echo "Build successful! Run ./$(TARGET) to start the server"

# Compile .c files to .o files
%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build and run the server
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete"

# Run tests
test: $(TARGET)
	@echo "Running tests..."
	# Add your test commands here later
	# ./tests/test_load.sh

# Check for required tools
deps:
	@echo "Checking dependencies..."
	@which ab >/dev/null || echo "Apache Bench (ab) not found - install with: sudo apt-get install apache2-utils"
	@which valgrind >/dev/null || echo "Valgrind not found - install with: sudo apt-get install valgrind"
	@which curl >/dev/null || echo "curl not found - install with: sudo apt-get install curl"
	@which gdb >/dev/null || echo "gdb not found - install with: sudo apt-get install gdb"

# Debug build with extra flags
debug: CFLAGS += -DDEBUG -O0
debug: clean $(TARGET)

# Release build with optimization
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# Run with valgrind for memory checking
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

# Run with helgrind for thread checking
helgrind: $(TARGET)
	valgrind --tool=helgrind ./$(TARGET)

# Run with gdb debugger
debug-run: $(TARGET)
	gdb ./$(TARGET)

# Show file sizes (useful for optimization)
size: $(TARGET)
	@size $(TARGET)
	@echo "---"
	@ls -lh $(TARGET)

# Show help
help:
	@echo "=== Concurrent HTTP Server Makefile ==="
	@echo "Available targets:"
	@echo "  all       - Build the server executable (default)"
	@echo "  run       - Build and start the server"
	@echo "  clean     - Remove object files and executable"
	@echo "  test      - Run automated tests"
	@echo "  deps      - Check for required dependencies"
	@echo "  debug     - Build with debug flags"
	@echo "  release   - Build with optimization flags"
	@echo "  valgrind  - Run with memory checking"
	@echo "  helgrind  - Run with thread error detection"
	@echo "  debug-run - Run with gdb debugger"
	@echo "  size      - Show executable size information"
	@echo "  help      - Show this help message"

.PHONY: all run clean test deps debug release valgrind helgrind debug-run size help