#include <string>
#include <fstream>
#include <map>
#include <climits>
#include "readsdb.h"
#include "kmerdb.h"
#include <iostream>
using namespace std;


Kmerdb *kmerdb;
Readsdb *readsdb;	
/**
* Write the merFreq.txt file.
*/
void CountKmer(string prefix,
	const unordered_map<string, unsigned long> &KmerHash){
	string outfile = prefix + "_mer_count.txt";
	ofstream ofs(outfile.c_str());
	if (!ofs) {
		cerr << "[Error] " << "Could not open " << outfile << endl;
		exit(1);
	}

	map < string, unsigned long> sortedCount(KmerHash.begin(),
			KmerHash.end());
	
	for (map<string, unsigned long>::iterator itr =
			sortedCount.begin(); itr != sortedCount.end(); ++itr) {
		ofs << itr->first << '\t' << itr->second << endl;
	}
	ofs.close();
}

void execution(const string &KmerFile, const unsigned int KmerSize,
	const string &FastqFile,const string &FastqOut,string prefix) {

	unordered_map<string, unsigned long> KmerHash;

	//Read kmer database file

	kmerdb->KmerToHash(KmerFile, KmerSize, KmerHash);

	//Read reads files (fastq.gz)
	unsigned long count_reads = 0;

	unordered_map<string, unsigned long> KmerHash_n =
			readsdb->CountFastqKmer(FastqFile, KmerSize,
					FastqOut, KmerHash, count_reads);

	/**
	* Write the Kmer count file.
	*/
	cout << count_reads << endl;
	CountKmer(prefix,KmerHash_n);
}


int main(int argc, char* argv[]) {
    if (argc != 6) {
        cerr << "Usage: " << argv[0] << " <KmerFile> <KmerSize> <InputFile> <OutReads> <OutKmerFreq>" << endl;
        return 1;
    }
    unsigned int kmerSize = stoi(argv[2]);
    execution(argv[1], kmerSize, argv[3], argv[4], argv[5]);
    return 0;
