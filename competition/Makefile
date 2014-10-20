agent:
	g++ -c utilities.cpp -o utilities.o
	g++ -c greedy.cpp -o greedy.o
	g++ -c minimax.cpp -o minimax.o
	g++ -c alphabeta.cpp -o alphabeta.o
	g++ -c edgeStability.cpp -o edgeStability.o
	g++ -c competition.cpp -o competition.o
	g++ -c agent1.cpp -o agent1.o
	g++ -c agent2.cpp -o agent2.o
	g++ agent1.o utilities.o greedy.o minimax.o alphabeta.o edgeStability.o competition.o -o agent1
	g++ agent2.o utilities.o greedy.o minimax.o alphabeta.o edgeStability.o competition.o -o agent2
	g++ check1.cpp -o check1
	g++ check2.cpp -o check2

run:
	./run.sh