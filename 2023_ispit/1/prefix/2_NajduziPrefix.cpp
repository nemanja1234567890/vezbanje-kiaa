#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Node
{
    bool is_leaf = false;
    unordered_map<char, Node*> nodes;
};

void freeTree(Node *root) {
    if (root == nullptr)
        return;
    for (auto &iter : root->nodes)
        freeTree(iter.second);
    delete root;
}

void addWord(Node *root, string &word) {
    for (char c : word) {
        if (root->nodes.find(c) == root->nodes.end())
            root->nodes[c] = new Node();
        root = root->nodes[c];
    }
    root->is_leaf = true;
}

void findPrefix(Node *root, string &prefix) {
    while (root->nodes.size() == 1 && !root->is_leaf) {
        auto iter = root->nodes.begin();

        prefix += iter->first;
        root = iter->second;
    }
}

int main() {
     vector<string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

    Node *root = new Node();

    for (string &s : words)
        addWord(root, s);

    string prefix_str;
    findPrefix(root, prefix_str);

    cout << "Najduzi prefiks: " << prefix_str << "\n";

    freeTree(root);
    return 0;
}
