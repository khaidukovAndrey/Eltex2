#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
    pid_t pid;
    int pipefd[2];
    int f;
    int t, buf;

    f = creat("f.txt", 0666);
    close(f);

    if (pipe(pipefd) == -1)
    {
        perror("Error pipe");
        exit(EXIT_FAILURE);
    }

    struct sembuf sem;
    sem.sem_flg = 0;
    sem.sem_num = 0;
    key_t key;
    key = ftok("/etc/fstab",0);
    int sem_id = semget(key, 1, IPC_CREAT | 0644);
    if (sem_id == -1)
    {
        perror("Error semget");
        exit(EXIT_FAILURE);
    }
    switch (pid = fork())
    {
    case -1:
        perror("Error fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
        srand(time(NULL));
        int seek = 0;
        int symT = 0;
        close(pipefd[0]);
        for (int i = 0; i < 10; i++)
        {

            t = rand() % 100;
            printf("Дочерний записал %d\n", t);
            write(pipefd[1], &t, sizeof(int));

            sem.sem_op = -1;
            semop(sem_id, &sem, 1);

            f = open("f.txt", O_RDONLY);
            char buf_s[10];

            while (read(f, buf_s, sizeof(buf_s)) > 0)
            {
                printf("%s", buf_s);
            }

            close(f);
        }
        close(pipefd[1]);
        break;
    default:
        close(pipefd[1]);
        for (int i = 0; i < 10 && read(pipefd[0], &buf, sizeof(buf)) > 0; i++)
        {
            printf("Родитель прочитал %d\n", buf);
            buf = buf * 2;
            f = open("f.txt", O_APPEND | O_WRONLY);

            char buf_s[10];
            sprintf(buf_s, "%d\n", buf);
            write(f, buf_s, sizeof(buf_s));

            sem.sem_op = 1;
            semop(sem_id, &sem, 1);
            close(f);
        }
        close(pipefd[0]);
        wait(NULL);

        printf("Результат работы программы записан в файл `%s`\n", "f.txt");
        break;
    }
    exit(EXIT_SUCCESS);
}