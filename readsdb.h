
#include <string>
#include <unordered_map>
using namespace std;

class Readsdb {
public:
	unordered_map<string, unsigned long> CountFastqKmer(
			const string &FastqFile, const unsigned int KmerSize,
			const string &FastqOut,unordered_map<string,unsigned long> &KmerHash,
			unsigned long &count_reads) const;
};


