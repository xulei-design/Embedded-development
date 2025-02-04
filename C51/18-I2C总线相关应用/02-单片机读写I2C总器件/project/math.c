#include <stdio.h>

// 交换两个元素的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 将数组根据基准值进行分区
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准值
    int i = (low - 1); // 定义分区的边界

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// 快速排序算法
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// 测试示例
int main() {
    int my_array[] = {54, 26, 93, 17, 77, 31, 44, 55, 20};
    int arr_size = sizeof(my_array) / sizeof(my_array[0]);

    printf("原始数组: ");
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");

    quicksort(my_array, 0, arr_size - 1);

    printf("排序后数组: ");
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");

    return 0;
}