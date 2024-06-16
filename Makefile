.PHONY:  all cat_test cat_check grep_test grep_check clean docker_run

all: cat_check grep_check cat_test grep_test

cat_test:
	cd ./cat && make test

cat_check:
	cd ./cat && make check

docker_run:
	docker rm -f cat_grep_tests && docker rmi -f alpine_cat_grep:1.0 && docker build -f build_docker/Dockerfile -t alpine_cat_grep:1.0 . && docker run --name cat_grep_tests alpine_cat_grep:1.0

grep_test:
	cd ./grep && make test

grep_check:
	cd ./grep && make check

clean:
	cd ./cat && $(MAKE) clean
	cd ./grep && $(MAKE) clean
