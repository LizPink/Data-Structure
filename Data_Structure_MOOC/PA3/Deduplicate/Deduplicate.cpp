#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

// 最大数据量 6 * 10^5
const int MAXN = 600005;
// 哈希表大小，选择一个大于 2 * MAXN 的质数以减少冲突
const int HASH_SIZE = 1300021; 

// 静态链表节点结构体
struct Node {
    char str[42]; // 字符串长度不超过40
    int state;    // 1: 出现过1次, 2: 已输出过重复
    int next;     // 冲突链表的下一个节点索引
} nodes[MAXN];

int node_cnt = 0;       // 当前分配的节点数量
int head[HASH_SIZE];    // 哈希桶头部索引

// BKDR Hash 算法（一种高效的字符串哈希函数）
unsigned int get_hash(const char* s) {
    unsigned int seed = 31; // 也可以用 131, 1313 等
    unsigned int hash_val = 0;
    while (*s) {
        hash_val = hash_val * seed + (*s - 'a' + 1);
        s++;
    }
    return hash_val % HASH_SIZE;
}

// 插入并检查字符串状态
void insert_and_check(const char* s) {
    unsigned int h = get_hash(s);
    
    // 在对应的哈希桶中查找是否已存在该字符串
    for (int i = head[h]; i != -1; i = nodes[i].next) {
        if (strcmp(nodes[i].str, s) == 0) {
            // 如果是第二次出现（第一次发生重复）
            if (nodes[i].state == 1) {
                printf("%s\n", s); // 立即按顺序输出
                nodes[i].state = 2; // 标记为已输出
            }
            return;
        }
    }
    
    // 如果没找到，说明是新字符串，插入到哈希表中
    strcpy(nodes[node_cnt].str, s);
    nodes[node_cnt].state = 1;
    nodes[node_cnt].next = head[h];
    head[h] = node_cnt;
    node_cnt++;
}

int main() {
    // 初始化哈希桶，-1 表示空
    memset(head, -1, sizeof(head));
    
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    char s[45];
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        insert_and_check(s);
    }
    
    return 0;
}