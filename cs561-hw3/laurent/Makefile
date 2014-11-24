CC			=	g++
INCLUDE		=	include
SOURCE		=	src
OBJECTIVE	=	obj
TARGET		=	bin
CFLAGS		=	-I./$(INCLUDE)

agent: dir base
	$(CC) $(CFLAGS) $(OBJECTIVE)/agent.o $(OBJECTIVE)/utilities.o \
		$(OBJECTIVE)/expr.o $(OBJECTIVE)/chaining.o -o agent

base: dir
	$(CC) $(CFLAGS) -c $(SOURCE)/utilities.cpp -o $(OBJECTIVE)/utilities.o
	$(CC) $(CFLAGS) -c $(SOURCE)/expr.cpp -o $(OBJECTIVE)/expr.o
	$(CC) $(CFLAGS) -c $(SOURCE)/chaining.cpp -o $(OBJECTIVE)/chaining.o
	$(CC) $(CFLAGS) -c $(SOURCE)/agent.cpp -o $(OBJECTIVE)/agent.o

run:
	./agent

dir:
	mkdir -p $(OBJECTIVE)

clean:
	rm -rf $(OBJECTIVE)
	rm -f agent
	rm -f *.txt
