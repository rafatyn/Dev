CC=g++ 
CXXFLAGS=-g

OBJS = transition_state_t.o state_t.o DFA.o main.o

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o DFA ${OBJS}

clean: 
	rm -rf *.o dfa
