/*
 * 检查一下你对select函数的理解，请修改图12-6的服务器，使得它在主服务器的每次迭代中最多只回送一个文本行
 * answer:
 * 目前仅支持单client，
 * 依据12-6，将listenfd准备好读时建立并执行echo()
 * 拆解为listenfd准备好读时建立连接，connfd准备好读时输出，当获得字符为0时关闭连接
 * 使用connected控制client数量
 */

#include "csapp.h"
void echo(int connfd);
size_t echoOneLine(int connfd);
void command(void);

int main(int argc, char **argv) {
	int listenfd, connfd, port;
	int connected = 0;
	socklen_t clientlen = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	fd_set read_set, ready_set;
	struct timeval timeout;
	
	timeout.tv_sec = 0;   
    timeout.tv_usec = 0;  
	
	//检查指令
	if(argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		return 0;
	}
	//监听端口
	port = atoi(argv[1]);
	listenfd = Open_listenfd(port);
	
	//对读集合进行处理
	FD_ZERO(&read_set);
	FD_SET(STDIN_FILENO, &read_set);
	FD_SET(listenfd, &read_set);
	
	//服务器主循环
	while(1) {
		ready_set = read_set; //重置集合去除select函数副作用
		if(connected) {
			FD_SET(connfd, &read_set);
			Select(connfd+1, &ready_set, NULL, NULL, &timeout);
		} else {
			Select(listenfd+1, &ready_set, NULL, NULL, &timeout);
		}
		
		
		if(FD_ISSET(STDIN_FILENO, &ready_set)) { //本地准备好读
			command();
		}
		if((!connected) && FD_ISSET(listenfd, &ready_set)) { //准备好连接
			connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
			connected = 1;
			puts("Built connection");
		}
		if(connected && FD_ISSET(connfd, &ready_set)) {  //client准备好读
			puts("Ok to read");
			if(!echoOneLine(connfd)) {
				puts("Closed connection");
				Close(connfd);
				FD_CLR(connfd, &read_set);
				connected = 0;
			}
		}
	}
	
	return 0;	
}

size_t echoOneLine(int connfd) {
	size_t n;
	char buf[MAXLINE];
	rio_t rio;
	
	Rio_readinitb(&rio, connfd);
	if(n = Rio_readlineb(&rio, buf, MAXLINE)){
		printf("server recieved %d bytes: %s", n, buf);
		Rio_writen(connfd, buf, n);
	}
	
	return n;
}

void echo(int connfd) {
	size_t n;
	char buf[MAXLINE];
	rio_t rio;
	
	Rio_readinitb(&rio, connfd);
	while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
		printf("server recieved %d bytes: %s", n, buf);
		Rio_writen(connfd, buf, n);
	}
}

void command(void) {
	char buf[MAXLINE];
	if(!Fgets(buf, MAXLINE, stdin)) {
		exit(0);
	}
	
	printf("%s", buf);
}
