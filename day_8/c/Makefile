EXE_FILE = wasteland

all: executable

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: executable

executable: main.c bumasoft/*.h aoc.h solution.h
	$(CC) $(CCFLAGS) -o $(EXE_FILE) bumasoft/*.c main.c solution.c

clean:
	rm $(EXE_FILE) && rm -rf $(EXE_FILE).dSYM