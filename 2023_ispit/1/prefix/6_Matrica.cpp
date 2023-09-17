#include <iostream>
#include <vector>

#define MAX_SIZE (100)

using namespace std;

struct Node
{
    bool is_leaf;
    vector<int> duplicates;
    Node *nodes[2];
};

Node* createNode() {
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->is_leaf = false;
    new_node->nodes[0] = new_node->nodes[1] = nullptr;

    return new_node;
}

void freeTree(Node *root) {
    if (root == nullptr)
        return;
    for (auto &iter : root->nodes)
        freeTree(iter);
    free(root);
}

void addRow(Node *root, int row[MAX_SIZE], int n, int i, int row_num) {
    while (i < n) {
        if (root->nodes[row[i]] == nullptr) {
            root->nodes[row[i]] = createNode();
        }
        root = root->nodes[row[i]];

        i++;
    }

    root->is_leaf = true;
    root->duplicates.push_back(row_num);
}

void traverseTree(Node *root) {
    if (root->is_leaf) {
        if (root->duplicates.size() > 1) {
            for (int el : root->duplicates)
                cout << el << " ";
            cout << "\n";
        }

        return;
    }



    if (root->nodes[0])
        traverseTree(root->nodes[0]);
    if (root->nodes[1])
        traverseTree(root->nodes[1]);
}

int main() {
    int matrix[MAX_SIZE][MAX_SIZE] = {
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
		{0, 1, 1, 0, 0},
		{1, 0, 0, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
        {1, 0, 0, 1, 0}
    };
    int n = 5;
    int m = 8;

    Node *root = createNode();
    for (int i = 0; i < m; i++) {
        addRow(root, matrix[i], n, 0, i + 1);
    }

    cout << "Duplikati:\n";
    traverseTree(root);

    freeTree(root);
    return 0;
}
