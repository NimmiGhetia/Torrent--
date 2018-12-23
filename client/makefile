CC = g++
CFLAGS = -Wall -std=c++14 -g 
DEPS = header.h global.h
LIBS= -lssl -lcrypto
OBJ = global.o hash.o mtorrent.o share.o remove.o commands.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

client: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	
.PHONY: clean

clean:
	rm -rf *.o clt 