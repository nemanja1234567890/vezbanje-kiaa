#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void buildSegTree(vector<int> &seg_tree, vector<int> &array, int k, int x, int y) {
    if (x == y) {
        seg_tree[k] = array[x];

        return;
    }

    int middle = (x + y) / 2;
    buildSegTree(seg_tree, array, 2 * k, x, middle);
    buildSegTree(seg_tree, array, 2 * k + 1, middle + 1, y);

    seg_tree[k] = seg_tree[2 * k] + seg_tree[2 * k + 1];
}

void updateTree(vector<int> &seg_tree, int k, int x, int y, int indeks, int vrednost) {
    if (x == y) {
        seg_tree[k] = vrednost;

        return;
    }

    int middle = (x + y) / 2;

    if (indeks <= middle)
        updateTree(seg_tree, 2 * k, x, middle, indeks, vrednost);
    else
        updateTree(seg_tree, 2 * k + 1, middle + 1, y, indeks, vrednost);

    seg_tree[k] = seg_tree[2 * k] + seg_tree[2 * k + 1];
}

void ispisi(vector<int> niz) {
    for (int x : niz)
        cout << x << " ";
    cout << "\n";
}

int main() {
    vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();
    int heigh = ceil(log2(n));
    int size = 2 * pow(2, heigh);

    vector<int> seg_tree(size);
    buildSegTree(seg_tree, array, 1, 0, n - 1);

    cout << "Original drvo: ";
    ispisi(seg_tree);

    int indeks, vrednost;
    cout << "Unesi indeks, vrednost: ";
    cin >>indeks >> vrednost;

    updateTree(seg_tree, 1, 0, n - 1, indeks, vrednost);

    cout << "Update drvo: ";
    ispisi(seg_tree);

    return 0;
}
