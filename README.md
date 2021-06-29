# Bash From Scratch

### Running the code
```
g++ -o shell shell.cpp -lreadline
./shell
```

### This code currently has the functions:
* run ls commands
* run cd commands
* run mkdir rmdir commands
* run cat command
* store history 
* cycle through history using up and down arrows
* cycle through characters using side arrow keys

### GNU Readline Library
The GNU Readline library provides a set of functions for use by applications that allow users to edit command lines as they are typed in. Both Emacs and vi editing modes are available. The Readline library includes additional functions to maintain a list of previously-entered command lines, to recall and perhaps reedit those lines, and perform csh-like history expansion on previous commands.  
see documentation [here](https://tiswww.case.edu/php/chet/readline/rltop.html)

