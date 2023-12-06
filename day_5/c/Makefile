EXE_FILE = fertilizer

all: executable

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: executable

executable: main.c bumasoft/*.h aoc.h part_one.h part_two.h
	$(CC) $(CCFLAGS) -o $(EXE_FILE) bumasoft/*.c part_one.c part_two.c main.c

clean:
	rm $(EXE_FILE) && rm -rf $(EXE_FILE).dSYM