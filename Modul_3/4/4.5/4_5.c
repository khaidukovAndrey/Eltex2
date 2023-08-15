#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>

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

    sem_t *sem;

    if ((sem = sem_open("sem", O_CREAT, 0644, 0)) == SEM_FAILED) {
        perror("Error sem_open");
        exit(1);
    }
    
    switch (pid = fork())
    {
    case -1:
        perror("Error fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
        srand(time(NULL));
        close(pipefd[0]);
        for (int i = 0; i < 10; i++)
        {

            t = rand() % 100;
            printf("Дочерний записал %d\n", t);
            write(pipefd[1], &t, sizeof(int));

            sem_wait(sem);

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
            close(f);
            sem_post(sem);
        }
        close(pipefd[0]);
        wait(NULL);

        printf("Результат работы программы записан в файл `%s`\n", "f.txt");
        break;
    }
    exit(EXIT_SUCCESS);
}