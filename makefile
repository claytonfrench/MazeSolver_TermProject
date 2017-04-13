CC = g++
CFLAGS = -g -Wall
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

Main: $(OBJECTS)
	$(CC) $(CFLAGS) src/Main.o -o build/Main

Main.o: /src/Main.cpp
	$(CC) $(CFLAGS) -c src/Main.cpp

*.o: src/*.cpp src/*.h
	$(CC) $(CFLAGS) -c src/*.cpp

clean:
	rm -f $(OBJECTS) build/Main
