/*
 * 编写hello.c（图12-13）的一个版本，它创建和回收n个可结合的对等线程，其中n是一个命令行参数 
 */

#include "csapp.h"
void *thread(void *vargp);

int main(int argc, char **argv) {
	int i, t_num;
	pthread_t *tid_list;
	
	//判断参数是否正确
	if(argc != 2) {
		puts("[error] hellothread <thread num>");
		
		return 0;
	}

	t_num = atoi(argv[1]);
		
	//判断参数是否合法
	if(t_num <= 0) {
		puts("[error] thread num must be number which bigger than 0 !");
		
		return 0;
	}
	
	//建立线程id记录区
	tid_list = (pthread_t *)malloc((sizeof(pthread_t)) * t_num);
	
	//创建线程
	for(i=0; i<t_num; i++) {
		Pthread_create(&tid_list[i], NULL, thread, NULL);
		printf("[notice] create thread %d: tid %u\n", i, tid_list[i]);
	}
	
	//回收线程
	for(i=0; i<t_num; i++) {
		Pthread_join(tid_list[i], NULL);
		printf("[notice] recovery thread %d: tid %u\n", i+1, tid_list[i]);
	}
	
	return 0;
}

void *thread(void *vargp) {
	printf("Hello, world!\n");
	
	return NULL;
}
