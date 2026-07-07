#include <cstdio>

struct Point {
    int x;
    int y;
};

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

void mergePointsByX(Point points[], Point temp[], int left, int middle, int right) {
    int i = left;
    int j = middle;
    int k = left;

    while (i < middle && j < right) {
        if (points[i].x <= points[j].x) {
            temp[k++] = points[i++];
        } else {
            temp[k++] = points[j++];
        }
    }

    while (i < middle) {
        temp[k++] = points[i++];
    }

    while (j < right) {
        temp[k++] = points[j++];
    }

    for (int p = left; p < right; ++p) {
        points[p] = temp[p];
    }
}

void sortPointsByX(Point points[], Point temp[], int left, int right) {
    if (right - left <= 1) {
        return;
    }

    int middle = left + (right - left) / 2;

    sortPointsByX(points, temp, left, middle);
    sortPointsByX(points, temp, middle, right);
    mergePointsByX(points, temp, left, middle, right);
}

long long countIncreasingPairs(int y[], int temp[], int left, int right) {
    if (right - left <= 1) {
        return 0;
    }

    int middle = left + (right - left) / 2;

    long long answer = 0;

    answer += countIncreasingPairs(y, temp, left, middle);
    answer += countIncreasingPairs(y, temp, middle, right);

    int i = left;
    int j = middle;
    int k = left;

    while (i < middle && j < right) {
        if (y[i] < y[j]) {
            /*
                y[i] 小于右半部分当前的 y[j]。
                因为右半部分已经有序，所以 y[i] 也小于 y[j], y[j+1], ..., y[right-1]。
                这些都能和 y[i] 构成一对可相互照亮的灯塔。
            */
            answer += right - j;
            temp[k++] = y[i++];
        } else {
            temp[k++] = y[j++];
        }
    }

    while (i < middle) {
        temp[k++] = y[i++];
    }

    while (j < right) {
        temp[k++] = y[j++];
    }

    for (int p = left; p < right; ++p) {
        y[p] = temp[p];
    }

    return answer;
}

int main() {
    FastInput input;

    int n = 0;
    input.readInt(n);

    if (n <= 1) {
        int dummyX = 0;
        int dummyY = 0;

        for (int i = 0; i < n; ++i) {
            input.readInt(dummyX);
            input.readInt(dummyY);
        }

        std::printf("0\n");
        return 0;
    }

    Point* points = new Point[n];
    Point* tempPoints = new Point[n];

    for (int i = 0; i < n; ++i) {
        input.readInt(points[i].x);
        input.readInt(points[i].y);
    }

    sortPointsByX(points, tempPoints, 0, n);

    int* y = new int[n];

    for (int i = 0; i < n; ++i) {
        y[i] = points[i].y;
    }

    delete[] points;
    delete[] tempPoints;

    int* tempY = new int[n];

    long long answer = countIncreasingPairs(y, tempY, 0, n);

    std::printf("%lld\n", answer);

    delete[] y;
    delete[] tempY;

    return 0;
}