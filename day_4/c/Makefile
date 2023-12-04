EXE_FILE = scratchcards

all: executable

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: executable

executable: main.c ancillary.h num_cell.h part_one.h part_two.h
	$(CC) $(CCFLAGS) -o $(EXE_FILE) ancillary.c num_cell.c part_one.c part_two.c main.c

clean:
	rm $(EXE_FILE) && rm -rf $(EXE_FILE).dSYM