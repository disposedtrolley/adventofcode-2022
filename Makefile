day:=day_$(DAY)
input:=$(INPUT)

build:
	gcc $(day).c -o $(day).out

run: build
	./$(day).out $(input)

clean:
	rm -f *.out
