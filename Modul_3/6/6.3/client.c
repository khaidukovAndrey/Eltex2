#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

unsigned short csum(unsigned short *ptr, int nbytes)
{
    register long sum;
    unsigned short oddbyte;
    register short answer;

    sum = 0;
    while (nbytes > 1)
    {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1)
    {
        oddbyte = 0;
        *((unsigned char *)&oddbyte) = *(unsigned char *)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum = sum + (sum >> 16);
    answer = (short)~sum;

    return (answer);
}

int main(int argc, char *argv[])
{
    int s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (s == -1)
    {
        perror("Error socket");
        exit(1);
    }
    char str[100];
    char datagram[256], *data;
    memset(datagram, 0, 256);

    struct iphdr *iph = (struct iphdr *)datagram;
    struct udphdr *udph = (struct udphdr *)(datagram + sizeof(struct iphdr));
    struct sockaddr_in sin;

    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    scanf("%s", str);
    strcpy(data, str);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(80);
    sin.sin_addr.s_addr = inet_addr(argv[1]);

    // Fill IP Header
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(data);
    iph->id = htonl(55555);
    iph->frag_off = 0;
    iph->ttl = 64;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;
    iph->saddr = inet_addr(argv[1]);
    iph->daddr = sin.sin_addr.s_addr;

    iph->check = csum((unsigned short *)datagram, iph->tot_len);
    printf("%u\n", iph->check);
    printf("%u\n", iph->tot_len);
    // UDP header
    udph->source = htons(6543);
    udph->dest = htons(atoi(argv[2]));
    udph->len = htons(8 + strlen(data));
    udph->check = 0;

    if (sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0)
        perror("Error sendto");
    else
        printf("Packet Send. Length : %d \n", iph->tot_len);
        
    return 0;
}