#include <stdio.h>

int main() {
    int secret = 42;
    int input = 0;
    int array[3] = {1, 2, 3};

    printf("请输入一个数字: ");
    scanf("%d", &input);

    // 故意制造一个越界访问
    printf("数组第 10 个元素的值是: %d\n", array[10]);

    if (input == secret) {
        printf("恭喜你，猜对了隐藏密码！\n");
    } else {
        printf("再接再厉。\n");
    }

    return 0;
}

