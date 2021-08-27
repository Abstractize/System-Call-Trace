#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *get_from_argv(const char *compare, int argc, char *argv[])
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
    int counter = 1;
    while (counter < argc)
    {
        if (strcmp("--mode", argv[counter]) && strcmp("--filter", argv[counter]))
        {
        	dest[args_count] = malloc(strlen(argv[counter]) * sizeof(char));
            strcpy(dest[args_count], argv[counter]);
            args_count++;
        }
        else
            counter++;
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
    int other_argc = strlen(*other_args);
    printf("Set mode is %s\n", mode);
    printf("Set filter is %s\n", filter);
    printf("Other args len: %ld\n", other_argc);
    printf("Other arguments are\n");
    for (int counter = 0; counter < other_argc; counter++)
    {
    	printf("%s\n",other_args[counter]);
    }
}

