CC = g++
CFLAGS = -Wall -std=c++14 -g
DEPS = header.h global.h
OBJ = tracker.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

term: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	
.PHONY: clean

clean:
	rm -rf *.o term