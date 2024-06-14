CC=gcc
LDFLAGS=-std=c17 # -g -Wall -Werror -Wextra
EXECUTABLE=f_cat

CC_VERSION := $(shell $(CC) --version | head -n 1 | awk '{print $$3}')
TARGET_VERSION := 14.1.1

COMPARE_VERSION = $(shell \
				  if [ "$(CC_VERSION)" = "$(TARGET_VERSION)" ]; then \
					  echo "OK" \
				  else \
					  echo NO; \
				  fi \
				  )

.PHONY: all f_cat rebuild check clean test check_gcc

all: check_gcc f_cat
	./f_cat

check_gcc:
	@if [ "$(CC_VERSION)" = "$(TARGET_VERSION)" ]; then \
		echo "GCC Success"; \
	else \
		echo "GCC --version must be $(TARGET_VERSION). \n -- Run Docker    bash run.sh -- "; \
		exit 1; \
	fi

f_cat: check_gcc ./srcs/main.c ./srcs/f_cat.c
	$(CC) $(LDFLAGS) ./srcs/main.c ./srcs/f_cat.c -o $(EXECUTABLE)

rebuild: clean f_cat

check:
	clang-format -n includes/*.h srcs/*.c

clean:
	rm -f $(EXECUTABLE) CPPLINT.cfg ./tests/log.txt ./log.txt

test: rebuild
	cp f_cat ./tests/f_cat
	cd ./tests && bash test_cat.sh bytes.txt
	rm ./tests/f_cat
