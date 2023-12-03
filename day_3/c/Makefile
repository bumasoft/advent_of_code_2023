all: executable

debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: executable

executable: main.c ancillary.h adjacent.h part_one.h part_two.h
	$(CC) $(CCFLAGS) -o gears ancillary.c adjacent.c part_one.c part_two.c main.c

clean:
	rm gears && rm -rf gears.dSYM