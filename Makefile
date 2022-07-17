UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CC := g++
else
	CC := /usr/local/opt/llvm/bin/clang++
	LDFLAG := -L/usr/local/opt/llvm/lib
endif
#
CFLAGS := -std=c++11 -O3 -Wall -fopenmp
#
COBJS := scan.o readsdb.o kmerdb.o
LIBS := -lz

COUNTMER := SCAN
#GTEST := gtest

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

# all
all: $(COUNTMER)

# countmer
$(COUNTMER): $(COBJS)
	$(CC) $(CFLAGS) -o $(COUNTMER) $(COBJS) $(LIBS) $(LDFLAG)

# gtest
#$(GTEST): $(GOBJS)
#	$(CC) $(CFLAGS) -o $(GTEST) $(GOBJS) $(LDFLAG)

# clean
clean:
	-rm -f $(COBJS) $(COUNTMER) $(GOBJS) *~

.PHONY: all clean

# dependencies
scan.o: scan.cpp kmerdb.h readsdb.h
fastq_sequence.o: readsdb.cpp readsdb.h
kmerdb.o: kmerdb.cpp kmerdb.h
