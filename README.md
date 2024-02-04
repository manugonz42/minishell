# Minishell Project - 42

## Overview

This is my implementation of the Minishell project as part of the curriculum at 42. Minishell is a simple shell that provides a basic command-line interface for users to interact with the operating system. It supports various built-in shell commands as well as the execution of external commands.

## Features

- **Built-in Commands:** Implements common shell built-in commands such as `echo`, `cd`, `pwd`, `export`,  `exit` and `unset`.
- **Command Execution:** Handles the execution of external commands using the `execve` system call.
- **Redirections:** Supports input and output redirections (`<`, `>`, `>>`) for command input and output.
- **Pipes:** Implements command piping (`|`) to connect the output of one command to the input of another.
- **Environment Variables:** Manages environment variables and supports variable expansion.
- **Signals:** Handles signals like `Ctrl + C` and `Ctrl + \`.

## Getting Started

### Prerequisites

- Make sure you have a C compiler installed (e.g., GCC).
- This project is designed to run on a Unix-like system.

### Building and Running

1. Clone the repository:

    ```bash
    git clone https://github.com/manugonz42/minishell.git
    cd minishell
    ```

2. Build the project:

    ```bash
    make
    ```

3. Run the Minishell:

    ```bash
    ./minishell
    ```

## Usage

- Use the shell as you would with any other command-line interface.
- Explore built-in commands and experiment with external command execution.
- Try out features like input/output redirections and piping.
