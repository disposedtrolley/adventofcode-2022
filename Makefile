day:=day_$(DAY)
input:=$(INPUT)

build:
	gcc $(day).c -g -O0 -Wall -Wextra -o $(day).out

run: build
	./$(day).out $(input)

clean:
	rm -f *.out
