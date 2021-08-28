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

int get_program_and_args(char* dest[], int argc, char *argv[])
{
    int args_count = 0;
    int counter = 1;
    while (counter < argc)
    {
        if (strcmp("--mode", argv[counter]) && strcmp("--filter", argv[counter]))
        {
        	dest[args_count] = malloc((strlen(argv[counter]) + 1) * sizeof(char));
            strcpy(dest[args_count], argv[counter]);
            args_count++;
        }
        else
            counter++;
        counter++;
    }
    return args_count;
}

int main(int argc, char *argv[])
{
    char *mode = get_from_argv("--mode", argc, argv);
    char *filter = get_from_argv("--filter", argc, argv);
    char **other_args;
    other_args = malloc(512 * sizeof(char));
    int other_argc = get_program_and_args(other_args, argc, argv);

    printf("Set mode is %s\n", mode);
    printf("Set filter is %s\n", filter);
    printf("Total args: %d\n", argc);
    printf("Other args len: %d\n", other_argc);
    printf("Other arguments are\n");
    for (int counter = 0; counter < other_argc; counter++)
    {
    	printf("%s\n",other_args[counter]);
    }
}

