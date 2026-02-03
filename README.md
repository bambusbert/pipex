*This project has been created as part of the 42 curriculum by slambert.*

**Description**

This is an implementation of the project "pipex" of 42 school. Its goal is to simulate the pipe operator that is a basic functionality on UNIX/POSIX systems and to learn the concepts that are needed in order to achieve that (eg. fork, dup2, pids).

**Bonus Implementation**
- It is possible to handle multiple pipes.

- It is not possible to handle "<<", ">>" and "here_doc".

**Instructions**

- Compilation (mandatory): run make to build the pipex executable.

- Compilation (bonus): run make bonus to build the executable with support for multiple pipes.

- Basic usage (mandatory):
./pipex file1 cmd1 cmd2 file2 behaves like < file1 cmd1 | cmd2 > file2. 
​
- Bonus usage (multiple pipes):
./pipex file1 cmd1 cmd2 ... cmdn file2 behaves like < file1 cmd1 | cmd2 | ... | cmdn > file2. 
​
- Limitations of this implementation:
here_doc, <<, and >> redirections are not supported and are intentionally left out of this version.
​

**Resources**

- Manual pages: man 2 fork, man 2 pipe, man 2 dup2, man 2 execve, man 2 open, man 2 access, man 2 waitpid.

- THE INTERNET

- GNU C Library / POSIX documentation for system calls and error handling.

- 42 documentation and intra subject PDF for the official pipex specification.

- AI was used for conceptual explanations and not for writing or generating any code.