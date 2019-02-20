# https://blogs.msdn.microsoft.com/vcblog/2018/12/13/using-multi-stage-containers-for-c-development/

FROM alpine:latest as build

LABEL description="Build container - rabbitmqcppexample"

RUN apk update && apk add --no-cache \ 
    autoconf build-base binutils cmake curl file gcc g++ git libgcc libtool linux-headers make musl-dev ninja tar unzip wget openssl 

RUN cd /tmp \
    && wget https://github.com/Microsoft/CMake/releases/download/untagged-fb9b4dd1072bc49c0ba9/cmake-3.11.18033000-MSVC_2-Linux-x86_64.sh \
    && chmod +x cmake-3.11.18033000-MSVC_2-Linux-x86_64.sh \
    && ./cmake-3.11.18033000-MSVC_2-Linux-x86_64.sh --prefix=/usr/local --skip-license \
    && rm cmake-3.11.18033000-MSVC_2-Linux-x86_64.sh

RUN cd /tmp \
    && git clone https://github.com/Microsoft/vcpkg.git -n \ 
    && cd vcpkg \
    && git checkout 1d5e22919fcfeba3fe513248e73395c42ac18ae4 \
    && ./bootstrap-vcpkg.sh -useSystemBinaries

COPY x64-linux-musl.cmake /tmp/vcpkg/triplets/

RUN VCPKG_FORCE_SYSTEM_BINARIES=1 ./tmp/vcpkg/vcpkg install openssl librabbitmq

COPY ./src /src
WORKDIR /src
RUN mkdir out \
    && cd out \
    && cmake .. -DCMAKE_TOOLCHAIN_FILE=/tmp/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux-musl \
    && make

FROM alpine:latest as runtime

LABEL description="Run container - rabbitmqcppexample"

RUN apk update && apk add --no-cache \ 
    libstdc++

COPY --from=build /src/out/rabbitmqcppexample /usr/local/rabbitmqcppexample/rabbitmqcppexample

WORKDIR /usr/local/rabbitmqcppexample

CMD ./rabbitmqcppexample

EXPOSE 80