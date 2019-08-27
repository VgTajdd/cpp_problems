# Specify compiler
CC=cl.exe /EHsc

# Specify linker
LINK=link.exe

.PHONY: clean all run

all : app

# Link the object files into a binary
app : main.o
	$(LINK) /OUT:app.exe main.o

# Compile the source files into object files
main.o : main.cpp
	$(CC) /c main.cpp /Fomain.o

# Clean target
clean :
	del main.o app.exe

run:
	app.exe