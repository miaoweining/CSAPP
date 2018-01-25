#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

extern char **environ;
pid_t pid;


void aaa(int sig) {
	kill(-pid, sig);
}

int main() {
	int status;
	
	pid = fork();
	if(pid == 0) { //子进程
		
		if(execve("/root/bar", NULL, environ) < 0) { //执行失败
			printf("%s\n", strerror(errno));
			exit(0);
		}
	
	} else {
		signal(SIGTSTP, aaa);
		signal(SIGINT, aaa);
		setpgid(pid, pid);
		if(waitpid(-pid, &status, WUNTRACED) < 0) {
			printf("error:%s\n", strerror(errno));
		} else { //成功回收
			printf("sucess get %d\n", pid);
			
			if (WIFEXITED(status)) {
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("continued\n");
            }
		}
	}
	
	return 1;
}
