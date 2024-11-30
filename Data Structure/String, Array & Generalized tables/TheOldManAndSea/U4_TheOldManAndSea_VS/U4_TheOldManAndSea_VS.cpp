#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef struct KMP {
    const char* pattern;
    int* lps;
    int m;
} KMP;

// 初始化KMP算法所需的LPS数组
void KMP_init(KMP* kmp, const char* pat) {
    kmp->pattern = pat;
    kmp->m = strlen(pat);
    kmp->lps = (int*)malloc(kmp->m * sizeof(int));
    int len = 0;
    kmp->lps[0] = 0;
    int i = 1;
    while (i < kmp->m) {
        if (kmp->pattern[i] == kmp->pattern[len]) {
            len++;
            kmp->lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = kmp->lps[len - 1];
            }
            else {
                kmp->lps[i] = 0;
                i++;
            }
        }
    }
}

// 使用KMP算法进行匹配，返回匹配次数
int KMP_search(KMP* kmp, const char* txt) {
    int n = strlen(txt);
    int i = 0;  // txt索引
    int j = 0;  // pattern索引
    int count = 0;

    while (i < n) {
        if (kmp->pattern[j] == txt[i]) {
            i++;
            j++;
        }
        if (j == kmp->m) {
            count++;
            j = kmp->lps[j - 1];
        }
        else if (i < n && kmp->pattern[j] != txt[i]) {
            if (j != 0) {
                j = kmp->lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
    return count;
}

void KMP_free(KMP* kmp) {
    free(kmp->lps);
}

// 读取文件直到句号
int countPatternInText(const char* filePath, const char* pattern) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        cerr << "Unable to open file!" << endl;
        return -1;
    }

    KMP kmp;
    KMP_init(&kmp, pattern);
    int totalCount = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        int lineLength = strlen(line);
        int index = 0;

        // 处理行中的每个字符，直到句号
        while (index < lineLength) {
            char* sentenceEnd = strchr(line + index, '。');
            if (sentenceEnd == NULL) {
                // 如果没有找到句号，读取到末尾
                sentenceEnd = line + lineLength;
            }

            // 动态分配缓冲区大小
            int bufferSize = sentenceEnd - (line + index) + 1;
            char* buffer = (char*)malloc(bufferSize * sizeof(char));

            strncpy(buffer, line + index, bufferSize - 1);
            buffer[bufferSize - 1] = '\0'; // 确保字符串终止

            // 计算当前句子中"马林鱼"的出现次数
            totalCount += KMP_search(&kmp, buffer);

            // 释放缓冲区
            free(buffer);

            index = sentenceEnd - line + 1; // 跳过句号
        }
    }

    fclose(file);
    KMP_free(&kmp);
    return totalCount;
}

int main() {
    const char* filePath = "TheOldManAndSea.txt";
    const char* pattern = "马林鱼";

    int count = countPatternInText(filePath, pattern);
    if (count != -1) {
        cout << "The word '马林鱼' appears " << count << " times in the text." << endl;
    }

    return 0;
}
