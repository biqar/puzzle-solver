CC=g++
CFLAGS=-I.
directory=build

all:
	mkdir -p $(directory)
	$(CC) $(CFLAGS) src/bfs.cpp -o $(directory)/bfs
	$(CC) $(CFLAGS) src/dfs_recursive.cpp -o $(directory)/dfs_recursive
	$(CC) $(CFLAGS) src/dfs_stack.cpp -o $(directory)/dfs_stack
	$(CC) $(CFLAGS) src/dls.cpp -o $(directory)/dls
	$(CC) $(CFLAGS) src/ids.cpp -o $(directory)/ids
	$(CC) $(CFLAGS) src/ucs.cpp -o $(directory)/ucs
	$(CC) $(CFLAGS) src/a_star.cpp -o $(directory)/a_star
