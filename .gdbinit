
file ./src/lighttpd

#b _start
target remote:1234




#b _check_dasics


b main

b _dasics_entry_stage1

b dynamic_hook

add-symbol-file ~/riscv/riscv64-unknown-linux-gnu-ycy/sysroot/lib/ld-linux-riscv64-lp64d.so.1 0x2140

// add-symbol-file ./src/.libs/mod_h2.so -s .plt 0x2000415560
// add-symbol-file ./src/.libs/mod_h2.so 0x2000415950
// add-symbol-file ./src/.libs/mod_openssl.so -s .plt 0x200042c350
// add-symbol-file ./src/.libs/mod_openssl.so 0x200042cfe0
// add-symbol-file ~/riscv/riscv64-unknown-linux-gnu/sysroot/usr/lib/libssl.so.3 0x200044e050
// add-symbol-file ~/riscv/riscv64-unknown-linux-gnu/sysroot/usr/lib/libcrypto.so.3 -s .plt 0x20000df760
// add-symbol-file ~/riscv/riscv64-unknown-linux-gnu/sysroot/usr/lib/libcrypto.so.3 0x20000dfee0
// add-symbol-file ~/riscv/riscv64-unknown-linux-gnu-ycy/sysroot/lib/libc.so.6 0x82a5a0
// add-symbol-file ~/riscv/riscv64-unknown-linux-gnu/sysroot/usr/lib/libpcre.so.1 0x20000030d0

add-symbol-file ~/riscv/riscv64-unknown-linux-gnu-ycy/sysroot/lib/libc.so.6 0x20003fb5a0

c
