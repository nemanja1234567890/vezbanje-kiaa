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

bool findNode(Node *root, string &word) {
    for (char c : word) {
        if (root->nodes.find(c) == root->nodes.end())
            return false;
        root = root->nodes[c];
    }

    return root->is_leaf;
}

int main() {
    vector<string> words = {"cod", "coder", "coding", "codecs"};
    Node *root = new Node();

    for (string &s : words)
        addWord(root, s);

    string rec;
    cout << "Unesi rec: ";
    cin >> rec;

    cout << "Rec se nalazi u stablu: " << boolalpha << findNode(root, rec) << "\n";

    freeTree(root);
    return 0;
}
