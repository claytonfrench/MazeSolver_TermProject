CC = g++
CFLAGS = -g -Wall
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

Main: $(OBJECTS)
	$(CC) $(CFLAGS) Main.o -o ../build/Main

Main.o: Main.cpp
	$(CC) $(CFLAGS) -c Main.cpp

*.o: *.cpp *.h
	$(CC) $(CFLAGS) -c *.cpp

clean:
	rm -f $(OBJECTS) Main
