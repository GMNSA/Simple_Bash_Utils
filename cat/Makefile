CC=gcc
LDFLAGS=-std=c11 -g -Wall -Werror -Wextra
EXECUTABLE=s21_cat

.PHONY: all s21_cat rebuild check clean test

all: s21_cat
	./s21_cat

s21_cat: ./srcs/main.c ./srcs/s21_cat.c
	$(CC) $(LDFLAGS) ./srcs/main.c ./srcs/s21_cat.c -o $(EXECUTABLE)

rebuild: clean s21_cat

check:
	# python3 ../../materials/linters/cpplint.py --extensions=c includes/*.h srcs/*.c
	clang-format -n includes/*.h srcs/*.c

clean:
	rm -f $(EXECUTABLE) CPPLINT.cfg ./tests/log.txt ./log.txt

test: rebuild
	cp s21_cat ./tests/s21_cat
	cd ./tests && bash test_cat.sh bytes.txt
	rm ./tests/s21_cat
