#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
  {
    perror("socket");
    exit(1);
  }

  struct sockaddr_in servaddr, claddr, cliaddr[10];
  socklen_t len = sizeof(claddr);
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1]));

  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
  {
    perror("bind");
    exit(1);
  }

  char buffer[BUFFER_SIZE];
  int n;
  int curCountAddr = 0;
  /*// Receive first message to determine client addresses
  int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cliaddr1, &len1);
  if (n < 0) {
      perror("recvfrom");
      exit(1);
  }
  cliaddr2 = cliaddr1;

  printf("Client 1 connected: %s:%d\n", inet_ntoa(cliaddr1.sin_addr), ntohs(cliaddr1.sin_port));

  // Receive second message to confirm client addresses
  n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cliaddr2, &len2);
  if (n < 0) {
      perror("recvfrom");
      exit(1);
  }

  if (cliaddr1.sin_addr.s_addr != cliaddr2.sin_addr.s_addr || cliaddr1.sin_port == cliaddr2.sin_port) {
      fprintf(stderr, "Error: clients are not distinct\n");
      exit(1);
  }

  printf("Client 2 connected: %s:%d\n", inet_ntoa(cliaddr2.sin_addr), ntohs(cliaddr2.sin_port));

  printf("Chat started\n");*/
  int newClFlg = 1;
  int numOfSender = 0;
  while (1)
  {
    newClFlg = 1;
    // Receive message from client 1
    n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&claddr, &len);
    if (n < 0)
    {
      perror("recvfrom");
      continue;
    }
    for (int i = 0; i < curCountAddr; i++)
    {
      if (claddr.sin_addr.s_addr == cliaddr[i].sin_addr.s_addr && claddr.sin_port == cliaddr[i].sin_port)
      {
        newClFlg = 0;
        numOfSender = i;
        break;
      }
    }
    if (newClFlg)
    {
      cliaddr[curCountAddr] = claddr;
      numOfSender = curCountAddr;
      curCountAddr++;
    }

    buffer[n] = '\0';
    for (int i = 0; i < curCountAddr; i++)
    {
      if (i != numOfSender)
      {
        if (sendto(sockfd, buffer, n, 0, (struct sockaddr *)&cliaddr[i], sizeof(cliaddr[i])) < 0)
        {
          perror("sendto");
          continue;
        }
      }
    }
  }
  close(sockfd);
  return 0;
}