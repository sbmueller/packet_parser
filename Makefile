all:
	g++ -std=c++11 packet.cpp parser.cpp solution.cpp -o solution
clean:
	rm solution