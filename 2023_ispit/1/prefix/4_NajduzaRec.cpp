#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Node
{
    int count = 0;
    unordered_map<char, Node*> nodes;
};

void freeTree(Node *root) {
    if (root == nullptr)
        return;
    for (auto &iter : root->nodes)
        freeTree(iter.second);
    delete root;
}

int max_count = 0;
string max_word;
void addWord(Node *root, string &word) {
    for (char c : word) {
        if (root->nodes.find(c) == root->nodes.end())
            root->nodes[c] = new Node();
        root = root->nodes[c];
    }

    root->count++;
    if (root->count > max_count) {
        max_count = root->count;
        max_word = word;
    }
}

int main() {
    vector<string> words = {"cod", "codecs", "coding", "coder", "coding", "coder", "coding"};
    Node *root = new Node();

    for (string &s : words)
        addWord(root, s);

    cout << "Najcesca rec: " << max_word << "\t" << max_count << "\n";

    freeTree(root);
    return 0;
}
