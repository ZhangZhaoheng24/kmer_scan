CC := g++
#
CFLAGS := -std=c++11 -O3 -Wall -fopenmp
#
COBJS := scan.o readsdb.o kmerdb.o
LIBS := -lz

SCAN := scan

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

# all
all: $(SCAN)

# scan
$(SCAN): $(COBJS)
	$(CC) $(CFLAGS) -o $(SCAN) $(COBJS) $(LIBS) $(LDFLAG)
# clean
clean:
	-rm -f $(COBJS) $(SCAN) $(GOBJS) *~

.PHONY: all clean

# dependencies
scan.o: scan.cpp kmerdb.h readsdb.h
fastq_sequence.o: readsdb.cpp readsdb.h
kmerdb.o: kmerdb.cpp kmerdb.h
