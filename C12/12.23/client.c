#include "csapp.h"
#include <unistd.h>

int main(int argc, char **argv) {
	int clientfd, port, i;
	char *host, buf[MAXLINE];
	rio_t rio;
	
	if(argc !=3) {
		printf("%s <host> <port>\n", argv[0]);
		exit(0);
	}
	
	host = argv[1];
	port = atoi(argv[2]);
	
	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);

	// 不断发送信息
	i = 50;
	while(i--) {
		Rio_writen(clientfd, "test!", strlen("test!"));
		sleep(5);
	}

	/*
	while(Fgets(buf, MAXLINE, stdin) != NULL) {
		Rio_writen(clientfd, buf, strlen(buf));
		Rio_readlineb(&rio, buf, MAXLINE);
		Fputs(buf, stdout);
	}
	*/
	
	Close(clientfd);

	return 0;
}


