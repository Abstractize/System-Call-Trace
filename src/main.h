#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>

/***
 *  Function that produces the value for the given argument key
 *  in argv
 *
 *  @param compare: string that represents the argument key
 *  @param argc: number of arguments in argv
 *  @param argv: arguments array to be queried
 *
 *  @return the value for the given argument key, empty if nothing
 *  is found
 */
char *get_from_argv(const char *compare, int argc, char *argv[]);

/**
 * Function that adds all arguments that are not tied to the mode
 * and filter argument keys to the dest array
 *
 * @params dest: destination array to add the arguments
 * @param argc: number of arguments in argv
 * @param argv: arguments array to be queried
 *
 * @return the size of the destination array
 */
int get_program_and_args(char *program_dest, char* dest[], int argc, char *argv[]);

/***
 * Program that lists all the syscalls made to the system by a program passed
 * on the parameters
 */
int main(int argc, char *argv[]);

