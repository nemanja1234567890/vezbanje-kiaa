#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Node
{
    bool is_leaf = false;
    string word;
    map<char, Node*> nodes;
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
    root->word = word;
}

void traverseTree(Node *root) {
    if (root->is_leaf)
        cout << root->word << "\n";

    for (auto &iter : root->nodes)
        traverseTree(iter.second);
}

int main() {
            vector<string> words = {"ana", "anastasija", "anastasijin", "anamarija", "anamarijin"};
//     vector<string> words = {"cod", "coder", "coding", "codecs"};

    Node *root = new Node();
    for (string &s : words)
        addWord(root, s);

    cout << "Sortirano:\n";
    traverseTree(root);

    freeTree(root);
    return 0;
}
