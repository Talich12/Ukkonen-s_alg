#include "SuffixTree.h"
#include "Ukkonen's_alg.h"
#include "KMP.h"

#include <chrono>

using namespace std;
using namespace std::chrono;


std::string gen_random(const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::string tmp_s;
	tmp_s.reserve(len);

	for (int i = 0; i < len; ++i) {
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return tmp_s;
}

int main() {

	string str = "absasldfhjsjakhdfkljhsaldkfhlksahdflkjasdhflksahdljkfhlsakdhfljashdfhashlkjhjlkafshjkalsfdhjlkasfdhjklsafdhjfkaldshjafksdlhjlfkdasjhlkdfashjlkdfashjklsdafhjkldfsahjkldfsahjlkfsdajhkldfashjlkasdfjhlkasdfjhlkadsfhjlkadsfhljkadfslhjkdafshjlkadsfjhlkdafshjlfdhjalskadsfjhlkdhjflsakdfjhsladfshjlaksdfajhldfshjaklsdfhjklsdfajhklsdfahljkhjlfksdahjlksdfakjfhsadljkfhewuqyhoriuweqhiufmhqwuefhoqwuiehmfisdgbaofhubuwhqbeuygbrqwygebruhqwberyhbw7ebrhyqwberyhuwqijermqw7uyherbnywhqebryhuwnqeuyhaslkdhflksahdflkjhsadkljfhsalkjdyfbluksabetluyfgbalseufhskduahnfsadgnfgsaydgvfmysagvdyufbsmayudfbmigsabdfmhbsadiufvisuaybfiutyefnasdknflkjsadhfuwyqeoruqwpioeursdhfkbsadfnbxzcbvsjadfhlksajdhflksahadfsadfsadfasdcabxabasdfasdfasdfcd";
	string substr = "abx";
	auto start = high_resolution_clock::now();	

	Substring_search_in_string(str, substr);

	cout << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by function: "
		<< duration.count() << " microseconds" << endl;
	cout << endl;

	auto start1 = high_resolution_clock::now();

	KMP(str, substr);

	cout << endl;
	auto stop1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(stop1 - start1);

	cout << "Time taken by function: "
		<< duration1.count() << " microseconds" << endl;
	cout << endl;

}