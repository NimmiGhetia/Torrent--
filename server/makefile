CC = g++
CFLAGS = -Wall -std=c++14 -g
DEPS = header.h global.h
LIBS= -pthread
OBJ = log.o tracker.o global.o share.o seed.o tracker.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tracker: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	
.PHONY: clean

clean:
	rm -rf *.o tracker 