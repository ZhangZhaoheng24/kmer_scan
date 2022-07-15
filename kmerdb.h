
#include <string>
#include <unordered_map>
using namespace std;

class Kmerdb {

public:



	void KmerToHash(const string &KmerFile, const unsigned int KmerSize,
			unordered_map<string, unsigned long> &KmerHash) const;

};

