day:=day_$(DAY)
input:=$(INPUT)

build: ht.o
	gcc $(day).c -g -O0 -Wall -Wextra -o $(day).out ht.o

run: build
	./$(day).out $(input)

clean:
	rm -f *.out

ht.o: vendor/ht/ht.c vendor/ht/ht.h
	gcc -Wall -c vendor/ht/ht.c -lvendor/ht