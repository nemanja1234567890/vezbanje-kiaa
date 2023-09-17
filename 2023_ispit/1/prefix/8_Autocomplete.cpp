#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Node
{
    bool is_leaf = false;
    string word;
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
        if (root->nodes.find(c) == root->nodes.end()) {
            root->nodes[c] = new Node();
        }
        root = root->nodes[c];
    }

    root->is_leaf = true;
    root->word = word;
}

Node* findNode(Node *root, string &word) {
    for (char c : word) {
        if (root->nodes.find(c) == root->nodes.end())
            return nullptr;
        root = root->nodes[c];
    }

    return root;
}

void traverseTree(Node *root) {
    if (root->is_leaf)
        cout << root->word << " ";

    for (auto &iter : root->nodes)
        traverseTree(iter.second);
}

int main() {
    vector<string> words = { "code", "coder", "codecs", "coding", "cod"};

    Node *root = new Node();
    for (string &s : words)
        addWord(root, s);

    string rec;
    cout << "Unesi rec: ";
    cin >> rec;

    Node *tmp_node = findNode(root, rec);
    cout << "Ponudjeno: ";
    if (tmp_node) {
        traverseTree(tmp_node);
    }
    else {
        cout << "nepostoji";
    }
    cout << "\n";

    freeTree(root);
    return 0;
}
