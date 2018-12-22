CC = g++
CFLAGS = -Wall -std=c++14 -g
DEPS = header.h global.h
LIBS= -pthread
OBJ = global.o share.o seederlist.o tracker.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tracker: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	
.PHONY: clean

clean:
	rm -rf *.o tracker