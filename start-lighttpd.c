#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include <string.h>

void _halt(int code)
{
    __asm__ volatile ("mv a0, %0\n\r.word 0x0005006b"::"r"(code));

    // should not reach here during simulation
    printf("Exit with code = %d\n", code);

    // should not reach here on FPGA
    while(1);
}


void exec_command(const char * command, const char * envp[], int wait_flag)
{

    char buffer[128];
    strcpy(buffer, command);
    char *token;
    int count = 0;

    char * argv[64];

    token = strtok(buffer, " ");
    while (token != NULL) {
        argv[count] = token;
        count++;
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] == ' ') buffer[i] = '\0';
    }
    

    argv[count] = NULL;

    pid_t buffer_pid = fork();
    int buffer_status;

    assert(buffer_pid != -1);

    if (buffer_pid)
    {
        if (!wait_flag) return;
        printf("[Log]: Wait %s %s finished\n", argv[0], argv[1]);

        wait(&buffer_status);
    } else 
    {
        printf("[Log]: execve %s\n", argv[0]);

        int execve_buffer = execve(argv[0], argv, envp);

        // should not print
        printf("[ERROR] %s failed\n", argv[0]);

        return;
    }    

}



int main(char * argc, const char * argv[],const char * envp[])
{

    exec_command("/bin/busybox mount -t proc proc /proc", envp, 1);
    exec_command("/bin/busybox mount -t sysfs sysfs /sys", envp, 1);
    exec_command("/bin/busybox mount -t tmpfs tmpfs /tmp", envp, 1);
    exec_command("/bin/busybox mount -o remount,rw /dev/htifbd0 /", envp, 1);
    exec_command("/bin/busybox --install -s", envp, 1);
    exec_command("/bin/mkdir -p /dev/pts", envp, 1);
    exec_command("/sbin/mdev -s", envp, 1);


    exec_command("/bin/busybox ifconfig lo 127.0.0.1", envp, 1);
    exec_command("/bin/busybox route add -net 127.0.0.1 netmask 255.255.255.0 lo", envp, 1);
    exec_command("/bin/lighttpd -f /bin/lighttpd.conf -dasics", envp, 0);
    sleep(2);
    exec_command("/bin/busybox ps -a", envp, 1);
    exec_command("/bin/busybox wget http://127.0.0.1:8080/hello.txt", envp, 1);


    // _halt(0);
    while(1);

    return 0;
}