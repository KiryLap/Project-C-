#include "functions1_by_Cheremshanov.h"

using namespace std;

AhoCorasick::AhoCorasick(const vector<string>& patterns) : patterns(patterns) { 
    root = new Node();
    for (int i = 0; i < patterns.size(); ++i) {
        Node* currentNode = root;
        for (char ch : patterns[i]) {
            if (!currentNode->children.count(ch)) {
                currentNode->children[ch] = new Node();
            }
            currentNode = currentNode->children[ch];
        }
        currentNode->output.push_back(i);
    }
    buildFailLinks();
}

void AhoCorasick::buildFailLinks() {
    root->failLink = root;
    queue<Node*> q;

    for (auto& pair : root->children) {
        pair.second->failLink = root;
        q.push(pair.second);
    }

    while (!q.empty()) {
        Node* currentNode = q.front();
        q.pop();

        for (auto& pair : currentNode->children) {
            char ch = pair.first;
            Node* child = pair.second;

            Node* fallback = currentNode->failLink;
            while (fallback != root && !fallback->children.count(ch)) {
                fallback = fallback->failLink;
            }
            if (fallback->children.count(ch)) {
                child->failLink = fallback->children[ch];
            } else {
                child->failLink = root;
            }

            child->output.insert(child->output.end(),
                                  child->failLink->output.begin(),
                                  child->failLink->output.end());

            q.push(child);
        }
    }
}

void AhoCorasick::search(const string& text) {
    if (patterns.empty() || patterns[0].empty()) {
        cout << "Совпадений не найдено." << endl;
        return;
    }

    Node* currentNode = root;
    bool foundMatch = false;  

    for (int i = 0; i < text.length(); ++i) {
        while (currentNode != root && !currentNode->children.count(text[i])) {
            currentNode = currentNode->failLink;
        }
        if (currentNode->children.count(text[i])) {
            currentNode = currentNode->children[text[i]];
        } else {
            currentNode = root;
        }

        for (int patternIndex : currentNode->output) {
            foundMatch = true;  
            cout << "Совпадение найдено на позиции: " << (i - patterns[patternIndex].length() + 1) << endl;
            return; 
        }
    }

    if (!foundMatch) {
        cout << "Совпадений не найдено." << endl;
    }
}

void function_by_Cheremshanov(const string& text, const string& pattern) {
    vector<string> patterns = { pattern }; 
    AhoCorasick ac(patterns);
    ac.search(text);
}
