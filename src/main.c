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

int get_program_and_args(char *program_dest, char* dest[], int argc, char *argv[])
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
    return args_count;
}

void exec_fork(char *program, char* argv[])
{
	int status;
	 pid_t pid;
	 struct user_regs_struct regs;
	 int counter = 0;
	 int in_call =0;

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
	         printf("SystemCall %ld called with %ld, %ld, %ld\n",regs.orig_rax, regs.rbx, regs.rcx, regs.rdx);
	         in_call=1;
	         counter ++;
	       }
	       else
	         in_call = 0;
	     ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
	     wait(&status);
	     }
	   }
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
    int other_argc = get_program_and_args(program_name, other_argv, argc, argv);

    exec_fork(program_name, other_argv);

    printf("Set mode is %s\n", mode);
    printf("Set filter is %s\n", filter);

    return 0;
}

