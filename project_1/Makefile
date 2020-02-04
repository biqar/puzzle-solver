CC=g++
CFLAGS=-std=c++11 -g -Wall -I./ -O2
SUBDIRS=src/core
SUBSRCS=$(wildcard core/*.cpp) $(wildcard 8-puzzle/*.cpp)
OBJECTS=$(SUBSRCS:.cpp=.o)
EXEC=puzzle
directory=build

all: $(SUBDIRS) $(EXEC)

$(SUBDIRS):
	$(MAKE) -C $@

$(EXEC): src/puzzle.cpp $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
	$(RM) $(EXEC)

.PHONY: $(SUBDIRS) $(EXEC)

# all:
# 	mkdir -p $(directory)
# 	$(CC) $(CFLAGS) src/bfs.cpp -o $(directory)/bfs
# 	$(CC) $(CFLAGS) src/bfs_bidir.cpp -o $(directory)/bfs_bidir
# 	$(CC) $(CFLAGS) src/bfs_greedy.cpp -o $(directory)/bfs_greedy
# 	$(CC) $(CFLAGS) src/dfs_recursive.cpp -o $(directory)/dfs_recursive
# 	$(CC) $(CFLAGS) src/dfs_stack.cpp -o $(directory)/dfs_stack
# 	$(CC) $(CFLAGS) src/dls.cpp -o $(directory)/dls
# 	$(CC) $(CFLAGS) src/dls_bidir.cpp -o $(directory)/dls_bidir
# 	$(CC) $(CFLAGS) src/ids.cpp -o $(directory)/ids
# 	$(CC) $(CFLAGS) src/ids_bidir.cpp -o $(directory)/ids_bidir
# 	$(CC) $(CFLAGS) src/a_star.cpp -o $(directory)/a_star
# 	$(CC) $(CFLAGS) src/ida_star.cpp -o $(directory)/ida_star
