CC=gcc
CFLAGS=-std=c17 # -g -Wall -Werror -Wextra
EXECUTABLE=f_grep

# -- -------------------------------------------- --

SOURCES=srcs/main.c srcs/f_grep.c
OBJECTS=$(addprefix objects/, $(subst srcs/,,$(SOURCES:.c=.o)))

HEADERS=./includes

# -- -------------------------------------------- --

.PHONY: all rebuild test check clean check_dir_objects check_gcc

# -- -------------------------------------------- --

CC_VERSION := $(shell $(CC) --version | head -n 1 | awk '{print $$3}')
TARGET_VERSION := 14.1.1

COMPARE_VERSION = $(shell \
				  if [ "$(CC_VERSION)" = "$(TARGET_VERSION)" ]; then \
					  echo "OK" \
				  else \
					  echo NO; \
				  fi \
				  )

# -- -------------------------------------------- --

all: check_gcc check_dir_objects build

build: $(EXECUTABLE) $(OBJECTS)

check_gcc:
	@if [ "$(CC_VERSION)" = "$(TARGET_VERSION)" ]; then \
		echo "GCC Success"; \
	else \
		echo "GCC --version must be $(TARGET_VERSION). \n -- Run Docker    make docker_run -- "; \
		exit 1; \
	fi

check_dir_objects:
	mkdir -p objects

rebuild: clean all

check:
	clang-format -n includes/*.h srcs/*.c

test: rebuild
	cd ./tests && bash test_grep.sh

clean:
	rm -f ./tests/log.txt ./log.txt $(EXECUTABLE)
	rm -rf ./objects/

objects/%.o: srcs/%.c
	@echo "Compiling: --> " $< -o $@
	$(CC) -I $(HEADERS) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	@echo "Linking: " -- -c $(OBJECTS) -o $(EXECUTABLE)
	@echo "OBJECTS: " $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)
