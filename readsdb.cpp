#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <zlib.h>
#include <climits>
#include "readsdb.h"
using namespace std;
unordered_map<string, unsigned long> Readsdb::CountFastqKmer(
                const string &FastqFile, const unsigned int KmerSize,
                const string &FastqOut,unordered_map<string,unsigned long> &KmerHash,
                unsigned long &count_reads) const {
        long max_reads_len=1000;
        string ends="gz";
	gzFile file = gzopen(FastqFile.c_str(), "rb");
        if (!file) {
                cerr << "[error] " << "Could not open " << FastqFile << endl;
                exit(1);
        }
	ofstream ofs(FastqOut.c_str());
        if (!ofs) {
                cerr << "[error] " << "Could not open " << FastqOut << endl;
                exit(1);
        }
	clock_t start,now;
        char buff[max_reads_len];
        string mer;
        string line[4];
        unsigned int nLine = 0;
        unsigned long nreads = 0;
	start=clock();
        while (gzgets(file, buff, max_reads_len) != Z_NULL) {

                line[nLine++] = string(buff);
                if (nLine == 4) {
                        bool  lock = false;
                        nLine = 0;
                        if (++nreads % 1000000 == 0) {
                                now=clock();
                                cerr << FastqFile << ": parsing " << nreads/1000000 << "Mb reads."	<<"time = "<<double(now-start)/CLOCKS_PER_SEC<<"s" <<endl;
                        }

                        if (line[0][0] != '@' || line[2][0] != '+') {
                                line[0].erase(--line[0].end());
                                cerr << "ERROR: file not is fastq in (" << line[0] << ") line." << endl;
                                exit(1);
                        }
                        if (line[1].length() > KmerSize) {
                                line[1].erase(--line[1].end());
                                for (unsigned long i = 0; i <= line[1].length() - KmerSize; i++) {
                                        count_reads++;
                                        mer.assign(line[1], i, KmerSize);
                                        if (KmerHash.find(mer) != KmerHash.end()){
                                                KmerHash[mer]++;
                                                if (lock == false){
                                                        ofs << line[0] << line[1] << "\n" << line[2] << line[3];
                                                        lock = true;
                                                }
                                        }
                                }
                        }
                }
        }
gzclose(file);
return KmerHash;
ofs.close();
}
