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

class FastOutput {
private:
    static const int BUFFER_SIZE = 1 << 20;
    char buffer[BUFFER_SIZE];
    int position;
    bool firstNumber;

public:
    FastOutput() {
        position = 0;
        firstNumber = true;
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

    void writeInt(int value) {
        if (!firstNumber) {
            writeChar(' ');
        }

        firstNumber = false;

        if (value == 0) {
            writeChar('0');
            return;
        }

        char digits[20];
        int length = 0;

        while (value > 0) {
            digits[length++] = (char)('0' + value % 10);
            value /= 10;
        }

        for (int i = length - 1; i >= 0; --i) {
            writeChar(digits[i]);
        }
    }

    void writeEndLine() {
        writeChar('\n');
    }

    void flush() {
        if (position > 0) {
            fwrite(buffer, 1, position, stdout);
            position = 0;
        }
    }
};

struct Frame {
    int preLeft;
    int postLeft;
    int length;
    int state;
};

/*
    state = 0: 还未处理左子树
    state = 1: 左子树已处理，准备输出根并处理右子树
    state = 2: 右子树已处理，可以弹栈
*/

void pushFrame(Frame stackFrames[], int& top, int preLeft, int postLeft, int length) {
    stackFrames[top].preLeft = preLeft;
    stackFrames[top].postLeft = postLeft;
    stackFrames[top].length = length;
    stackFrames[top].state = 0;
    ++top;
}

int main() {
    FastInput input;
    FastOutput output;

    int n = input.readInt();

    int* preorder = new int[n];
    int* postPosition = new int[n + 1];

    for (int i = 0; i < n; ++i) {
        preorder[i] = input.readInt();
    }

    for (int i = 0; i < n; ++i) {
        int value = input.readInt();
        postPosition[value] = i;
    }

    Frame* stackFrames = new Frame[n + 5];
    int top = 0;

    pushFrame(stackFrames, top, 0, 0, n);

    while (top > 0) {
        Frame& current = stackFrames[top - 1];

        if (current.length == 1) {
            output.writeInt(preorder[current.preLeft]);
            --top;
            continue;
        }

        if (current.state == 0) {
            current.state = 1;

            int leftRoot = preorder[current.preLeft + 1];
            int leftLength = postPosition[leftRoot] - current.postLeft + 1;

            pushFrame(
                stackFrames,
                top,
                current.preLeft + 1,
                current.postLeft,
                leftLength
            );
        } else if (current.state == 1) {
            current.state = 2;

            output.writeInt(preorder[current.preLeft]);

            int leftRoot = preorder[current.preLeft + 1];
            int leftLength = postPosition[leftRoot] - current.postLeft + 1;
            int rightLength = current.length - leftLength - 1;

            pushFrame(
                stackFrames,
                top,
                current.preLeft + 1 + leftLength,
                current.postLeft + leftLength,
                rightLength
            );
        } else {
            --top;
        }
    }

    output.writeEndLine();
    output.flush();

    delete[] preorder;
    delete[] postPosition;
    delete[] stackFrames;

    return 0;
}