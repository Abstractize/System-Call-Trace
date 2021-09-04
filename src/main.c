#include "main.h"

char *get_from_argv(const char *compare, int argc, char *argv[])
{
    for (int counter = 0; counter < argc; counter++)
    {
        if (!strcmp(compare, argv[counter]))
            return argv[counter + 1];
    }
    return "";
}

void get_program_and_args(char *program_dest, char* dest[], int argc, char *argv[])
{
    int args_count = 0;
    int counter = 1;
    int name_flag = 1;
    while (counter < argc)
    {
        if (strcmp("--mode", argv[counter]) && strcmp("--filter", argv[counter]))
        {
        	if(args_count == 0 && name_flag)
        	{
        		strcpy(program_dest, argv[counter]);
        		name_flag = 0;
        	}
        	else
        	{
        		dest[args_count] = malloc((strlen(argv[counter]) + 1) * sizeof(char));
        		strcpy(dest[args_count], argv[counter]);
        		args_count++;
        	}
        }
        else
            counter++;
        counter++;
    }
}

void get_syscall(int syscall_num, char *syscall_name) {
	char command[25];
	snprintf(command, 25, "ausyscall %d", syscall_num);
	FILE *name_syscall = popen(command, "r");
	fgets(syscall_name, sizeof(syscall_name), name_syscall);
	syscall_name[strcspn(syscall_name, "\n")] = 0;
	pclose(name_syscall);
}

void exec_fork(char *program, char* argv[], char *mode, char *filter)
{
	 int status;
	 pid_t pid;
	 int syscalls[547]= {0};
	 struct user_regs_struct regs;
	 int counter = 0;
	 int in_call =0;
	 char syscall_name[256];
	 int interact_flag = 0;

	 if(!strcmp(mode, "interactive"))
		 interact_flag = 1;


	 switch(pid = fork()){
	   case -1:
	     perror("fork");
	     exit(1);
	   case 0: /* in the child process */
	     ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	     execvp(program, argv);
	     break;
	   default: /* in the parent process */
	     wait(&status);
	     while(status == 1407){
	       ptrace(PTRACE_GETREGS, pid, NULL, &regs);
	       if(!in_call){
			 get_syscall(regs.orig_rax, syscall_name);
	         printf("Executed syscall %s\n",syscall_name);
	         syscalls[regs.orig_rax]++;
	         in_call=1;
	         counter ++;
	       }
	       else{
	    	 if(interact_flag)
	    		   getchar();
	         in_call = 0;
	       }
	     ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
	     wait(&status);
	     }
	   }
	   printf("+---------------+-------+-------+\n");
	   printf("|Syscall\t|Number\t|Amount\t|\n");
	   printf("+---------------+-------+-------+\n");
	   for(int i=0; i<547;i++){
		   if(syscalls[i]>0)
		   {
			   get_syscall(i, syscall_name);
			   if(strlen(syscall_name)<7)
				   printf("|%s\t\t|%d\t|%d\t|\n", syscall_name, i, syscalls[i]);
			   else
				   printf("|%s\t|%d\t|%d\t|\n", syscall_name, i, syscalls[i]);
		   }
	   }
	   printf("+---------------+-------+-------+\n");
	   printf("Total Number of System Calls=%d\n", counter);
}

int main(int argc, char *argv[])
{
    char *mode = get_from_argv("--mode", argc, argv);
    char *filter = get_from_argv("--filter", argc, argv);
    char *program_name;
    char **other_argv;
    program_name = malloc(64 * sizeof(char));
    other_argv = malloc(512 * sizeof(char));
    get_program_and_args(program_name, other_argv, argc, argv);

    exec_fork(program_name, other_argv, mode, filter);

    printf("Set filter is %s\n", filter);

    return 0;
}
