# Minishell - As beautiful as a shell

## Requirements
Install readline:  
* Mac:  
&emsp; Install brew:  
&emsp; `rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update`  
&emsp; Install Readline Library:  
&emsp; `brew install readline`  
* Fedora:  
&emsp; Install Readline Library:  
&emsp; `sudo dnf install readline-devel`  
* Ubuntu/Debian:  
&emsp; List every library name \*readline\*:  
&emsp; `apt-cache search readline`  
&emsp; Choose latest libreadline<$VERSION_NUMBER> and install Readline Library:  
&emsp; `sudo apt-get install libreadline-dev libreadline<$VERSION_NUMBER>`  

## Versions  
* v1: f/expand  
* v2: f/lexer  

## Allowed functions
- **char \*readline (const char \*prompt);**  
&emsp;    
- rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
