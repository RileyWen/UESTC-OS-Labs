/* reaping children through SIGCHLD */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

int reaped = 0;

void reaper(int sig) {
    int status;
    struct rusage usage;

    pid_t pid2 = wait3(&status, 0, &usage);

    printf("\n");
    printf("got SIGCHLD, cleaning up!\n");
    printf("...child of %d done calling cat.\n",getpid());
    printf("exit code for %d is %d\n", pid2, status);
    printf("total user seconds: %lf\n",
            (double) usage.ru_utime.tv_sec +
            (double) usage.ru_utime.tv_usec / (double) 1000000);
    printf("total system seconds: %lf\n",
            (double) usage.ru_stime.tv_sec +
            (double) usage.ru_stime.tv_usec / (double) 1000000);

    reaped = 1;  // I reaped it, so I can exit myself.
}

int main()
{
    pid_t pid1;
    int status;
    struct rusage usage;

    signal(SIGCHLD,reaper);

    if ( pid1 = fork() ) {
        printf("I am parent %d; child is %d\n",getpid(),pid1);
    }
    else {
        printf("[child]: calculating...\n");
        int sum = 0;
        for (int i = 0; i < 900000000; i++)
            sum += i;
        _exit(0);
    }

    while (!reaped)
    {
        printf("[parent]: waiting...\n");
        sleep(1);
    }

    signal(SIGCHLD,SIG_DFL);

    return 0;
}
