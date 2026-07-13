#include <cstdio>

const int STATE_NUM = 40320;

int fact[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int distArr[STATE_NUM];
int q[STATE_NUM];

// 康托展开：把 1~8 的排列编码为 0~40319
int encodeState(int a[]) {
    int code = 0;

    for (int i = 0; i < 8; i++) {
        int smaller = 0;

        for (int j = i + 1; j < 8; j++) {
            if (a[j] < a[i]) {
                smaller++;
            }
        }

        code += smaller * fact[7 - i];
    }

    return code;
}

// 康托逆展开：把编号还原为排列
void decodeState(int code, int a[]) {
    bool used[9];

    for (int i = 1; i <= 8; i++) {
        used[i] = false;
    }

    for (int i = 0; i < 8; i++) {
        int f = fact[7 - i];
        int kth = code / f;
        code %= f;

        int cnt = -1;

        for (int v = 1; v <= 8; v++) {
            if (!used[v]) {
                cnt++;

                if (cnt == kth) {
                    a[i] = v;
                    used[v] = true;
                    break;
                }
            }
        }
    }
}

/*
状态表示规则：
a[0] a[1] a[2] a[3] 是上排从左到右
a[4] a[5] a[6] a[7] 是下排从右到左

为了求“当前状态 -> 初始状态”的最短步数，
从初始状态开始 BFS 时要使用 A、B、C 的逆操作。
*/

// A 的逆操作还是 A：交换上下两行
void opAInverse(int a[], int b[]) {
    b[0] = a[7];
    b[1] = a[6];
    b[2] = a[5];
    b[3] = a[4];
    b[4] = a[3];
    b[5] = a[2];
    b[6] = a[1];
    b[7] = a[0];
}

// B 是循环右移，所以 B 的逆操作是循环左移
void opBInverse(int a[], int b[]) {
    b[0] = a[1];
    b[1] = a[2];
    b[2] = a[3];
    b[3] = a[0];

    b[4] = a[7];
    b[5] = a[4];
    b[6] = a[5];
    b[7] = a[6];
}

// C 是中心顺时针旋转，所以这里用中心逆时针旋转
void opCInverse(int a[], int b[]) {
    b[0] = a[0];
    b[1] = a[2];
    b[2] = a[5];
    b[3] = a[3];

    b[4] = a[4];
    b[5] = a[6];
    b[6] = a[1];
    b[7] = a[7];
}

void buildBFS() {
    for (int i = 0; i < STATE_NUM; i++) {
        distArr[i] = -1;
    }

    int start[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int startCode = encodeState(start);

    int front = 0;
    int rear = 0;

    distArr[startCode] = 0;
    q[rear++] = startCode;

    int cur[8];
    int nxt[8];

    while (front < rear) {
        int code = q[front++];
        decodeState(code, cur);

        for (int op = 0; op < 3; op++) {
            if (op == 0) {
                opAInverse(cur, nxt);
            } else if (op == 1) {
                opBInverse(cur, nxt);
            } else {
                opCInverse(cur, nxt);
            }

            int nextCode = encodeState(nxt);

            if (distArr[nextCode] == -1) {
                distArr[nextCode] = distArr[code] + 1;
                q[rear++] = nextCode;
            }
        }
    }
}

int main() {
    buildBFS();

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a[8];

        for (int j = 0; j < 8; j++) {
            scanf("%d", &a[j]);
        }

        int code = encodeState(a);
        printf("%d\n", distArr[code]);
    }

    return 0;
}