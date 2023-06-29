OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))
Project.exe: $(OBJ)
	gcc -o $@ $^  
clean:
	rm *.o *.exe
