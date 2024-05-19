#!/bin/sh
./configure --prefix=$PWD/../lighttpd-install --host=riscv64 --with-pcre --with-openssl --enable-shared CC=riscv64-unknown-linux-gnu-gcc CXX=riscv64-unknown-linux-gnu-g++ CFLAGS=-g CPPFLAGS=-g

make -j`nproc`
make install

