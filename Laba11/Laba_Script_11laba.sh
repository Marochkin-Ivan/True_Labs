gcc -std=c99 -pedantic Laba11.c
echo "Good_morning 12ff_pp Alex228 Fufel#_n ls_!s sd" > input1.txt
echo "Ansver: 3" > test1.txt
echo "F" > input2.txt
echo "Ansver: 1" > test2.txt
echo "1234" > input3.txt
echo "Ansver: 0" > test3.txt
echo "QwErT_y" > input4.txt
echo "Ansver: 1" > test4.txt
echo "jj#ew" > input5.txt
echo "Ansver: 0" > test5.txt
echo "hdsdfh sdfsdf lhl _kgkdf% 123e fjg656_2 ^%da" > input6.txt
echo "Ansver: 4" > test6.txt
./a.out < input1.txt | diff -b test1.txt - && echo "OK"
./a.out < input2.txt | diff -b test2.txt - && echo "OK"
./a.out < input3.txt | diff -b test3.txt - && echo "OK"
./a.out < input4.txt | diff -b test4.txt - && echo "OK"
./a.out < input5.txt | diff -b test5.txt - && echo "OK"
./a.out < input6.txt | diff -b test6.txt - && echo "OK"
