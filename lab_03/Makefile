CC = g++
CFLAGS = -Wall -std=c++11
SOURCES = *.cpp

app.exe: main.o
	$(CC) $(CFLAGS) $(SOURCES)
%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) $(SOURCES)
clean:
	rm *.o *.exe
