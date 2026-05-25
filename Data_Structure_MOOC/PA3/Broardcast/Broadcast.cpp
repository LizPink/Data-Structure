#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    int* head = new int[n + 1];
    int* to = new int[2 * m];
    int* nxt = new int[2 * m];

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }

    int edgeCount = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        to[edgeCount] = v;
        nxt[edgeCount] = head[u];
        head[u] = edgeCount;
        edgeCount++;

        to[edgeCount] = u;
        nxt[edgeCount] = head[v];
        head[v] = edgeCount;
        edgeCount++;
    }

    int* color = new int[n + 1];
    for (int i = 1; i <= n; i++) {
        color[i] = -1;
    }

    int* q = new int[n + 1];

    bool ok = true;

    for (int start = 1; start <= n && ok; start++) {
        if (color[start] != -1) {
            continue;
        }

        int front = 0;
        int rear = 0;

        color[start] = 0;
        q[rear++] = start;

        while (front < rear && ok) {
            int u = q[front++];

            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];

                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q[rear++] = v;
                } else if (color[v] == color[u]) {
                    ok = false;
                    break;
                }
            }
        }
    }

    if (ok) {
        cout << 1 << '\n';
    } else {
        cout << -1 << '\n';
    }

    delete[] head;
    delete[] to;
    delete[] nxt;
    delete[] color;
    delete[] q;

    return 0;
}