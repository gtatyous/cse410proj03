Student NetID: gtatyous (Yousef Gtat), I am working alone.

Compilation tested on: ned, carl, marge and skinner

main.cpp has all the source code used for this project. 

Command for compile: make

Command to run: ./proj3 fileName/DirectoryName

comments: if no files or directories were provided, the code will notify the user and terminate. If a file name is provided, the code will check if there is already a Bizzaro version and if this is the case, the program will notify the user and terminate. If it is not, a Bizzaro version of the file will be created in the same directory. If the provided is a directory name, then the code will recursively apply Bizzaro on all files and sub-directories inside of it with no exceptions.

*****************Sample output*************************

Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls
Makefile	README.txt	main.cpp	test		zzz.txt


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ make
clang++ -Wall -std=c++11   -c -o main.o main.cpp
clang++ main.o -o proj3


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ cat zzz.txt
File in the current directory that will get reversed!


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ./proj3 zzz.txt
The argument provided is a file
Operation finished succesfully!


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls
Makefile	main.cpp	proj3		txt.zzz
README.txt	main.o		test		zzz.txt


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ cat txt.zzz

!desrever teg lliw taht yrotcerid tnerruc eht ni eliFYousefs-MacBook-Pro:CSE410proj03 Gtat$./proj3 zzz.txt
Error: can't create Bizarro file/directory; txt.zzz already exists!!

————————————————————————————————————————————————————————————

Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls
Makefile	main.cpp	proj3		txt.zzz
README.txt	main.o		test		zzz.txt
Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ./proj3 test
The argument provided is a directory
Operation finished succesfully!
Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls -R test
2erazzib	bizzare1	bizzare2	jjj.txt		txt.jjj.txt

test/2erazzib:
qqq.txt

test/bizzare1:
ddww.txt	txt.by.txt	zzaa.txt

test/bizzare2:
fff.txt
Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls -R tset/
1erazzib	2erazzib	bizzare2	txt.jjj		txt.jjj

tset//1erazzib:
txt.aazz	txt.wwdd	txt.yb.txt

tset//2erazzib:
txt.fff

tset//bizzare2:
txt.qqq
Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ./proj3 test
Error: can't create Bizarro file/directory; tset already exists!!
Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ./proj3 tset
Error: can't create Bizarro file/directory; test already exists!!


————————————————————————————————————————————————————————————






