#include <stdio.h>
#include "bubble.h"

#define COUNT 10
int main(void) {
    int i;
    int a[COUNT] = {3, 5, 4, 8, 9, 6, 2, 1, 7, 0};
    bubble(a, COUNT);
    for(i = 0; i < COUNT; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
