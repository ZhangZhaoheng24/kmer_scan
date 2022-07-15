
#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>
#include "kmerdb.h"

using namespace std;

// Read the Kmer database file.

void Kmerdb::KmerToHash(const string &KmerFile, const unsigned int KmerSize,
		unordered_map<string, unsigned long> &KmerHash) const {
	ifstream ifs(KmerFile.c_str());
	if (!ifs) {
		cerr << "[error] " << "Could not open " << KmerFile << endl;
		exit(1);
	}

	string line;
	string kmerseq = "";
	while (getline(ifs, line)) {
		if (line[0] != '>') {
			if (line[line.size() - 1] == '\n') {
				line.erase(--line.end());
			}
			if (line[line.size() - 1] == '\r') {
				line.erase(--line.end());
			}
			kmerseq += line;
			kmerseq += kmerseq.substr(0, KmerSize - 1);
			// Convert to upper case
			transform(kmerseq.begin(), kmerseq.end(), kmerseq.begin(), ::toupper);
			unsigned long i = 0;
			string mer = kmerseq.substr(i, KmerSize);
			string revMer(mer);
			// Complementary kmerseq of kmer
			reverse(revMer.begin(), revMer.end());
			for (unsigned int j = 0; j < KmerSize; j++) {
				switch (revMer[j]) {
				case 'A':
					revMer[j] = 'T';
					break;
				case 'T':
					revMer[j] = 'A';
					break;
				case 'G':
					revMer[j] = 'C';
					break;
				case 'C':
					revMer[j] = 'G';
					break;
				default:
					break;
				}
			}
			KmerHash[mer] = 0;
			KmerHash[revMer] = 0;
			kmerseq = "";
		}
	}
}

