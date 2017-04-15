CC = g++
CXXFLAGS = -g -Wall -std=c++0x
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

Main: $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o build/Main

*.o: src/*.cpp src/*.h
	$(CC) $(CXXFLAGS) -c src/*.cpp

clean:
	rm -f $(OBJECTS) build/Main
