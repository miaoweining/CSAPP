struct job {
	pid_t pid;         //进程id
	pid_t pgid;        //进程组id
	unsigned int jid; //作业id
	char *name;        //作业名称，argv[0]
	int bg;            //是否背景执行
	int status;        //状态
	char *cmd;         //启动的命令行语句
	struct job *next;
};
struct job *jobList=NULL, *last=NULL; //指向作业链表头与末尾
unsigned int jobId = 0; //当前jid

struct job *addJob(pid_t pid, pid_t pgid, char *name, int bg, char *cmd);
void printJob(struct job *job);
void dumpJobs();
void deleteJob(pid_t pid);
pid_t getPidByJid(unsigned int jid);
void setJobStopped(int pid);
int isJobExist(pid_t pid);

/**
 * 添加一个作业记录到job列表中，返回此次添加作业记录的位置，last指向其下一个作业记录
 */
struct job *addJob(pid_t pid, pid_t pgid, char *name, int bg, char *cmd) {
	struct job *temp;
	
	temp = (struct job *)malloc(sizeof(struct job));
	temp->jid  = ++jobId;
	temp->pid  = pid;
	temp->pgid = pgid;
	temp->name = (char *)malloc(strlen(name)+1);
	strcpy(temp->name, name);
	temp->bg     = bg;
	temp->status = 1;
	temp->cmd    = (char *)malloc(strlen(cmd)+1);
	strcpy(temp->cmd, cmd);
	
	if(jobList == NULL) { 
		jobList = temp;
		last    = temp;
	} else {
		last->next = temp;
		last = temp;
	}
	
	return temp;
}

void printJob(struct job *job) {
	printf("[%d] %d-%d %s %d %d %s",
		job->jid,
		job->pid,
		job->pgid,
		job->name,
		job->status,
		job->bg,
		job->cmd
	);
}

void dumpJobs() {
	struct job *temp;
	temp = jobList;
	
	if(temp == NULL) {
		puts("No Jobs!");
	} else {
		// 列出所有作业
		while(temp) {
			printJob(temp);
			temp = temp->next;
		}
	}
}

void setJobStopped(int pid) {
	struct job *temp;
	temp = jobList;
	
	//遍历链表
	while(temp) {
		if(temp->pid == pid) {
			temp->status = 0;
			break;
		}
		
		temp = temp->next;
	}
}

void deleteJob(pid_t pid) {
	struct job *temp;
	temp = jobList;
	
	//遍历链表
	while(temp) {
		if(temp->pid == pid) {
			temp->status = -1;
			break;
		}
		
		temp = temp->next;
	}
}

pid_t getPidByJid(unsigned int jid) {
	struct job *temp;
	temp = jobList;
	pid_t result = -1;
	
	//遍历链表
	while(temp) {
		if(temp->jid == jid) {
			result = temp->pid;
			break;
		}
		
		temp = temp->next;
	}
	
	return result;
}

int isJobExist(pid_t pid) {
	struct job *temp;
	temp = jobList;
	
	//遍历链表
	while(temp) {
		if(temp->pid == pid) {
			return temp->status;
			break;
		}
		
		temp = temp->next;
	}
	
	return -1;
}
