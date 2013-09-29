
Plsh
x   Prompt for input - <username>@<hostname>:<working_directory>--)
x   The working directory should be absolute
o   Implement the following built-in commands
    x   exit - quits the shell and prints an exit message
    x   cd 
    o   time 
    x   viewproc <file> 
o   Runs any simple program found on the path, such as “ls” or “grep”
o   input redirection - cat < a.txt
o   output redirection - ls > ls.txt
o   background execution - sleep 10 & iping - ls | grep „a‟ | grep „b‟
o   Guarantees no zombies 
~   environment variable expansiono - Non-existent variables expand to the empty string 

report these errors
    0   Malformed I/O redirections
    o   Missing file name or command
    o   Malformed pipes
    ~   Missing a command
    o   Incorrect placement of ampersand
    ~   Non-existent path/filename passed to cd or viewproc

