#include <stdio.h>



#define ATTR_ULIB_TEXT __attribute__((section(".ulibtext")))
#define ATTR_ULIB_DATA __attribute__((section(".ulibdata")))

#define ATTR_UFREEZONE_TEXT __attribute__((section(".ufreezonetext")))
#define ATTR_UFREEZONE_DATA __attribute__((section(".ufreezonedata")))

void _halt(int code)
{
    __asm__ volatile ("mv a0, %0\n\r.word 0x0005006b"::"r"(code));

    // should not reach here during simulation
    printf("Exit with code = %d\n", code);

    // should not reach here on FPGA
    while(1);
}

int ATTR_ULIB_TEXT do_nothing()
{
    printf("untrusted area call printf\n");
    return 0;
}


int main()
{
    do_nothing();
    do_nothing();
    do_nothing();
    do_nothing();
    do_nothing();
    do_nothing();
    do_nothing();
    do_nothing();
    do_nothing();
    do_nothing();
    _halt(0);
    return 0;
}


