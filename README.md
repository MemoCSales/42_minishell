<div align="center">
    <h1>Let's create our own MINISHELL</h1>
</div>

### Table of contents

* [Overview](#Overview)
* [The Challenge](#The-Challenge)
* [Key Concepts](#Key-Concepts)
* [Building and Running](#Building-and-Running)
* [Example tests](#Example-tests)
* [Conclusion](#Conclusion)
* [Contributors](#Contributors)
## Overview

We call this project minihell and is a Unix shell replica created as part of the 42 school [curriculum](https://42wolfsburg.de/de/42-programming-curriculum/).

> This project aims to mimic the basic functionality of a traditional Unix shell, including command execution, built-ins handling, en environment management.

## The Challenge

The challenge lies in accurately replicating the behavior of  a Unix shell within the constraings of the C programming language, and the 42 guidelines.

This includes parsing user input, executing  commands, managing environment variables, and handling signals.

## Key Concepts
- **Command Parsing and Execution**: Analyzing user input and executing commands accordingly.
- **Built-ins Implementation**: Internal shell commands like `cd`, `echo`, `env`, `exit`, `export`, `pwd`, and `unset`.
- **Environment Management**: Handling environment variables for command execution.
- **Signal Handling**: Managing signals like `SIGINT` and `SIGQUIT` to mimic the behavior of a traditional shell.
- **Redirection and Piping**: Redirecting command output and input, as well as piping the output of one command to another.

## Building and Running

To build the project, navigate to the project directory and use the `Makefile` provided:

```sh
cd 42_minishell
make
```

This will compile the project and create an executable named minishell. To run it, simply execute:
```sh
./minishell
```

## Example tests

After building the project, you can test its functionality with some basic commands:

1. Display the current directory:
    ```sh
    ψΨ$ pwd
    ```

2. List files in the current directory:
    ```sh
    ψΨ$ ls
    ```

3. Change directory:
    ```sh
    ψΨ$ cd <directory>
    OR
    ψΨ$ cd ..
    OR
    ψΨ$ cd
    ```

4. Set an environment variable:
    ```sh
    ψΨ$ export NAME=value
    ```

5. Print an environment variable:
    ```sh
    ψΨ$ echo $NAME
    ```

6. And so much more...


## Conclusion
42_minishell is a comprehensive project that covers many aspects of shell functionality, providing a solid foundation in systems programming, process management, and Unix system calls.

## Contributors
- [Memo Sales](https://github.com/MemoCSales)
- [Demetrio Rodrigues](https://github.com/demacinema)

Feel free to contribute to this project by submitting pull requests or opening issues.