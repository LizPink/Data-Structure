#include <iostream>
#include <string>
using namespace std;

void buildNext(const string& pattern, int* nxt) {
    int m = pattern.length();

    nxt[0] = 0;

    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = nxt[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            j++;
        }

        nxt[i] = j;
    }
}

bool kmpSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    int* nxt = new int[m];
    buildNext(pattern, nxt);

    int j = 0;

    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = nxt[j - 1];
        }

        if (text[i] == pattern[j]) {
            j++;
        }

        if (j == m) {
            delete[] nxt;
            return true;
        }
    }

    delete[] nxt;
    return false;
}

bool isCycleShift(const string& s1, const string& s2) {
    if (s1.length() != s2.length()) {
        return false;
    }

    string doubled = s1 + s1;

    return kmpSearch(doubled, s2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s1, s2;

    while (cin >> s1 >> s2) {
        if (isCycleShift(s1, s2)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}