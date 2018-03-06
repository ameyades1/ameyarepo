#!/bin/bash

# 0 => stdin, 1 => stdout, 2 => stderr
# cmd > stdout
# cmd 2>stderr
# cmd <stdin
# cmd &> file stdout + stderr
# cmd 2>&1 | cmd2 stdout and stderr from cmd
# cmd &>> file stderr and stdout concat to file
# cmd << file heredoc
# cmd1 |& cmd2 cmd1 stderr and stdout both piped to cmd2's stdin

# Heredoc
sort <<END
cherry
banana
apple
END


echo Just '>' ----------------------
find /etc -name grub > grub.out

echo Doing '2>' ---------------------
find /etc -name grub 2>err.out

echo Doing '&>' ---------------------
find /etc -name grub &>both.out

