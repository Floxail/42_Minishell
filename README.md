*This project has been created as part
of the 42 curriculum by damarcin, flvejux.*


# Minishell

A Unix shell implementation written in C that recreates core functionality of bash, focusing on process management, command parsing, and inter-process communication.

---

## Description

Minishell is a systems programming project that challenges students to build a functional command-line interpreter from scratch. The goal is to understand how shells work by implementing core features including command parsing, process creation, I/O redirection, pipes, and signal handling.

The project emphasizes learning fundamental Unix concepts through practical implementation:

- Process creation and management using fork, execve, and waitpid
- File descriptor manipulation for I/O redirection and pipes
- Command-line parsing with lexing and parsing stages
- Signal handling for terminal control
- Environment variable expansion and management

The implementation supports executing external commands, chaining commands with pipes, redirecting input and output to files, handling environment variables, and providing built-in shell commands that cannot be delegated to child processes.

---

## Instructions

### Compilation

The project is compiled using GNU Make and must be compiled with the following command:

```
make
```

This produces the executable `minishell`.

To remove object files:

```
make clean
```

To remove all build artifacts including the executable:

```
make fclean
```

To recompile from scratch:

```
make re
```

### Execution

Run the compiled shell:

```
./minishell
```

The shell presents an interactive prompt where commands can be entered and executed. The shell supports both built-in commands and external executables available in the system PATH.

Exit the shell by typing:

```
exit
```

### Supported Features

The shell implements the following core features:

- Command execution from absolute paths, relative paths, or via PATH environment variable
- Pipes (|) for command chaining with inter-process communication
- Input/output redirections: < (read from file), > (write to file), >> (append to file)
- Heredoc (<<) for multi-line input until a specified delimiter
- Environment variable expansion ($HOME, $USER, $?, etc.)
- Exit status tracking and expansion via $?
- Quote handling (single quotes preserve literals, double quotes allow variable expansion)
- Escape sequences with backslash
- Multiple command execution separated by semicolons (;)
- Signal handling for Ctrl+C (SIGINT), Ctrl+D (EOF), Ctrl+\ (SIGQUIT)

Built-in commands:

- echo: print text to output (supports -n flag)
- cd: change current working directory
- pwd: print working directory
- export: set or update environment variables
- unset: remove environment variables
- env: display all environment variables
- exit: terminate the shell with optional exit code

### Example Usage

```
$ ./minishell
minishell> ls -la
minishell> cat file.txt | grep pattern | wc -l
minishell> echo "output" > file.txt
minishell> cd /tmp
minishell> export MY_VAR=value
minishell> echo $MY_VAR
minishell> exit
```

---

## Technical Overview

The shell is built around four main processing stages:

Lexer: The input line is tokenized into words, operators, and special characters. This stage handles quote processing and escape sequences.

Parser: Tokens are organized into a tree structure that represents the command structure, respecting operator precedence (pipes, semicolons, redirections).

Expander: Environment variables are substituted with their values. The special variable $? expands to the exit status of the previous command.

Executor: The parse tree is executed recursively. For external commands, a child process is created via fork, redirected appropriately via dup2, and executed via execve. Built-in commands are executed directly in the shell process without forking.

Key implementation details:

File descriptors are managed explicitly. The standard descriptors (0=stdin, 1=stdout, 2=stderr) are redirected using dup2 before executing external commands. Pipes create pairs of descriptors that are connected between adjacent commands.

Process management relies on fork to create child processes and waitpid to collect exit statuses. For pipes, multiple children are created and synchronized through the parent process.

Signal handling is configured at startup to handle terminal control signals appropriately. The handlers maintain the shell's ability to display prompts and manage state.

Environment variables are maintained in a linked list structure for efficient access and modification.

---

## Resources

The following references are recommended for understanding the concepts and implementation details:

The Linux Programming Interface by Michael Kerrisk - Comprehensive coverage of system calls including fork, execve, pipes, and file descriptors.

Advanced Programming in the UNIX Environment by Stevens and Rago - Classic reference for Unix system programming concepts.

Linux man pages - man 2 fork, man 2 execve, man 2 pipe, man 2 dup2, man 7 signal

GNU Readline Library Documentation - For understanding line editing and history features.

42 Curriculum Materials - Project specifications and related documentation available through the school.

POSIX Standards - Official specifications for system calls and standard library functions.

### Use of AI

AI assistance was used for the following aspects of this project:

Documentation and README writing: Structure, formatting, and comprehensive explanation of features and usage.

Code review and optimization suggestions: General guidance on code organization and function decomposition.

Concept explanation: Clarification of Unix system programming concepts including signal handling.

Debugging guidance: General troubleshooting approaches and common pitfalls to avoid in shell implementation.