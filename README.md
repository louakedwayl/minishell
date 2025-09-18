# minishell

<p align="center">
  <img src="images/minishell.png" alt="Minishell">
</p>

## General usage

### Installation
Clone the repository
```bash
git clone git@github.com:louakedwayl/minishell.git 
```

Compile
```bash
cd minishell && make
```

### Start minishell
```bash
./minishell
```
A prompt will appear. You may enter your commands to be executed.

---

## Description

The **Minishell** project consists in recreating a simplified version of a UNIX shell.  
It is an introduction to **process management**, **signal handling**, **command parsing**, and **environment variable manipulation** in C.  

Our shell reproduces the behavior of `bash` for the most common features: executing commands, handling pipes and redirections, managing environment variables, and supporting built-in commands.

---

## Shell Requirements Summary

### Main Features
- **Prompt and History**  
  - Displays a prompt when waiting for a command.  
  - Keeps a working command history.

- **Command Execution**  
  - Executes programs based on the `PATH` variable or using relative/absolute paths.

- **Global Variable**  
  - Only **one global variable** allowed, used exclusively to store the number of a received signal.

- **Quote Handling**  
  - **Single quote `'`**: content is taken literally, no expansions.  
  - **Double quote `"`**: content is literal except for variable expansion with `$`.

- **Redirections**  
  - `<` : input redirection.  
  - `>` : output redirection (overwrite).  
  - `>>` : output redirection in append mode.  
  - `<<` : heredoc, reads input until a delimiter is reached.

- **Pipes**  
  - `|` : connects the output of one command to the input of the next.

- **Variable Expansion**  
  - `$VAR` : replaced by the value of the environment variable.  
  - `$?` : replaced by the exit status of the last executed command.

- **Signal and Control Handling**  
  - **Ctrl-C** : interrupts the current command and shows a new prompt.  
  - **Ctrl-D** : exits the shell.  
  - **Ctrl-\\** : does nothing.

- **Built-in Commands**  
  - `echo` with `-n` option.  
  - `cd` with relative or absolute path.  
  - `pwd` without options.  
  - `export` to set environment variables.  
  - `unset` to remove environment variables.  
  - `env` to display all environment variables.  
  - `exit` to quit the shell.

---

## 🔄 Complete Process

Here is an overview of the workflow in **Minishell**:

- **User input:** The user types a command.  
- **Lexical analysis:** The `tokenizer()` function (implemented in `tokenizer2.c`) processes the input and generates a **list of tokens**.  
- **Syntax analysis:** The create_cmd() function (implemented in parser.c) parses the list of tokens and constructs a command structure, including redirections and heredocs.
  - If a << heredoc is encountered, create_heredoc() reads the content from the user until the delimiter and stores it in the command structure.
- **Command execution:** The `ft_exec()` (implemented in `exec.c`) function executes the command structure, handling **redirections, pipes**, and other shell features.
  
---

## Memory Management: Custom Garbage Collector

Unlike the standard `malloc`/`free` workflow, **Minishell** uses a custom garbage collector to handle memory.  

- Every allocation goes through `ft_malloc`, a wrapper around `malloc`.  
- Each allocated pointer is automatically registered in a linked list of allocations.  
- At the end of execution (or when cleaning the shell), all allocations can be released in one single call.  

This system ensures:  
- No memory leaks.  
- Easier memory management.  
- A safer and cleaner execution flow, even when the shell exits unexpectedly.

Example of allocation workflow:
```c
void *ft_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
        return (NULL);
    if (create_node_garbage(ptr) == -1)
        return (NULL);
    return (ptr);
}
```
