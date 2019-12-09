gcc -std=c99 -pedantic Laba11.c
./a.out < Laba11_input1.txt | diff -b Laba11_test1.txt - && echo "OK"
./a.out < Laba11_input2.txt | diff -b Laba11_test2.txt - && echo "OK"
./a.out < Laba11_input3.txt | diff -b Laba11_test3.txt - && echo "OK"
./a.out < Laba11_input4.txt | diff -b Laba11_test4.txt - && echo "OK"
