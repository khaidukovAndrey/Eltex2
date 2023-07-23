#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid;
    uid_t uid;
    gid_t gid;

    pid = getpid();
    printf("Результат вызова getpid: %d\n", pid);
    printf("Результат вызова getppid: %d\n", getppid());
    printf("Результат вызова getsid: %d\n", getsid(pid));

    uid = getuid();
    printf("Результат вызова getuid: %u\n", uid);
    printf("Результат вызова geteuid: %u\n", geteuid());
    
    gid = getgid();
    printf("Результат вызова getgid: %u\n", gid);
    return 0;
}
