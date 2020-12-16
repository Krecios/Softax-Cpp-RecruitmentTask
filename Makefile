CC = g++

softax.o: server.cpp
	$(CC) -pthread server.cpp -o softax.o