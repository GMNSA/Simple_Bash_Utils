.PHONY:  all cat_test cat_check grep_test grep_check clean

all: cat_check grep_check cat_test grep_test

cat_test:
	cd ./cat && make test

cat_check:
	cd ./cat && make check

grep_test:
	cd ./grep && make test

grep_check:
	cd ./grep && make check

clean:
	cd ./cat && $(MAKE) clean
	cd ./grep && $(MAKE) clean
