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

void ispisi(vector<int> niz) {
    for (int x : niz)
        cout << x << " ";
    cout << "\n";
}

void update_tree(vector<int> &seg_tree, vector<int> &lazy_values, int k, int x, int y, int a, int b, int vrednost) {
    if (lazy_values[k] != 0) {
        seg_tree[k] += lazy_values[k] * (y - x + 1);

        if (x != y) {
            lazy_values[2 * k] += lazy_values[k];
            lazy_values[2 * k + 1] += lazy_values[k];
        }

        lazy_values[k] = 0;
    }

    if (x > b || y < a)
        return;
    if (x >= a && y <= b) {
        seg_tree[k] += vrednost * (y - x + 1);

        if (x != y) {
            lazy_values[2 * k] += vrednost;
            lazy_values[2 * k + 1] += vrednost;
        }
        return;
    }

    int middle = (x + y) / 2;
    update_tree(seg_tree, lazy_values, 2 * k, x, middle, a, b, vrednost);
    update_tree(seg_tree, lazy_values, 2 * k + 1, middle + 1, y, a, b, vrednost);

    // na kraj mora da updatujemo i vrednosti
    seg_tree[k] = seg_tree[2 * k] + seg_tree[2 * k + 1];
}

int suma_seg(vector<int> &seg_tree, vector<int> &lazy_values, int k, int x, int y, int a, int b) {
    // skroz isti deo koda kao kod update
    if (lazy_values[k] != 0) {
        seg_tree[k] += lazy_values[k] * (y - x + 1);

        if (x != y) {
            lazy_values[2 * k] += lazy_values[k];
            lazy_values[2 * k + 1] += lazy_values[k];
        }

        lazy_values[k] = 0;
    }

    // ovaj deo je isti kao kod obicnog suma_seg
    if (x > b || y < a)
        return 0;
    if (x >= a && y <= b)
        return seg_tree[k];

    int middle = (x + y) / 2;
    return suma_seg(seg_tree, lazy_values, 2 * k, x, middle, a, b)
            + suma_seg(seg_tree, lazy_values, 2 * k + 1, middle + 1, y, a, b);
}

int main() {
    vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8};

    int n = array.size();
    int height = ceil(log2(n));
    int size = 2 * pow(2, height);

    vector<int> seg_tree(size);
    vector<int> lazy_values(size, 0);

    buildSegTree(seg_tree, array, 1, 0, n - 1);
//     cout << "Seg_tree: ";
//     ispisi(seg_tree);

    //     a = 2 b = 4 vrednost = 4
    update_tree(seg_tree, lazy_values, 1, 0, n - 1, 2, 4, 4);
    //     a = 1  b = 3 vrednost = 7
    update_tree(seg_tree, lazy_values, 1, 0, n - 1, 1, 3, 7);

    int a, b;
    cout << "Unesi granice za zbir: ";
    cin >> a >> b;
    cout << "Suma seg[2, 4]: " << suma_seg(seg_tree, lazy_values, 1, 0, n - 1, a, b) << "\n";

    return 0;
}
