Plsh
====
    Toggle debugging with 'sed -i 's/DEBUG 1/DEBUG 0/' libplsh.c ' because why not.

Features
--------

        x   Prompt for input - <username>@<hostname>:<working_directory>--)
        x   The working directory should be absolute
        o   Implement the following built-in commands
            x   exit - quits the shell and prints an exit message
            x   cd 
            o   time 
            x   viewproc <file> 
        x   Runs any simple program found on the path, such as “ls” or “grep”
        x   input redirection - cat < a.txt
        x   output redirection - ls > ls.txt
        o   background execution - sleep 10 &
        o   piping - ls | grep „a‟ | grep „b‟
        o   Guarantees no zombies 
        ~   environment variable expansiono - Non-existent variables expand to the empty string 
        
        report these errors
            !   Malformed I/O redirections
            !   Missing file name or command
            o   Malformed pipes
            ~   Missing a command
            o   Incorrect placement of ampersand
            x   Non-existent path/filename passed to cd or viewproc
        
