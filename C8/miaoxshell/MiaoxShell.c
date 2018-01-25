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
#include "JobManage.c"

#define MAXLINE 1024
#define MAXARGS 128

void eval(char *cmdline);
int parse(char *buf, char **argv);
int isBuiltin(char **argv);
void handler(int sig);
void closeALL(int sig);
void suppendALL(int sig);
void printProcessExitInfo(pid_t pid, int status);

extern char **environ;
pid_t currentPid = 0; //当前前台进程组id
int argc;

int main() {
	char cmdline[MAXLINE];
	
	puts(" ------------------------------------- ");
	puts("|                                     |");
	puts("|              MiaoxShell             |");
	puts("|     Create by Miaox, 2017-05-22     |");
	puts("|                                     |");
	puts(" ------------------------------------- ");

	signal(SIGINT, closeALL);
	signal(SIGTSTP, suppendALL);
	signal(SIGCHLD, handler);
	
	while(1) {
		printf("> ");
		
		//取得输入
		fgets(cmdline, MAXLINE, stdin);
		if(feof(stdin)) { //读到文件流末尾就退出
			exit(0);      //要引入stdlib.h
		}

		//求值并执行
		eval(cmdline);
	}
	
	return 0;
}

/**
 * 对命令行求值并执行
 */
void eval(char *cmdline) {
	char *argv[MAXARGS]; //对命令行的参数解析
	char buf[MAXLINE];   //保存原始的命令行
	
	int bg;              //是否背景执行
	pid_t pid;           //创建的进程id
	int status;

	strcpy(buf, cmdline);//保存原有的cmdline
	
	//将cmdline解析到argv数组
	bg = parse(buf, argv);
	
	if(argv[0] == NULL) { //参数为空则返回
		return;
	} else {
		if(!isBuiltin(argv)) { //非内建命令
		
			pid = fork();
			
			if(pid == 0) { //子进程
				if(execve(argv[0], argv, environ) < 0) { //执行失败
					printf("%s: %s\n", argv[0], strerror(errno));
					exit(0);
				}
			} else { //父进程
				//设置子进程pgid
				setpgid(pid, pid);
				printJob(addJob(pid, getpgid(pid), argv[0], bg , cmdline));
			
				if(!bg) { //前台执行
					currentPid = pid;
					if(waitpid(-currentPid, &status, WUNTRACED)>0) {
						//判断子进程的状态
						printProcessExitInfo(currentPid, status);
					
						puts("fg: collect success");
					} else {
						puts("fg: collect failure");
					}
					
					signal(SIGCHLD, handler); //恢复后台子进程回收
					currentPid = 0;
				} else { 
					//后台执行
				}
			}
		}
	}
	
	return;
}

/**
 * 将buf解析到argv数组
 */
int parse(char *buf, char **argv) {
	char *delim;
	int bg;

	buf[strlen(buf)-1] = ' ';//替换换行符为空格
	//删除命令行前的空格
	while(*buf && (*buf == ' ')) {
		buf++;
	}
	
	argc = 0;
	while((delim = strchr(buf, ' '))) { //获取以空格为分节符的位置
		argv[argc++] = buf; //第argc个参数为buf
		*delim = '\0';      //将分节符位置插入'\0'，截断buf后面内容
		buf =delim + 1;     //更新buf的开始位置
		
		//忽略开头的空格
		while(*buf && (*buf == ' ')) {
			buf++;
		}
	}
	argv[argc] = NULL; //最后一个argc为NULL
	
	if(argc == 0) { //argv数组为空
		return 1;
	} else {
		if((bg = (*argv[argc-1] == '&')) != 0) { //最后一个为&
			argv[--argc] = NULL; //清除
		}
		
		return bg;
	}
}

int isBuiltin(char **argv) {
	pid_t pid;
	unsigned int jid;
	int status;

	if(!strcmp(argv[0], "quit")) {
		exit(0);
	} else if(!strcmp(argv[0], "exit")) {
		exit(0);
	} else if(!strcmp(argv[0], "jobs")) {
		dumpJobs();
		return 1;
	} else if(!strcmp(argv[0], "&")) {
		return 1; //忽略&
	} else if(!strcmp(argv[0], "fg")) { //在前台重启暂停的子进程
		if(argc != 2) {
			puts("fg [pid|jid]");
		} else {
			if(argv[1][0] == '%') { //jid
				sscanf(argv[1]+1, "%u", &jid);
				pid = getPidByJid(jid);
				if(pid == -1) {
					printf("jid %d not exist!\n", jid);
					return 1;
				}
			} else { //pid
				sscanf(argv[1], "%d", &pid);
			}
			
			if(isJobExist(pid) == 0) {
				signal(SIGCHLD, SIG_DFL);
				kill(-pid, SIGCONT);
				
				if(waitpid(-pid, &status, 0)>0) {
					printProcessExitInfo(pid, status);
				
					puts("fg: collect success");
				} else {
					printf("fg: collect failure, %s", strerror(errno));
				}
				
				signal(SIGCHLD, handler);
			} else {
				printf("pid %d not exist or able to run!\n", pid);
			}
		}
		
		return 1;
	} else if(!strcmp(argv[0], "bg")) { //在后台重启暂停的子进程
		if(argc != 2) {
			puts("bg [pid|jid]");
		} else {
			if(argv[1][0] == '%') { //jid
				sscanf(argv[1]+1, "%u", &jid);
				pid = getPidByJid(jid);
				if(pid == -1) {
					printf("jid %d not exist!\n", jid);
					return 1;
				}
			} else { //pid
				sscanf(argv[1], "%d", &pid);
			}
			
			if(isJobExist(pid) == 0) {
				kill(-pid, SIGCONT);
				printf("pid %d reboot!\n", pid);
			} else {
				printf("pid %d not exist or able to run!\n", pid);
			}
		}
		
		return 1;
	} else {
		return 0; //不是内建命令
	}
}

void handler(int sig) {
	pid_t pid;
	int status;
	
	
	while((pid = waitpid(-1, &status, 0)) > 0) {
		//判断子进程的状态
		printProcessExitInfo(pid, status);
	}
	
	if(errno != ECHILD) {
		//产生非ECHILD错误
		puts("bg: waitpid error");
	}
	
	return;
}

void closeALL(int sig) {
	// 发送信号SIGINT给前台进程组
	if(currentPid>0) {
		printf("Sending SIGINT To Front %d\n", -currentPid);
		
		signal(SIGCHLD, SIG_DFL); //隐患，在回收前台进程组时无法回收后台组
		kill(-currentPid, SIGINT);
		
		puts("sending ok!");
	} else {
		puts("No Front");
	}
	
	return;
}

void suppendALL(int sig) {
	// 发送信号SIGTSTP给前台进程组
	if(currentPid>0) {
		printf("Sending SIGTSTP To Front %d\n", -currentPid);
		
		signal(SIGCHLD, SIG_DFL); //隐患，在回收前台进程组时无法回收后台组
		kill(-currentPid, SIGSTOP);
		
		puts("sending ok!");
	} else {
		puts("No Front");
	}
	
	return;
}

void printProcessExitInfo(pid_t pid, int status) {
	if(WIFEXITED(status)) {
		printf("process-%d exit: %d\n", pid, WEXITSTATUS(status));
		deleteJob(currentPid);
	} else if(WIFSIGNALED(status)) {
		printf("process-%d terminated by signal: %d\n", pid, WTERMSIG(status));
		deleteJob(currentPid);
	} else if(WIFSTOPPED(status)) {
		printf("process-%d signal num: %d\n", pid, WSTOPSIG(status));
		if(WSTOPSIG(status) == 19) {
			setJobStopped(pid);
		} else {
			deleteJob(pid);
		}
	}
}
