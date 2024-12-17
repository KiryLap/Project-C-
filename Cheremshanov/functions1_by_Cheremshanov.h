#ifndef FUNCTIONS1_BY_CHEREMSHANOV_H
#define FUNCTIONS1_BY_CHEREMSHANOV_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

class AhoCorasick {
public:
    struct Node {
        unordered_map<char, Node*> children;
        Node* failLink;
        vector<int> output;

        Node() : failLink(nullptr) {}
    };

    AhoCorasick(const vector<string>& patterns);
    void search(const string& text, vector<int>& result_indices);

private:
    vector<string> patterns;
    Node* root;

    void buildFailLinks();
};

vector<int> function_by_Cheremshanov(const string& text, const string& pattern);

#endif
