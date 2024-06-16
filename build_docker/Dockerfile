FROM archlinux:base-20240101.0.204074

RUN pacman -Sy --noconfirm  \
        openssl \
        git \
        git-lfs \
        curl \
        bash \
        make \
        gcc \
        diffutils \
        python \
        valgrind \
        cppcheck \
    && pacman -Scc --noconfirm

RUN mkdir /test

COPY . /project
COPY build_docker/run_tests.sh /project/

WORKDIR "/project"

ENTRYPOINT ["/bin/bash","run_tests.sh"]
