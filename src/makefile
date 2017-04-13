CC = g++
CFLAGS = -g -Wall
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

Main: $(OBJECTS)
	$(CC) $(CFLAGS) Main.o -o ../build/Main

Main.o: Main.cpp
	$(CC) $(CFLAGS) -c Main.cpp

Bitmap.o: Bitmap.cpp Bitmap.h
	$(CC) $(CFLAGS) -c Bitmap.cpp

Color.o: Color.cpp Color.h
	$(CC) $(CFLAGS) -c Color.cpp

Maze.o: Maze.cpp Maze.h
	$(CC) $(CFLAGS) -c Maze.cpp

MazeSolver.o: MazeSolver.cpp MazeSolver.h
	$(CC) $(CFLAGS) -c MazeSolver.cpp

MazeTile.o: MazeTile.cpp MazeTile.h
	$(CC) $(CFLAGS) -c MazeTile.cpp

clean:
	rm -f $(OBJECTS) Main
