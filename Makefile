CC = gcc
CFLAGS = -Wall -Wextra -O2
PTHREAD_FLAGS = -pthread

PART_A_DIRS = Part-A/A1-exec-system-call \
              Part-A/A2-file-read-system-calls \
              Part-A/A3-fork-child-processes \
              Part-A/A4-file-write-system-calls \
              Part-A/A5-signal-handling \
              Part-A/A6-mutex-critical-section \
              Part-A/A7-binary-semaphores

PART_B_DIRS = Part-B/B1-fcfs-scheduling \
              Part-B/B2-sjf-scheduling \
              Part-B/B3-round-robin-scheduling \
              Part-B/B4-producer-consumer \
              Part-B/B5-bankers-algorithm

TARGETS = Part-A/A1-exec-system-call/main \
          Part-A/A2-file-read-system-calls/main \
          Part-A/A3-fork-child-processes/main \
          Part-A/A4-file-write-system-calls/main \
          Part-A/A5-signal-handling/main \
          Part-A/A6-mutex-critical-section/main \
          Part-A/A7-binary-semaphores/main \
          Part-B/B1-fcfs-scheduling/main \
          Part-B/B2-sjf-scheduling/main \
          Part-B/B3-round-robin-scheduling/main \
          Part-B/B4-producer-consumer/main \
          Part-B/B5-bankers-algorithm/main

.PHONY: all clean Part-A Part-B help

all: $(TARGETS)

# Part A Targets
Part-A/A1-exec-system-call/main: Part-A/A1-exec-system-call/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/A2-file-read-system-calls/main: Part-A/A2-file-read-system-calls/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/A3-fork-child-processes/main: Part-A/A3-fork-child-processes/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/A4-file-write-system-calls/main: Part-A/A4-file-write-system-calls/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/A5-signal-handling/main: Part-A/A5-signal-handling/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-A/A6-mutex-critical-section/main: Part-A/A6-mutex-critical-section/main.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

Part-A/A7-binary-semaphores/main: Part-A/A7-binary-semaphores/main.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

# Part B Targets
Part-B/B1-fcfs-scheduling/main: Part-B/B1-fcfs-scheduling/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-B/B2-sjf-scheduling/main: Part-B/B2-sjf-scheduling/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-B/B3-round-robin-scheduling/main: Part-B/B3-round-robin-scheduling/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-B/B4-producer-consumer/main: Part-B/B4-producer-consumer/main.c
	$(CC) $(CFLAGS) $< -o $@

Part-B/B5-bankers-algorithm/main: Part-B/B5-bankers-algorithm/main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)
	find . -type f \( -name "*.out" -o -name "a.out" -o -name "*.o" \) -delete

help:
	@echo "Available commands:"
	@echo "  make all         - Compile all Part A and Part B experiments"
	@echo "  make clean       - Remove all compiled binaries"
	@echo "  make <target>    - Build specific experiment binary (e.g., make Part-A/A1-exec-system-call/main)"
