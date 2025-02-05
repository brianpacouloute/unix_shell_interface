/*
Author Brian Pacouloute
Term Winter 2025
*/

/* Defining Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Defining Constants */
#define INPUT_SIZE 50
#define ARGUMENT_SIZE 50

void user_input(char* prompt, char* input, int INPUT_SIZE_CONSTANT) {
    printf("%s", prompt);
    fgets(input, sizeof(char) * INPUT_SIZE_CONSTANT, stdin); /* Printing the prompt */

    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    } else {
        while (getchar() != '\n'); /* Flushing the stdin */
    }
}

int main() {
    char *user_in_cmd = (char*)malloc(sizeof(char) * INPUT_SIZE);
    if (user_in_cmd == NULL) {
        perror("Memory Allocation Failed");
        return 1;
    }

    while (1) { 
        user_input("myshell> ", user_in_cmd, INPUT_SIZE);

        /* Exit condition */
        if (strcmp(user_in_cmd, "q") == 0) {
            break;
        }

        int sub_process = fork();
        if (sub_process == 0) {
            /* This is the child process */

            /* Split the input into command and arguments */
            int count = 0;
            char* token = strtok(user_in_cmd, " ");
            char** argument_values = (char**)malloc(sizeof(char*));

            if (argument_values == NULL) {
                perror("Memory Allocation Failed: unable to allocate memory for argument values");
                exit(1);
            }

            /* Tokenize and allocate memory for each argument */
            while (token != NULL) {
                char** new_arg_vals = (char**)realloc(argument_values, sizeof(char*) * (count + 1));
                if (new_arg_vals == NULL) {
                    perror("Memory Allocation Failed: unable to expand argument array");
                    /* Free previously allocated memory */
                    for (int i = 0; i < count; i++) {
                        free(argument_values[i]);
                    }
                    free(argument_values);
                    exit(1);
                }

                argument_values = new_arg_vals;

                /* Allocate memory for each argument string */
                argument_values[count] = (char*)malloc(sizeof(char) * (strlen(token) + 1));
                if (argument_values[count] == NULL) {
                    perror("Memory Allocation Failed: unable to allocate memory for token");
                    /* Free previously allocated memory */
                    for (int i = 0; i < count; i++) {
                        free(argument_values[i]);
                    }
                    free(argument_values);
                    exit(1);
                }

                strcpy(argument_values[count], token);
                token = strtok(NULL, " ");
                count++;
            }

            /* Execute the command */
            if (execvp(argument_values[0], argument_values) == -1) {
                perror("Execution Failed");

                /* Free allocated memory before exiting */
                for (int i = 0; i < count; i++) {
                    free(argument_values[i]);
                }
                free(argument_values);
                exit(1);
            }

            /* This line will never be reached if execvp succeeds */
            for (int i = 0; i < count; i++) {
                free(argument_values[i]);
            }
            free(argument_values);

            exit(0); /* Exit when child process is done with its task */

        } else if (sub_process > 0) {
            /* This is the parent process */
            int status;
            wait(&status); /* Wait for child to finish */
            continue;
        } else {
            perror("Failed to create process");
        }
    }

    /* Free user command input memory before exiting the program */
    free(user_in_cmd);
    return 0;
}
