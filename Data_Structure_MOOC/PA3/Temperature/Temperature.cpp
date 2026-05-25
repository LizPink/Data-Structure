#include "temperature.h"

struct Station {
    int x;
    int y;
    int temp;
};

struct SegNode {
    int l;
    int r;
    int minX;
    int maxX;
    int start;
    int len;
};

Station* stations;
Station* tempStations;
SegNode* tree;

int* poolY;
long long* poolSum;
int poolUsed = 0;

bool lessByX(const Station& a, const Station& b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.temp < b.temp;
}

void mergeSortByX(int l, int r) {
    if (l >= r) return;

    int mid = l + (r - l) / 2;
    mergeSortByX(l, mid);
    mergeSortByX(mid + 1, r);

    int i = l;
    int j = mid + 1;
    int k = l;

    while (i <= mid && j <= r) {
        if (lessByX(stations[i], stations[j])) {
            tempStations[k++] = stations[i++];
        } else {
            tempStations[k++] = stations[j++];
        }
    }

    while (i <= mid) {
        tempStations[k++] = stations[i++];
    }

    while (j <= r) {
        tempStations[k++] = stations[j++];
    }

    for (int p = l; p <= r; p++) {
        stations[p] = tempStations[p];
    }
}

long long getSingleTemp(int nodeIndex, int offset) {
    int pos = tree[nodeIndex].start + offset;
    if (offset == 0) return poolSum[pos];
    return poolSum[pos] - poolSum[pos - 1];
}

void build(int nodeIndex, int l, int r) {
    tree[nodeIndex].l = l;
    tree[nodeIndex].r = r;
    tree[nodeIndex].minX = stations[l].x;
    tree[nodeIndex].maxX = stations[r].x;
    tree[nodeIndex].len = r - l + 1;
    tree[nodeIndex].start = poolUsed;
    poolUsed += tree[nodeIndex].len;

    if (l == r) {
        int start = tree[nodeIndex].start;
        poolY[start] = stations[l].y;
        poolSum[start] = stations[l].temp;
        return;
    }

    int mid = l + (r - l) / 2;
    int left = nodeIndex * 2;
    int right = nodeIndex * 2 + 1;

    build(left, l, mid);
    build(right, mid + 1, r);

    int i = 0;
    int j = 0;
    int k = 0;

    int leftStart = tree[left].start;
    int rightStart = tree[right].start;
    int leftLen = tree[left].len;
    int rightLen = tree[right].len;
    int curStart = tree[nodeIndex].start;

    long long acc = 0;

    while (i < leftLen || j < rightLen) {
        int chosenY;
        long long chosenTemp;

        if (j >= rightLen || (i < leftLen && poolY[leftStart + i] <= poolY[rightStart + j])) {
            chosenY = poolY[leftStart + i];
            chosenTemp = getSingleTemp(left, i);
            i++;
        } else {
            chosenY = poolY[rightStart + j];
            chosenTemp = getSingleTemp(right, j);
            j++;
        }

        poolY[curStart + k] = chosenY;
        acc += chosenTemp;
        poolSum[curStart + k] = acc;
        k++;
    }
}

int lowerBoundY(int start, int len, int value) {
    int l = 0;
    int r = len;

    while (l < r) {
        int mid = l + (r - l) / 2;
        if (poolY[start + mid] < value) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}

int upperBoundY(int start, int len, int value) {
    int l = 0;
    int r = len;

    while (l < r) {
        int mid = l + (r - l) / 2;
        if (poolY[start + mid] <= value) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}

void queryYInNode(int nodeIndex, int y1, int y2, long long& sum, int& count) {
    int start = tree[nodeIndex].start;
    int len = tree[nodeIndex].len;

    int leftPos = lowerBoundY(start, len, y1);
    int rightPos = upperBoundY(start, len, y2);

    if (leftPos >= rightPos) return;

    count += rightPos - leftPos;

    long long partSum = poolSum[start + rightPos - 1];
    if (leftPos > 0) {
        partSum -= poolSum[start + leftPos - 1];
    }

    sum += partSum;
}

void query(int nodeIndex, int x1, int y1, int x2, int y2, long long& sum, int& count) {
    if (tree[nodeIndex].maxX < x1 || tree[nodeIndex].minX > x2) {
        return;
    }

    if (x1 <= tree[nodeIndex].minX && tree[nodeIndex].maxX <= x2) {
        queryYInNode(nodeIndex, y1, y2, sum, count);
        return;
    }

    if (tree[nodeIndex].l == tree[nodeIndex].r) {
        int idx = tree[nodeIndex].l;
        if (x1 <= stations[idx].x && stations[idx].x <= x2 &&
            y1 <= stations[idx].y && stations[idx].y <= y2) {
            sum += stations[idx].temp;
            count++;
        }
        return;
    }

    query(nodeIndex * 2, x1, y1, x2, y2, sum, count);
    query(nodeIndex * 2 + 1, x1, y1, x2, y2, sum, count);
}

int main() {
    int n = GetNumOfStation();

    if (n <= 0) {
        int x1, y1, x2, y2;
        while (GetQuery(&x1, &y1, &x2, &y2)) {
            Response(0);
        }
        return 0;
    }

    stations = new Station[n];
    tempStations = new Station[n];

    for (int i = 0; i < n; i++) {
        GetStationInfo(i, &stations[i].x, &stations[i].y, &stations[i].temp);
    }

    mergeSortByX(0, n - 1);

    int levels = 0;
    int p = 1;
    while (p < n) {
        p <<= 1;
        levels++;
    }

    int poolCapacity = n * (levels + 3) + 10;

    tree = new SegNode[4 * n + 10];
    poolY = new int[poolCapacity];
    poolSum = new long long[poolCapacity];

    build(1, 0, n - 1);

    int x1, y1, x2, y2;

    while (GetQuery(&x1, &y1, &x2, &y2)) {
        long long sum = 0;
        int count = 0;

        query(1, x1, y1, x2, y2, sum, count);

        if (count == 0) {
            Response(0);
        } else {
            Response((int)(sum / count));
        }
    }

    delete[] stations;
    delete[] tempStations;
    delete[] tree;
    delete[] poolY;
    delete[] poolSum;

    return 0;
}