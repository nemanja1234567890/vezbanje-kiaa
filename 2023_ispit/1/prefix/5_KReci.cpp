#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

struct Node
{
    bool is_leaf = false;
    int count = 0;
    string word;
    unordered_map<char, Node*> nodes;
};

struct my_compare
{
    bool operator() (Node *n1, Node *n2)  {
        return n2->count > n1->count;
    }
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
    root->count++;
    root->word = word;
}

void fillPQ(Node *root, priority_queue<Node*, vector<Node*>, my_compare> &max_heap) {
    if (root->is_leaf)
        max_heap.push(root);
    for (auto &iter : root->nodes)
        fillPQ(iter.second, max_heap);
}

int main() {
    vector<string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

    Node *root = new Node();
    for (string &s : words)
        addWord(root, s);

    priority_queue<Node*, vector<Node*>, my_compare> max_heap;
    fillPQ(root, max_heap);

    int n;
    cout << "n = ";
    cin >> n;

    Node *tmp_node;
    while (n) {
        tmp_node = max_heap.top();
        max_heap.pop();

        cout << tmp_node->word << "\t" << tmp_node->count << "\n";

        n--;
    }

    freeTree(root);
    return 0;
}
