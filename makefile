check: main.c src/dict.c src/check.c src/print.c src/hash.c src/list.c src/word.c src/corr.c
	- gcc -g -std=c99 -Wall -Werror main.c src/dict.c src/check.c src/print.c src/hash.c src/corr.c src/list.c src/word.c -o check
	- ./check files/dictionary.txt files/text.txt
	- rm check

time: main.c src/dict.c src/check.c src/print.c src/hash.c src/list.c src/word.c src/corr.c
	- gcc -g -std=c99 -Wall -Werror main.c src/dict.c src/check.c src/print.c src/hash.c src/list.c src/word.c src/corr.c -o time
	- time ./time files/dictionary.txt files/text.txt
	- rm time

valgrind: main.c src/dict.c src/check.c src/print.c src/hash.c src/list.c src/word.c src/corr.c
	- gcc -g -std=c99 -Wall -Werror main.c src/dict.c src/check.c src/print.c src/hash.c src/list.c src/word.c src/corr.c -o valgrind
	- valgrind ./valgrind files/dictionary.txt files/text.txt
	- rm valgrind