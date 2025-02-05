# Simple Shell

## Author
Brian Pacouloute

## Term
Winter 2025

## Overview
This is a simple command-line shell program implemented in C. It allows users to enter commands, which are then executed by creating a child process using `fork()` and `execvp()`. The shell continuously prompts the user for input and executes commands until the user enters `q` to quit.

## Features
- Reads user input and processes commands.
- Uses `fork()` to create child processes for command execution.
- Uses `execvp()` to execute commands.
- Supports multiple arguments.
- Implements memory allocation and proper deallocation for argument parsing.

## Prerequisites
- GCC compiler (or any C compiler)
- Linux or macOS (may work on Windows with WSL)

## Compilation
To compile the program, use the following command:

```sh
gcc -o myshell myshell.c
```

## Usage
Run the compiled executable:

```sh
./myshell
```

You will see the shell prompt:

```
myshell>
```

Enter a command like:

```
myshell> ls -l
```

To exit the shell, type:

```
myshell> q
```

## Implementation Details
- Uses `fgets()` to read user input safely.
- `strtok()` is used to split the input into command arguments.
- `malloc()` and `realloc()` are used for dynamic memory allocation.
- The child process executes the command, while the parent waits for it to complete.
- Proper memory deallocation is handled to prevent leaks.

