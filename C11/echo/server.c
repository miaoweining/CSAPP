#include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv) {
	int listenfd, connfd, clientlen, port;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp;
	
	if(argc !=2) {
		printf("%s <port>\n", argv[0]);
		exit(0);
	}
	port = atoi(argv[1]);
	
	listenfd = Open_listenfd(port);

	while(1) {
		clientlen = sizeof(clientaddr);
		connfd    = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		
		hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
							sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(clientaddr.sin_addr);
		
		printf("server connected to %s (%s)\n", hp->h_name, haddrp);
		
		echo(connfd);
		Close(connfd);
	}

	exit(0);
}

void echo (int connfd) {
	size_t n;
	char buf[MAXLINE];
	rio_t rio;
	
	Rio_readinitb(&rio, connfd);
	while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
		printf("server recieved %d bytes\n", n);
		Rio_writen(connfd, buf, n);
	}
}
