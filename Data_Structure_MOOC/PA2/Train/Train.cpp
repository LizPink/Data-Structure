#include <stdio.h>

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
            length = (int)fread(buffer, 1, BUFFER_SIZE, stdin);
            position = 0;

            if (length == 0) {
                return EOF;
            }
        }

        return buffer[position++];
    }

    bool readInt(int& value) {
        int ch = readChar();

        while (ch != EOF && (ch < '0' || ch > '9')) {
            ch = readChar();
        }

        if (ch == EOF) {
            return false;
        }

        value = 0;

        while (ch >= '0' && ch <= '9') {
            value = value * 10 + ch - '0';
            ch = readChar();
        }

        return true;
    }
};

class FastOutput {
private:
    static const int BUFFER_SIZE = 1 << 20;
    char buffer[BUFFER_SIZE];
    int position;

public:
    FastOutput() {
        position = 0;
    }

    ~FastOutput() {
        flush();
    }

    void writeChar(char ch) {
        if (position >= BUFFER_SIZE) {
            flush();
        }

        buffer[position++] = ch;
    }

    void writeString(const char str[]) {
        for (int i = 0; str[i] != '\0'; ++i) {
            writeChar(str[i]);
        }
    }

    void flush() {
        if (position > 0) {
            fwrite(buffer, 1, position, stdout);
            position = 0;
        }
    }
};

int main() {
    FastInput input;

    int n = 0;
    int m = 0;

    input.readInt(n);
    input.readInt(m);

    int* stationStack = new int[n + 5];

    /*
        operation[i] = 1 表示 push
        operation[i] = 0 表示 pop
        最多 n 次 push 和 n 次 pop，所以最多 2n 个操作。
    */
    char* operation = new char[2 * n + 5];

    int stackSize = 0;
    int nextTrain = 1;
    int operationCount = 0;

    bool feasible = true;

    for (int i = 0; i < n; ++i) {
        int target = 0;
        input.readInt(target);

        /*
            如果当前栈顶不是 target，就继续把 A 端车厢压入 S，
            直到栈顶变成 target。
        */
        while (feasible && (stackSize == 0 || stationStack[stackSize - 1] != target)) {
            if (nextTrain > n) {
                feasible = false;
                break;
            }

            if (stackSize >= m) {
                feasible = false;
                break;
            }

            stationStack[stackSize++] = nextTrain;
            ++nextTrain;

            operation[operationCount++] = 1;
        }

        /*
            栈顶是 target，则 pop 出站。
        */
        if (feasible && stackSize > 0 && stationStack[stackSize - 1] == target) {
            --stackSize;
            operation[operationCount++] = 0;
        } else {
            feasible = false;
        }

        if (!feasible) {
            break;
        }
    }

    FastOutput output;

    if (!feasible) {
        output.writeString("No\n");
    } else {
        for (int i = 0; i < operationCount; ++i) {
            if (operation[i] == 1) {
                output.writeString("push\n");
            } else {
                output.writeString("pop\n");
            }
        }
    }

    delete[] stationStack;
    delete[] operation;

    return 0;
}