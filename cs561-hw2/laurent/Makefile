CC			=	g++
INCLUDE		=	include
SOURCE		=	src
OBJECTIVE	=	obj
TARGET		=	bin
CFLAGS		=	-I./$(INCLUDE)

agent: dir edgeStability base depthAdjustment
	$(CC) $(CFLAGS) -c $(SOURCE)/agent.cpp -o $(OBJECTIVE)/agent.o
	$(CC) $(CFLAGS) $(OBJECTIVE)/agent.o $(OBJECTIVE)/utilities.o $(OBJECTIVE)/greedy.o \
		$(OBJECTIVE)/minimax.o $(OBJECTIVE)/alphabeta.o $(OBJECTIVE)/edgeStability.o \
		$(OBJECTIVE)/depthAdjustment.o $(OBJECTIVE)/competition.o -o agent

base: dir
	$(CC) -c $(SOURCE)/utilities.cpp $(CFLAGS) -o $(OBJECTIVE)/utilities.o
	$(CC) $(CFLAGS) -c $(SOURCE)/greedy.cpp -o $(OBJECTIVE)/greedy.o
	$(CC) $(CFLAGS) -c $(SOURCE)/minimax.cpp -o $(OBJECTIVE)/minimax.o
	$(CC) $(CFLAGS) -c $(SOURCE)/alphabeta.cpp -o $(OBJECTIVE)/alphabeta.o
	$(CC) $(CFLAGS) -c $(SOURCE)/edgeStability.cpp -o $(OBJECTIVE)/edgeStability.o
	$(CC) $(CFLAGS) -c $(SOURCE)/competition.cpp -o $(OBJECTIVE)/competition.o

edgeStability: dir
	$(CC) $(SOURCE)/edgeStabilityGenerator.cpp -o $(TARGET)/edgeStability
	./$(TARGET)/edgeStability

depthAdjustment: dir base
	$(CC) $(CFLAGS) -c $(SOURCE)/depthAdjustmentGenerator.cpp -o $(OBJECTIVE)/depthAdjustment.o
	$(CC) $(CFLAGS) $(OBJECTIVE)/depthAdjustment.o $(OBJECTIVE)/utilities.o \
		$(OBJECTIVE)/edgeStability.o $(OBJECTIVE)/competition.o -o $(TARGET)/depthAdjustment
	./$(TARGET)/depthAdjustment
	$(CC) $(CFLAGS) -c $(SOURCE)/depthAdjustment.cpp -o $(OBJECTIVE)/depthAdjustment.o

run:
	./agent

dir:
	mkdir -p $(OBJECTIVE)
	mkdir -p $(TARGET)

clean:
	rm -rf $(OBJECTIVE)
	rm -rf $(TARGET)
	rm -f agent
	rm -f *.txt
	rm -f edgeStability.cpp
	rm -f depthAdjustment.cpp
