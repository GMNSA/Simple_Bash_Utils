#!/bin/bash

function run_docker() {
	docker rm -f cat_grep_tests 					&&
	docker rmi -f archlinux:base-20240101.0.204074  &&
	docker build -f ../build_docker/Dockerfile
		-t archlinux:base-20240101.0.204074 . 		&&
	docker run --name cat_grep_tests archlinux:base-20240101.0.204074
}

run_docker

