objects=program.o

fileOpen: $(objects)
	gcc -o printDir $(objects)
program.o: program.c program.h
	gcc -c program.c

.PHONY:clean
clean:
	rm printDir $(objects)

run:
	./printDir .
