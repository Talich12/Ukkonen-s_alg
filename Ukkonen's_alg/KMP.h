#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


vector<int> prefix_function(string str) {
    vector<int> pi(str.size());
    for (int i = 1; i < str.size(); i++) {
        int j = pi[i - 1];
        while (j > 0 && str[i] != str[j]) {
            j = pi[j - 1];
        }
        if (str[i] == str[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

int KMP(string str, string substr) {
    int size = substr.size();

    substr.push_back('$');
    substr.append(str);
    vector<int> pi = prefix_function(substr);

    for (int i = size + 1; i < pi.size(); i++) {
        if (pi[i] == size) { 
            return i - size * 2;
        }
    }
    return -1;
}
