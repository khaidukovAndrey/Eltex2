#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>", argv[0]);
        exit(1);
    }

    int port = atoi(argv[1]);
    int sockfd; /* Дескриптор сокета */
    int n; /* Переменные для различных длин и количества символов */
    socklen_t clilen;
    char line[1000]; /* Массив для принятой и отсылаемой строки */
    struct sockaddr_in servaddr, cliaddr; /* Структуры для адресов сервера и клиента */
/* Заполняем структуру для адреса сервера */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
/* Создаем UDP сокет */
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror(NULL); /* Печатаем сообщение об ошибке */
        exit(1);
    }/* Настраиваем адрес сокета */
    if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    while (1) {
/* Основной цикл обслуживания*/
        clilen = sizeof(cliaddr);
/* Ожидаем прихода запроса от клиента и читаем его */
        if ((n = recvfrom(sockfd, line, 999, 0,
                          (struct sockaddr *) &cliaddr, &clilen)) < 0) {
            perror(NULL);
            close(sockfd);
            exit(1);
        }
/* Печатаем принятый текст на экране */
        printf("%s\n", line);
/* Принятый текст отправляем обратно по адресу отправителя */
        if (sendto(sockfd, line, strlen(line), 0,
                   (struct sockaddr *) &cliaddr, clilen) < 0) {
            perror(NULL);
            close(sockfd);
            exit(1);
        } /* Уходим ожидать новую датаграмму*/
    }
    return 0;
}