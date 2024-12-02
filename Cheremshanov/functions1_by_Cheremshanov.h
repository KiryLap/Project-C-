#ifndef FUNCTIONS1_BY_CHEREMSHANOV_H
#define FUNCTIONS1_BY_CHEREMSHANOV_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

class AhoCorasick {
private:
    struct Node {
        unordered_map<char, Node*> children;
        Node* failLink;
        vector<int> output; 
    };

    Node* root;
    vector<string> patterns; 

    void buildFailLinks();

public:
    AhoCorasick(const vector<string>& patterns);

    void search(const string& text);
};

void function_by_Cheremshanov(const string& text, const string& pattern);

#endif
