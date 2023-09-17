#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

void buildSegTree(vector<int> &seg_tree, vector<int> &array, int k, int x, int y) {
    if (x == y) {
        seg_tree[k] = array[x];
        return;
    }

    int middle = (x + y) / 2;
    buildSegTree(seg_tree, array, 2 * k, x, middle);
    buildSegTree(seg_tree, array, 2 * k + 1, middle + 1, y);

    seg_tree[k] = min(seg_tree[2 * k], seg_tree[2 * k + 1]);
}

void update_tree(vector<int> &seg_tree, vector<int> &lazy_values, int k, int x, int y, int a, int b, int vrednost) {
    if (lazy_values[k] != 0) {
        seg_tree[k] += lazy_values[k];

        if (x != y) {
            lazy_values[2 * k] += lazy_values[k];
            lazy_values[2 * k + 1] += lazy_values[k];
        }

        lazy_values[k] = 0;
    }

    if (x > b || y < a)
        return;
    if (x >= a && y <= b) {
        seg_tree[k] += vrednost;

        if (x != y) {
            lazy_values[2 * k] += vrednost;
            lazy_values[2 * k + 1] += vrednost;
        }
        return;
    }

    int middle = (x + y) / 2;
    update_tree(seg_tree, lazy_values, 2 * k, x, middle, a, b, vrednost);
    update_tree(seg_tree, lazy_values, 2 * k + 1, middle + 1, y, a, b, vrednost);

    seg_tree[k] = min(seg_tree[2 * k], seg_tree[2 * k + 1]);
}

int min_of_seg(vector<int> &seg_tree, vector<int> &lazy_values, int k, int x, int y, int a, int b) {
    if (lazy_values[k] != 0) {
        seg_tree[k] += lazy_values[k];

        if (x != y) {
            lazy_values[2 * k] += lazy_values[k];
            lazy_values[2 * k + 1] += lazy_values[k];
        }

        lazy_values[k] = 0;
    }

    if (x > b || y < a)
        return INT_MAX;
    if (x >= a && y <= b)
        return seg_tree[k];

    int middle = (x + y) / 2;
    return min(min_of_seg(seg_tree, lazy_values, 2 * k, x, middle, a, b),
               min_of_seg(seg_tree, lazy_values, 2 * k + 1, middle + 1, y, a, b));
}

int main() {
    vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();
    int height = ceil(log2(n));
    int size = 2 * pow(2, height);

    vector<int> seg_tree(size);
    vector<int> lazy_values(size, 0);

    buildSegTree(seg_tree, array, 1, 0, n - 1);

    //     a = 2  b = 5  vrednost = 4
    update_tree(seg_tree, lazy_values, 1, 0, n - 1, 2, 5, 4);
    //     a = 1  b = 3  vrednost = 7
    update_tree(seg_tree, lazy_values, 1, 0, n - 1, 1, 3, 7);

    int a, b;
    cout << "Unesi granice: ";
    cin >> a >> b;

    cout << "Min of seg: " << min_of_seg(seg_tree, lazy_values, 1, 0, n - 1, a, b) << "\n";


    return 0;
}
