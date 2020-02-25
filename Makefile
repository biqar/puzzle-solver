CC=g++
CFLAGS=-std=c++11 -g -Wall -I./ -O2
SUBDIRS=src/core
SUBSRCS=$(wildcard src/core/*.cc)
OBJECTS=$(SUBSRCS:.cc=.o)
EXEC=puzzle
directory=build

all: $(SUBDIRS) $(EXEC)

$(SUBDIRS):
	$(MAKE) -C $@

$(EXEC): src/puzzle.cc $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
	$(RM) $(EXEC)

.PHONY: $(SUBDIRS) $(EXEC)
