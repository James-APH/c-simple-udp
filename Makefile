#
#
# Info for compiler:
# (I like lots of information if stuff goes wrong)
#
CC=gcc
CFLAGS=-std=c23 -Wall -Wextra

#
#
# Directory variables:
#
#
BUILD_DIR = build/
SOURCE_DIR = src/

#
#
# Commands:
#
#
all: client server

client: $(BUILD_DIR)/client.o
	$(CC) $^ -o $@

server: $(BUILD_DIR)/server.o
	$(CC) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) client server

.PHONY: all clean

#
#
# Build instructions:
#
#
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(BUILD_DIR)/client.o: $(SOURCE_DIR)/client.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/server.o: $(SOURCE_DIR)/server.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
