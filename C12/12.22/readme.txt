gcc client.c csapp.c csapp.h -o echoClient -pthread && ./echoClient 127.0.00.1 8111
gcc select.c csapp.c csapp.h -o echoServerByIO -pthread && ./echoServerByIO 8111

要带上编译选项-lpthread或-pthread以链接POSIX thread库
