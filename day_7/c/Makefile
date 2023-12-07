EXE_FILE = camelcards

all: executable

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: executable

executable: main.c bumasoft/*.h aoc.h cards.h solution.h
	$(CC) $(CCFLAGS) -o $(EXE_FILE) bumasoft/*.c cards.c solution.c main.c

clean:
	rm $(EXE_FILE) && rm -rf $(EXE_FILE).dSYM