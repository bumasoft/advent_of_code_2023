EXE_FILE = camelcards

all: executable

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: executable

executable: main.c bumasoft/*.h aoc.h solution.h
	$(CC) $(CCFLAGS) -o $(EXE_FILE) bumasoft/*.c solution.c main.c

clean:
	rm $(EXE_FILE) && rm -rf $(EXE_FILE).dSYM