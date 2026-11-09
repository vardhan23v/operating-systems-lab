CC = gcc
CFLAGS = -Wall -Wextra -O2
PTHREAD_FLAGS = -pthread

PART_A_DIRS = Part-A/Program-1-execl-system-call \
              Part-A/Program-2-file-read-system-calls \
              Part-A/Program-3-fork-child-processes \
              Part-A/Program-4-file-write-system-calls \
              Part-A/Program-5-signal-handling \
              Part-A/Program-6-mutex-critical-section \
              Part-A/Program-7-binary-semaphores

PART_B_DIRS = Part-B/Program-1-fcfs-scheduling \
              Part-B/Program-2-sjf-scheduling \
              Part-B/Program-3-round-robin-scheduling \
              Part-B/Program-4-producer-consumer \
              Part-B/Program-5-bankers-algorithm

TARGETS = Part-A/Program-1-execl-system-call/main \
          Part-A/Program-2-file-read-system-calls/main \
          Part-A/Program-3-fork-child-processes/main \
          Part-A/Program-4-file-write-system-calls/main \
          Part-A/Program-5-signal-handling/main \
          Part-A/Program-6-mutex-critical-section/main \
          Part-A/Program-7-binary-semaphores/main \
          Part-B/Program-1-fcfs-scheduling/main \
          Part-B/Program-2-sjf-scheduling/main \
          Part-B/Program-3-round-robin-scheduling/main \
          Part-B/Program-4-producer-consumer/main \
          Part-B/Program-5-bankers-algorithm/main

.PHONY: all clean Part-A Part-B help

all: $(TARGETS)

# Part A Targets
Part-A/Program-1-execl-system-call/main: Part-A/Program-1-execl-system-call/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/Program-2-file-read-system-calls/main: Part-A/Program-2-file-read-system-calls/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/Program-3-fork-child-processes/main: Part-A/Program-3-fork-child-processes/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/Program-4-file-write-system-calls/main: Part-A/Program-4-file-write-system-calls/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/Program-5-signal-handling/main: Part-A/Program-5-signal-handling/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/Program-6-mutex-critical-section/main: Part-A/Program-6-mutex-critical-section/main.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

Part-A/Program-7-binary-semaphores/main: Part-A/Program-7-binary-semaphores/main.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

# Part B Targets
Part-B/Program-1-fcfs-scheduling/main: Part-B/Program-1-fcfs-scheduling/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-B/Program-2-sjf-scheduling/main: Part-B/Program-2-sjf-scheduling/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-B/Program-3-round-robin-scheduling/main: Part-B/Program-3-round-robin-scheduling/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-B/Program-4-producer-consumer/main: Part-B/Program-4-producer-consumer/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-B/Program-5-bankers-algorithm/main: Part-B/Program-5-bankers-algorithm/main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)
	find . -type f \( -name "*.out" -o -name "a.out" -o -name "*.o" \) -delete

help:
	@echo "Available commands:"
	@echo "  make all         - Compile all Part A and Part B programs"
	@echo "  make clean       - Remove all compiled binaries"
	@echo "  make <target>    - Build specific program binary (e.g., make Part-A/Program-1-execl-system-call/main)"
