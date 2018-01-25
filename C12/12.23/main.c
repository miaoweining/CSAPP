#include "csapp.h"

// 定义连接池
typedef struct {
    int maxfd;                    // 在读集合中最大描述符
    fd_set read_set;              // 读集合
    fd_set ready_set;             // 准备好读的集合
    int nready;                   // select 检测到准备好的描述符数目
    int maxi;                     // clientfd 数组的最大索引
    int clientfd[FD_SETSIZE];     // 连接描述符数组
    rio_t clientrio[FD_SETSIZE];  // 对应连接描述符的读缓冲区数组    
} pool;

int byte_cnt = 0;                        // 服务器已接收/发送的字节数
void init_pool(int listenfd, pool *p);   // 初始化连接池
void add_client(int connfd, pool *p);    // 添加连接到连接池
void check_clients(pool *p);             // 检查连接：读写就绪或断开

int main(int argc, char **argv) {
    int listenfd, connfd, port;
    //struct timeval time;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    static pool pool;

    // 设置 Select 的超时时间
    //time.tv_sec = 0;
    //time.tv_usec = 0;

    // 验证输入
    if(argc != 2) { 
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);

    // 建立监听
    listenfd = Open_listenfd(port);

    // 初始化连接池
    init_pool(listenfd, &pool); 

    // 服务器循环
    while(1) {
        // 重置各个连接的状态
        pool.ready_set = pool.read_set;

        // 监听，返回准备好读的数量
        pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);

        // 准备好连接
        if(FD_ISSET(listenfd, &pool.ready_set)) {
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            printf("Built connection %d\n", connfd);
            add_client(connfd, &pool); // 将连接加入连接池中监听
        }

        // 检查连接池内各个连接描述符是否可读
        check_clients(&pool);
    }

    return 0;
}

void init_pool(int listenfd, pool *p) {
    int i;
    p->maxi = -1; // clientfd 数组的最大索引设为 -1，即为空
    for(i=0; i<FD_SETSIZE; i++) {
        p->clientfd[i] = -1; // 将 clientfd 数组中的所有元素设为 -1，-1 代表空槽位
                             // 监听描述符不记录进入 clientfd 数组
    }

    p->maxfd = listenfd; // 将监听描述符设为当前的最大描述符
    FD_ZERO(&p->read_set); // 读集合清空
    FD_SET(listenfd, &p->read_set); // 将监听描述符加入读集合
}

void add_client(int connfd, pool *p) {
    int i;
    p->nready--; // 若为增加client，即监听描述符可用，减一是为了不计入监听描述符

    // 遍历 clientfd 找到一个空槽位
    for(i=0; i<FD_SETSIZE; i++) {
        if(p->clientfd[i] < 0){
            p->clientfd[i] = connfd;                 // 记录连接描述符到数组
            Rio_readinitb(&p->clientrio[i], connfd); // 将连接描述符和读缓冲区联系起来
            FD_SET(connfd, &p->read_set);            // 将连接描述符加入监听

            // 设置当前最大连接描述符 maxfd
            if(connfd > p->maxfd) {
                p->maxfd = connfd;
            } 

            // 设置数组当前最大索引 maxi
            if(i > p->maxi) {
                p->maxi = i;
            }

            break;
        }
    }

    if(i==FD_SETSIZE) {
        app_error("add_client error: Too many clients");
    }
}

void check_clients(pool *p) {
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    // 循环进行的条件是 索引 i 未超过最大索引，且可读数量大于零
    for(i=0; (i <= p->maxi) && (p->nready > 0); i++) {
        // 设置此次循环的可读连接描述符和相应的读缓冲区
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) { // 可读
            p->nready--; //减少可读数量

            // key：使用 read() 代替 rio_readlineb 或其他 rio 包内的函数
            if((n=read(connfd, buf, MAXLINE)) != 0) { // 读缓冲区不为空  
                printf("---- Server start read fd:%d\n", connfd);
                byte_cnt += n; // 记录总共读的字节数量
                printf("Server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
                Rio_writen(connfd, buf, n); // echo 回客户端
                printf("---- Server finish read fd:%d\n", connfd);
            } else { // 可读但读缓冲区为空，即 EOF 断开连接
                printf("Closed connection %d\n", connfd);
                Close(connfd); // 关闭连接描述符
                FD_CLR(connfd, &p->read_set); // 清除此连接描述符的监听
                p->clientfd[i] = -1; // 将此链接描述符在 clientfd 中的位位置置为 -1
            }
        }
    }
}