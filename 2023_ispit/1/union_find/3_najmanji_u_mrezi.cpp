#include <iostream>
#include <vector>

using namespace std;

vector<int> roditelj;
vector<int> rang;
vector<int> najmanji;

void napravi_dsu(int n) {
    roditelj.resize(n);
    rang.resize(n, 1);
    najmanji.resize(n);

    for (int i = 0; i < n; i++) {
        roditelj[i] = i;
        najmanji[i] = i;
    }
}

int predstavnik(int a) {
    while (roditelj[a] != a) {
        a = roditelj[a];
    }
    return a;
}

void unija(int a, int b) {
    a = predstavnik(a);
    b = predstavnik(b);

    // ako su isti koreni
    if (a == b)
        return;

    if (rang[a] < rang[b]) { // kacimo na b
        roditelj[a] = b;
        rang[b] += rang[a];
        najmanji[b] = min(najmanji[a], najmanji[b]);
    }
    else { // kaicmo na a
        roditelj[b] = a;
        rang[a] += rang[b];
        najmanji[a] = min(najmanji[a], najmanji[b]);
    }
}

int main() {
    int n, m, a, b;

    cout << "n = ";
    cin >> n;

    cout << "Unesi broj upita: ";
    cin >> m;

    napravi_dsu(n);

    string operacija;
    while (m--){
        cout << "Unesi operaciju: ";
        cin >> operacija;

        if (operacija == "unija") {
            cin >> a >> b;
            unija(a, b);
        }
        else if (operacija == "najmanji") {
            cin >> a;
            cout << najmanji[predstavnik(a)] << "\n";
        }
    }

    return 0;
}
