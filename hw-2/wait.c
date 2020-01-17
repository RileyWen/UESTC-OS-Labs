#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>

#define print_parent(Pid) printf("[parent-pid:%d]: ", Pid)
#define print_child(Pid) printf("[child-pid:%d]: ", Pid)

int main()
{
    pid_t pid;
    pid = fork();
    if (fork < 0)
        exit(1);
    else if (!fork) {
        print_parent(pid);
        printf("waiting for child to finish......\n");
        pid_t child_pid = waitpid()
    }
    else {
        int sum = 0;
        for (int i = 1; i <= 1000000; i++)
            sum += i;
        print_child(pid);
        printf("Calculation completed.");
    }
    return 0;
}
