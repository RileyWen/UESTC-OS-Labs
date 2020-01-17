#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int child;
    char *args[] = {"/bin/echo", "Hello", "World!", NULL};

    if (!(child = fork()))
    {
        // child
        printf("pid %d: %d is my father\n", getpid(), getppid());
        execve("/bin/echo", args, NULL);
        printf("pid %d: I'm back! Something went wrong!\n", getpid());
    }
    else {
        int myself = getpid();
        printf("pid %d: %d is my child process\n", myself, child);
        wait4(child, 0, 0, 0);
        printf("pid %d: child has been raped.\n", myself);
    }
    return 0;
}
