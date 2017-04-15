CXX = g++
CXXFLAGS = -g -Wall -std=c++0x
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

Main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o build/Main

*.o: src/*.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c src/*.cpp

clean:
	rm -f $(OBJECTS) build/Main
