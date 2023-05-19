# Build Stage
FROM --platform=linux/amd64 ubuntu:22.04 as builder

## Install build dependencies.
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y clang


ADD . ./src

RUN cd /src && \
    clang fuzzer.cpp -o fuzzer -fsanitize=fuzzer

ENTRYPOINT []
CMD /src/fuzzer


