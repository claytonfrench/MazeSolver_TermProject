CC = g++
CFLAGS = -g -Wall -std=c++11
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

Main: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o build/Main

*.o: src/*.cpp src/*.h
	$(CC) $(CFLAGS) -c src/*.cpp

clean:
	rm -f $(OBJECTS) build/Main
