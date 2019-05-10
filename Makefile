CC = g++
FLAGS = -Wall
TARGETS = main.o Ecosystem.o MapGenerator.o Entity.o Plants.o Animals.o

ecosystemSimulator:$(TARGETS)
	$(CC) $(FLAGS) -o ecosystemSimulator $(TARGETS)

main.o: main.cpp
	$(CC) $(FLAGS) -o main.o -c main.cpp

Ecosystem.o: Ecosystem.cpp
	$(CC) $(FLAGS) -o Ecosystem.o -c Ecosystem.cpp

MapGenerator.o: MapGenerator.cpp
	$(CC) $(FLAGS) -o MapGenerator.o -c MapGenerator.cpp

Entity.o: Entity.cpp
	$(CC) $(FLAGS) -o Entity.o -c Entity.cpp

Plants.o: Plants.cpp
	$(CC) $(FLAGS) -o Plants.o -c Plants.cpp

Animals.o: Animals.cpp
	$(CC) $(FLAGS) -o Animals.o -c Animals.cpp

.PHONY: clean

clean:
	rm -f ecosystemSimulator $(TARGETS)