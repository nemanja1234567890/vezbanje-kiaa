#include <iostream>
#include <vector>

using namespace std;

vector<int> roditelj;
vector<int> rang;

void napravi_dsu(int n) {
    roditelj.resize(n);
    rang.resize(n, 1);

    // na pocetku je svako sam sebi roditelj uvek
    for (int i = 0; i < n; i++)
        roditelj[i] = i;
}

int predstavnik(int a) {
    int t = a;

    // odredjujemo predstavnika
    while (roditelj[t] != t) {
        t = roditelj[t];
    }

    // sve cvorove na putu do svog predstavnika vezujemo direktno na njega (opciona optimizacija dovoljno je i bez toga)
    while (a != t) {
        int tmp = roditelj[a];
        roditelj[a] = t;
        a = tmp;
    }

    return a;
}

void unija(int a, int b) {
    a = predstavnik(a);
    b = predstavnik(b);

    // ako imaju istog predstavnika kraj ne treba nista
    if (a == b)
        return;


    // uvek vezujemo manje prema vece
    if (rang[a] < rang[b]) {
        roditelj[a] = b;
        rang[b] += rang[a];
    }
    else {
        roditelj[b] = a;
        rang[a] += rang[b];
    }
}

int main() {
    int n, a, b;

    printf("n = ");
    cin >> n;

    napravi_dsu(n);

    while (true) {
        string operacija;
        cout << "Unesi operaciju: ";
        cin >> operacija;

        if (operacija == "unija") {
            cin >> a >> b;
            unija(a, b);
        }
        else if (operacija == "predstavnik"){
            cin >> a;
            cout << predstavnik(a) << "\n";
        }
    }

    return 0;
}
