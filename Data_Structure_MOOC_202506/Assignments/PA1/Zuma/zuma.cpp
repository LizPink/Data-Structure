#include <iostream>

const int MAX_INITIAL_LENGTH = 10000;
const int MAX_OPERATIONS = 10000;
const int MAX_NODES = MAX_INITIAL_LENGTH + MAX_OPERATIONS + 5;
const int OUTPUT_BUFFER_SIZE = 1 << 20;

struct Node {
    int left;
    int right;
    int size;
    unsigned int priority;
    char value;
};

Node tree[MAX_NODES];
int nodeCount = 0;
int root = 0;

char outputBuffer[OUTPUT_BUFFER_SIZE];
int outputPosition = 0;

unsigned int randomSeed = 123456789u;

unsigned int nextPriority() {
    randomSeed ^= randomSeed << 13;
    randomSeed ^= randomSeed >> 17;
    randomSeed ^= randomSeed << 5;
    return randomSeed;
}

int getSize(int node) {
    if (node == 0) {
        return 0;
    }
    return tree[node].size;
}

void update(int node) {
    if (node != 0) {
        tree[node].size = getSize(tree[node].left) + getSize(tree[node].right) + 1;
    }
}

int createNode(char value) {
    ++nodeCount;
    tree[nodeCount].left = 0;
    tree[nodeCount].right = 0;
    tree[nodeCount].size = 1;
    tree[nodeCount].priority = nextPriority();
    tree[nodeCount].value = value;
    return nodeCount;
}

void split(int node, int leftSize, int& leftRoot, int& rightRoot) {
    if (node == 0) {
        leftRoot = 0;
        rightRoot = 0;
        return;
    }

    int currentLeftSize = getSize(tree[node].left);

    if (leftSize <= currentLeftSize) {
        split(tree[node].left, leftSize, leftRoot, tree[node].left);
        rightRoot = node;
        update(rightRoot);
    } else {
        split(tree[node].right, leftSize - currentLeftSize - 1, tree[node].right, rightRoot);
        leftRoot = node;
        update(leftRoot);
    }
}

int merge(int leftRoot, int rightRoot) {
    if (leftRoot == 0) {
        return rightRoot;
    }

    if (rightRoot == 0) {
        return leftRoot;
    }

    if (tree[leftRoot].priority < tree[rightRoot].priority) {
        tree[leftRoot].right = merge(tree[leftRoot].right, rightRoot);
        update(leftRoot);
        return leftRoot;
    } else {
        tree[rightRoot].left = merge(leftRoot, tree[rightRoot].left);
        update(rightRoot);
        return rightRoot;
    }
}

char getCharAt(int node, int rank) {
    int leftSize = getSize(tree[node].left);

    if (rank < leftSize) {
        return getCharAt(tree[node].left, rank);
    }

    if (rank == leftSize) {
        return tree[node].value;
    }

    return getCharAt(tree[node].right, rank - leftSize - 1);
}

void insertAt(int position, char value) {
    int leftRoot = 0;
    int rightRoot = 0;

    split(root, position, leftRoot, rightRoot);

    int newNode = createNode(value);

    root = merge(merge(leftRoot, newNode), rightRoot);
}

void eraseRange(int left, int right) {
    int partA = 0;
    int partB = 0;
    int partC = 0;

    split(root, left, partA, partB);
    split(partB, right - left, partB, partC);

    root = merge(partA, partC);
}

void eliminateAround(int position) {
    while (getSize(root) > 0 && position >= 0 && position < getSize(root)) {
        char color = getCharAt(root, position);

        int left = position;
        int right = position + 1;

        while (left > 0 && getCharAt(root, left - 1) == color) {
            --left;
        }

        int currentSize = getSize(root);

        while (right < currentSize && getCharAt(root, right) == color) {
            ++right;
        }

        if (right - left < 3) {
            break;
        }

        eraseRange(left, right);

        currentSize = getSize(root);

        if (currentSize == 0) {
            break;
        }

        if (left < currentSize) {
            position = left;
        } else {
            position = currentSize - 1;
        }
    }
}

void outputChar(char ch) {
    if (outputPosition >= OUTPUT_BUFFER_SIZE) {
        std::cout.write(outputBuffer, outputPosition);
        outputPosition = 0;
    }

    outputBuffer[outputPosition++] = ch;
}

void flushOutput() {
    if (outputPosition > 0) {
        std::cout.write(outputBuffer, outputPosition);
        outputPosition = 0;
    }
}

void outputTree(int node) {
    if (node == 0) {
        return;
    }

    outputTree(tree[node].left);
    outputChar(tree[node].value);
    outputTree(tree[node].right);
}

void outputSequence() {
    if (getSize(root) == 0) {
        outputChar('-');
        outputChar('\n');
        return;
    }

    outputTree(root);
    outputChar('\n');
}

int getLength(const char str[]) {
    int length = 0;

    while (str[length] != '\0' && str[length] != '\n' && str[length] != '\r') {
        ++length;
    }

    return length;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char initial[MAX_INITIAL_LENGTH + 5];

    std::cin.getline(initial, MAX_INITIAL_LENGTH + 5);

    int initialLength = getLength(initial);

    for (int i = 0; i < initialLength; ++i) {
        root = merge(root, createNode(initial[i]));
    }

    int operationCount = 0;
    std::cin >> operationCount;

    for (int i = 0; i < operationCount; ++i) {
        int position = 0;
        char color = '\0';

        std::cin >> position >> color;

        insertAt(position, color);
        eliminateAround(position);
        outputSequence();
    }

    flushOutput();

    return 0;
}