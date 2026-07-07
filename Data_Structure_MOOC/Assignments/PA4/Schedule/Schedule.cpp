#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

// 任务结构体定义
struct Task {
    unsigned long long prio; // 优先级数，使用无符号长整型防止乘2后溢出
    uint64_t name_val;       // 字符串压缩后的64位整数，用于高效比较
    char name_str[9];        // 原始字符串，用于最终输出

    // 比较运算符重载：优先级数小的优先；若相等，则任务名ASCII码小的优先
    bool operator<(const Task& other) const {
        if (prio != other.prio) {
            return prio < other.prio;
        }
        return name_val < other.name_val;
    }
};

const int MAXN = 4000005; // 最大任务数量限制
Task heap[MAXN];          // 静态堆数组（从索引 1 开始存储）
int heap_size = 0;        // 当前堆的大小

// 将长度不超过8的字符串压缩为单条64位无符号整数
uint64_t pack_string(const char* s) {
    uint64_t val = 0;
    bool ended = false;
    for (int i = 0; i < 8; i++) {
        val <<= 8;
        if (!ended && s[i] != '\0') {
            val |= (unsigned char)s[i];
        } else {
            ended = true; // 遇到结束符后，后续高位均补0
        }
    }
    return val;
}

// 堆的下滤调整函数（保持最小堆性质）
void percolateDown(int hole) {
    Task target = heap[hole];
    int child;
    for (; hole * 2 <= heap_size; hole = child) {
        child = hole * 2;
        // 选择左右孩子中较小的一个
        if (child != heap_size && heap[child + 1] < heap[child]) {
            child++;
        }
        // 如果孩子节点比目标节点小，则上移孩子节点
        if (heap[child] < target) {
            heap[hole] = heap[child];
        } else {
            break;
        }
    }
    heap[hole] = target; // 找到最终安置位置
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // 1. 读入数据
    for (int i = 1; i <= n; i++) {
        scanf("%llu %s", &heap[i].prio, heap[i].name_str);
        heap[i].name_val = pack_string(heap[i].name_str);
    }
    heap_size = n;

    // 2. 自底向上高效建堆：O(n)
    for (int i = heap_size / 2; i >= 1; i--) {
        percolateDown(i);
    }

    // 3. 执行调度预测
    for (int i = 0; i < m; i++) {
        if (heap_size == 0) break; // 若任务提前处理完毕，退出循环

        // 输出当前最高优先级任务
        printf("%s\n", heap[1].name_str);

        // 优先级数加倍
        heap[1].prio *= 2;

        if (heap[1].prio >= 4294967296ULL) { // 2^32 = 4294967296
            // 真正退出：使用堆尾元素覆盖堆顶，并缩减堆大小
            heap[1] = heap[heap_size--];
        }
        
        // 重新调整堆顶元素的位置
        if (heap_size > 0) {
            percolateDown(1);
        }
    }

    return 0;
}