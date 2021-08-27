#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *get_from_argv(char *compare, int argc, char *argv[])
{
    for (int counter = 0; counter < argc; counter++)
    {
        if (!strcmp(compare, argv[counter]))
            return argv[counter + 1];
    }
    return "";
}

void get_program_and_args(char* dest[], int argc, char *argv[])
{
    int args_count = 0;
    for (int counter = 1; counter < argc; counter++)
    {
        if (strcmp("--mode", argv[counter]) && strcmp("--filter", argv[counter]))
        {
        	dest[args_count] = malloc(strlen(argv[counter]) * sizeof(char));
            strcpy(dest[args_count], argv[counter]);
            //strcat(dest[args_count], "\0");
            args_count++;
        }
        else
            counter++;
    }
}

int main(int argc, char *argv[])
{
    char *mode = get_from_argv("--mode", argc, argv);
    char *filter = get_from_argv("--filter", argc, argv);
    char **other_args;
    other_args = malloc(1024 * sizeof(char));
    get_program_and_args(other_args, argc, argv);
    printf("Number of args: %d\n", argc);
    printf("Set mode is %s\n", mode);
    printf("Set filter is %s\n", filter);
    printf("Other args len: %ld\n", strlen(*other_args));
    printf("Other arguments are\n");
    for (int counter = 0; counter < strlen(*other_args); counter++)
    {
    	printf("%s\n",other_args[counter]);
        //free(other_args[counter]);
    }
    //free(other_args);
    //return 0;
}
