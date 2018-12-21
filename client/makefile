CC = g++
CFLAGS = -Wall -std=c++14 -g 
DEPS = header.h global.h
LIBS= -lssl -lcrypto
OBJ = hash.o mtorrent.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

client: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	
.PHONY: clean

clean:
	rm -rf *.o clt 