#include <cstdio>

const int INPUT_BUFFER_SIZE = 1 << 20;
const int OUTPUT_BUFFER_SIZE = 1 << 20;

char inputBuffer[INPUT_BUFFER_SIZE];
int inputPosition = 0;
int inputLength = 0;

char outputBuffer[OUTPUT_BUFFER_SIZE];
int outputPosition = 0;

int readChar() {
    if (inputPosition >= inputLength) {
        inputLength = (int)std::fread(inputBuffer, 1, INPUT_BUFFER_SIZE, stdin);
        inputPosition = 0;

        if (inputLength == 0) {
            return EOF;
        }
    }

    return inputBuffer[inputPosition++];
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

void writeChar(char ch) {
    if (outputPosition >= OUTPUT_BUFFER_SIZE) {
        std::fwrite(outputBuffer, 1, outputPosition, stdout);
        outputPosition = 0;
    }

    outputBuffer[outputPosition++] = ch;
}

void writeInt(int value) {
    if (value == 0) {
        writeChar('0');
        writeChar('\n');
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

    writeChar('\n');
}

void flushOutput() {
    if (outputPosition > 0) {
        std::fwrite(outputBuffer, 1, outputPosition, stdout);
        outputPosition = 0;
    }
}

void merge(int array[], int temp[], int left, int middle, int right) {
    int i = left;
    int j = middle;
    int k = left;

    while (i < middle && j < right) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    while (i < middle) {
        temp[k++] = array[i++];
    }

    while (j < right) {
        temp[k++] = array[j++];
    }

    for (int p = left; p < right; ++p) {
        array[p] = temp[p];
    }
}

void mergeSort(int array[], int temp[], int left, int right) {
    if (right - left <= 1) {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSort(array, temp, left, middle);
    mergeSort(array, temp, middle, right);
    merge(array, temp, left, middle, right);
}

int lowerBound(int array[], int size, int target) {
    int left = 0;
    int right = size;

    while (left < right) {
        int middle = left + (right - left) / 2;

        if (array[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

int upperBound(int array[], int size, int target) {
    int left = 0;
    int right = size;

    while (left < right) {
        int middle = left + (right - left) / 2;

        if (array[middle] <= target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

int main() {
    int n = readInt();
    int m = readInt();

    int* points = new int[n];

    for (int i = 0; i < n; ++i) {
        points[i] = readInt();
    }

    if (n > 1) {
        int* temp = new int[n];
        mergeSort(points, temp, 0, n);
        delete[] temp;
    }

    for (int i = 0; i < m; ++i) {
        int a = readInt();
        int b = readInt();

        int left = lowerBound(points, n, a);
        int right = upperBound(points, n, b);

        writeInt(right - left);
    }

    flushOutput();

    delete[] points;

    return 0;
}