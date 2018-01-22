#!/bin/bash

# 0 => stdin, 1 => stdout, 2 => stderr
# cmd > stdout
# cmd 2>stderr
# cmd <stdin
# cmd &> file stdout + stderr
# cmd 2>&1 | cmd2 stdout and stderr from cmd
# cmd &>> file stderr and stdout concat to file
# cmd << file heredoc


sort <<END
cherry
banana
apple
END

