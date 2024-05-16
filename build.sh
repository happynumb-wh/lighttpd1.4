#!/bin/sh
./configure --prefix=$PWD/../lighttpd-install --host=riscv64 --with-pcre --with-openssl CC=riscv64-unknown-linux-gnu-gcc CXX=riscv64-unknown-linux-gnu-g++

make -j`nproc`
make install

