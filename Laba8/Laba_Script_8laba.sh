echo "4 6" > input.txt
echo "3 8" > test.txt
gcc -std=c99 -pedantic Laba8.c
./a.out < input.txt | diff -b test.txt - && echo "OK"
