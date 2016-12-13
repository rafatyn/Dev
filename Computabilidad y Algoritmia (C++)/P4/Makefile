CXX=g++ 
CXXFLAGS=-g

OBJS = transicion.o estado.o nfa.o main.o

all: ${OBJS}
	$(CXX) $(CXXFLAGS) -o nfa ${OBJS}

clean: 
	rm -rf *.o NFA
