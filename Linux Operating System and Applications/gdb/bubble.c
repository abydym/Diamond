#include "bubble.h"

void bubble(int* a, int n) {
    int i, j, t;
    for(i = 1; i < n; i++) {
        for(j = 0; j < n - i; j++) {
            if(a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}
// 检查这里后面是不是跟着一个 main 函数？如果有，请删掉。
