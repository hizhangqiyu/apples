#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define N 64

// data struct of shared memory
typedef struct
{
    pid_t pid;
    char buf[N];
} SHM;

// signal handler
void handler(int signo)
{
    printf("reader: get signal\n");
    return;
}

int main()
{
    key_t key;  // ipc id, same between different processes
    int shmid;  // shared memory id
    SHM *p;     // pointer of data
    pid_t pid;  // process id

    // ftok(file path, id)
    if ((key = ftok(".", 'm')) < 0)
    {
        perror("fail to ftok");
        exit(-1);
    }

    // user defined signal handler
    signal(SIGUSR1, handler);
    // shmget(ipc id, memory size, flags)
    if ((shmid = shmget(key, sizeof(SHM), 0666|IPC_CREAT|IPC_EXCL)) < 0)// create sm and report error if sm exist already.
    {
        if (EEXIST == errno)
        {
            shmid = shmget(key, sizeof(SHM), 0666);
            // attach sm, shmat(sm id, addr, flag:read&write)
            p = (SHM *)shmat(shmid, NULL, 0);
            pid = p->pid;
            p->pid = getpid();
            // signal process, not kill it
            kill(pid, SIGUSR1);
        }
        else
        {
            perror("fail to shmget");
            exit(-1);
        }
    }
    else
    {
        p = (SHM *)shmat(shmid, NULL, 0);
        // initial pid
        p->pid = getpid();
        pause();
        pid = p->pid;
    }

    while ( 1 )
    {
        pause();
        if (strcmp(p->buf, "quit\n") == 0) exit(0);
        printf("read from shm : %s", p->buf);
        // signal process, not kill it
        kill(pid, SIGUSR1);
    }

    return 0;


}