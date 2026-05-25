#include <cstdio>

class FastInput {
private:
    static const int BUFFER_SIZE = 1 << 20;
    char buffer[BUFFER_SIZE];
    int position;
    int length;

public:
    FastInput() {
        position = 0;
        length = 0;
    }

    int readChar() {
        if (position >= length) {
            length = (int)std::fread(buffer, 1, BUFFER_SIZE, stdin);
            position = 0;

            if (length == 0) {
                return EOF;
            }
        }

        return buffer[position++];
    }

    int readInt() {
        int ch = readChar();

        while (ch != EOF && (ch < '0' || ch > '9')) {
            ch = readChar();
        }

        int value = 0;

        while (ch >= '0' && ch <= '9') {
            value = value * 10 + ch - '0';
            ch = readChar();
        }

        return value;
    }
};

int main() {
    FastInput input;

    int n = input.readInt();
    int m = input.readInt();

    int* head = new int[n + 1];
    int* inDegree = new int[n + 1];
    int* dp = new int[n + 1];

    for (int i = 1; i <= n; ++i) {
        head[i] = -1;
        inDegree[i] = 0;
        dp[i] = 1;
    }

    int* to = new int[m];
    int* next = new int[m];

    for (int i = 0; i < m; ++i) {
        int u = input.readInt();
        int v = input.readInt();

        to[i] = v;
        next[i] = head[u];
        head[u] = i;

        ++inDegree[v];
    }

    int* queue = new int[n + 1];
    int front = 0;
    int rear = 0;

    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int answer = 1;

    while (front < rear) {
        int u = queue[front++];

        if (dp[u] > answer) {
            answer = dp[u];
        }

        for (int edge = head[u]; edge != -1; edge = next[edge]) {
            int v = to[edge];

            if (dp[v] < dp[u] + 1) {
                dp[v] = dp[u] + 1;
            }

            --inDegree[v];

            if (inDegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    std::printf("%d\n", answer);

    delete[] head;
    delete[] inDegree;
    delete[] dp;
    delete[] to;
    delete[] next;
    delete[] queue;

    return 0;
}