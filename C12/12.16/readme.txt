gcc hello.c csapp.c csapp.h -o hellothread -lpthread && ./hellothread n
gcc hello.c csapp.c csapp.h -o hellothread -pthread && ./hellothread n

要带上编译选项-lpthread或-pthread以链接POSIX thread库
