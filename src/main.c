#include <stdio.h>
#include <string.h>

char *get_from_argv(char *compare, int argc, char *argv[])
{
    int counter;
    for (counter = 0; counter < argc; counter++)
    {
        if (!strcmp(compare, argv[counter]))
            return argv[counter + 1];
    }
    return "";
}

int main(int argc, char *argv[])
{
    char *mode = get_from_argv("--mode", argc, argv);
    char *filter = get_from_argv("--filter", argc, argv);
    printf("Set mode is %s\n", mode);
    printf("Set filter is %s\n", filter);
}
