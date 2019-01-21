echo "Running pwd 5000 times..."
strace -c -o out1.o ./loop1.sh 
head -6 out1.o

echo "Running /bin/pwd 5000 times..."
strace -c -o out2.o ./loop2.sh
head -6 out2.o
