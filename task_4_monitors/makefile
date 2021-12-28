main: main.o smartbuffer.o
	g++  main.o smartbuffer.o -Wall -fsanitize=thread,undefined -lpthread -lm

main.o: main.cpp smartbuffer.h
	g++ -o main.o -c main.cpp -Wall -fsanitize=thread,undefined -lpthread -lm

smartbuffer.o: smartbuffer.cpp smartbuffer.h monitor.h
	g++ -o smartbuffer.o -c smartbuffer.cpp -Wall -fsanitize=thread,undefined -lpthread -lm

clean:
	rm *.o *.out