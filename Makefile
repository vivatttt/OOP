SOURCES = main.cpp CarManager.cpp Coordinates.cpp
CC = g++
CFLAGS = -Wall
EXECUTABLE = program

OBJECTS = $(SOURCES:.cpp=.o)

all: target

target: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: target
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)