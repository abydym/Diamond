#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PROCESS 5
#define MAX_RESOURCE 3


typedef struct {
    int available[MAX_RESOURCE];
    int max[MAX_PROCESS][MAX_RESOURCE];
    int allocation[MAX_PROCESS][MAX_RESOURCE];
    int need[MAX_PROCESS][MAX_RESOURCE];
} BankerData;

// 初始化数据结构
void initialize(BankerData *data) {
    // 计算need矩阵
    for (int i = 0; i < MAX_PROCESS; i++) {
        for (int j = 0; j < MAX_RESOURCE; j++) {
            data->need[i][j] = data->max[i][j] - data->allocation[i][j];
        }
    }
}

// 安全性检查算法
bool is_safe(BankerData *data, int *safe_sequence) {
    int work[MAX_RESOURCE];
    bool finish[MAX_PROCESS] = {false};
    int count = 0;

    // 初始化工作向量
    memcpy(work, data->available, sizeof(int) * MAX_RESOURCE);

    // 寻找可完成的进程
    while (count < MAX_PROCESS) {
        bool found = false;
        
        for (int i = 0; i < MAX_PROCESS; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                
                // 检查资源是否满足需求
                for (int j = 0; j < MAX_RESOURCE; j++) {
                    if (data->need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    // 模拟资源分配
                    for (int j = 0; j < MAX_RESOURCE; j++) {
                        work[j] += data->allocation[i][j];
                    }
                    
                    safe_sequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) break; // 无进程可分配
    }

    return (count == MAX_PROCESS);
}

// 资源请求处理
int request_resources(BankerData *data, int pid, int request[]) {
    // 步骤1：检查请求是否超过需求
    for (int i = 0; i < MAX_RESOURCE; i++) {
        if (request[i] > data->need[pid][i]) {
            return -1; // 超过最大需求
        }
    }

    // 检查请求是否超过可用资源
    for (int i = 0; i < MAX_RESOURCE; i++) {
        if (request[i] > data->available[i]) {
            return -2; // 资源不足
        }
    }

    // 尝试分配
    BankerData temp = *data;
    for (int i = 0; i < MAX_RESOURCE; i++) {
        temp.available[i] -= request[i];
        temp.allocation[pid][i] += request[i];
        temp.need[pid][i] -= request[i];
    }

    // 检查分配后是否安全
    int sequence[MAX_PROCESS];
    if (is_safe(&temp, sequence)) {
        *data = temp; // 应用分配
        return 1;     // 分配成功
    }
    return 0;         // 分配导致不安全状态
}

// Python接口封装（重要！！！）
// ================================
#ifdef __cplusplus
extern "C" {
#endif

// 封装后的安全检查函数
// 参数格式：
// - available: 1D数组[MAX_RESOURCE]
// - max:       2D数组[MAX_PROCESS][MAX_RESOURCE]
// - allocation:2D数组[MAX_PROCESS][MAX_RESOURCE]
// 返回值：安全状态（1=安全，0=不安全）
int c_is_safe(int available[], int max[], int allocation[]) {
    BankerData data;
    
    // 初始化数据结构
    memcpy(data.available, available, sizeof(int) * MAX_RESOURCE);
    memcpy(data.max, max, sizeof(int) * MAX_PROCESS * MAX_RESOURCE);
    memcpy(data.allocation, allocation, sizeof(int) * MAX_PROCESS * MAX_RESOURCE);
    
    initialize(&data);
    
    int sequence[MAX_PROCESS];
    return is_safe(&data, sequence) ? 1 : 0;
}

// 封装资源请求函数
// 参数：
// - request: 1D数组[MAX_RESOURCE]
// 返回值：
//  1 = 分配成功
//  0 = 导致不安全状态
// -1 = 超过最大需求
// -2 = 资源不足
int c_request_resources(int available[], int max[], int allocation[], 
                       int pid, int request[]) {
    BankerData data;
    
    // 初始化数据结构
    memcpy(data.available, available, sizeof(int) * MAX_RESOURCE);
    memcpy(data.max, max, sizeof(int) * MAX_PROCESS * MAX_RESOURCE);
    memcpy(data.allocation, allocation, sizeof(int) * MAX_PROCESS * MAX_RESOURCE);
    initialize(&data);
    
    return request_resources(&data, pid, request);
}

#ifdef __cplusplus
}
#endif
