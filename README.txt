Student NetID: gtatyous (Yousef Gtat), I am working alone.

Compilation tested on: ned, carl, marge and skinner

main.cpp has all the source code used for this project. 

Command for compile: make

Command to run: ./proj3 fileName/DirectoryName

comments: if no files or directories were provided, the code will notify the user and terminate. If a file name is provided, the code will check if it is already a Bizzaro version and if this is the case, the program will notify the user and terminate. If it is not, a Bizzaro version of the file will be created in the same directory. If the directory name is provided, the code will recursively apply Bizzaro on the files and sub-directories inside if needed. 

*****************Sample output*************************

Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls
Makefile	README.txt	main.cpp	test		txt.zzz


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls -R test
2erazzib	bizzare1	bizzare2	jjj.txt		txt.xyz.txt

test/2erazzib:
txt.wasBizzare2.txt

test/bizzare1:
ddww.txt	zzaa.txt

test/bizzare2:
wasNotBizzare.txt


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ cat test/2erazzib/txt.wasBizzare2.txt
This is already bizarre


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ cat test/bizzare1/ddww.txt
Finals are my nightmare!


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ cat test/bizzare1/zzaa.txt
The horse to get some hay over the fence jumped.


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ cat test/bizzare2/wasNotBizzare.txt
This is not bizarre version


ousefs-MacBook-Pro:CSE410proj03 Gtat$ make
clang++ -Wall -std=c++11   -c -o main.o main.cpp
clang++ main.o -o proj3


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ./proj3 txt.zzz
Error: can't create Bizarro file txt.zzz; it's already a Bizarro file!!


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ./proj3 README.txt
Operation finished succesfully!


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls
Makefile	main.cpp	proj3		txt.EMDAER
README.txt	main.o		test		txt.zzz


ousefs-MacBook-Pro:CSE410proj03 Gtat$ ./proj3 README.txt
Error: can't create Bizarro file/directory; txt.EMDAER already exists!!


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ./proj3 test
Operation finished succesfully!


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls
Makefile	main.cpp	proj3		tset		txt.zzz
README.txt	main.o		test		txt.EMDAER


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ ls -R tset
1erazzib	2erazzib	bizzare2	txt.jjj		txt.xyz

tset/1erazzib:
txt.aazz	txt.wwdd

tset/2erazzib:
txt.erazziBtoNsaw

tset/bizzare2:
txt.wasBizzare2.txt


Yousefs-MacBook-Pro:CSE410proj03 Gtat$ cat tset/txt.jjj

Yousefs-MacBook-Pro:CSE410proj03 Gtat$ cat tset/1erazzib/txt.aazz

.depmuj ecnef eht revo yah emos teg ot esroh ehTYousefs-MacBook-Pro:CSE410proj03 Gtat$ cat tset/1erazzib/txt.wwdd

!eramthgin ym era slaniFYousefs-MacBook-Pro:CSE410proj03 Gtat$ cat tset/2erazzib/txt.erazziBtoNsaw

noisrev errazib ton si sihTYousefs-MacBook-Pro:CSE410proj03 Gtat$ cat tset/bizzare2/txt.wasBizzare2.txt
This is already bizarre









