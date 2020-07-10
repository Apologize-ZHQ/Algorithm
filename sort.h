//
// Created by 郑红强 on 2020/7/8.
//

#ifndef SORT_SORT_H
#define SORT_SORT_H
#include <string.h>
#include <stdlib.h>

/*
 * 直接插入排序 -稳定的排序算法
 *
 * 思想：
 *      1. 初始化：将数组的nums[0]定义为已排序数组，nums[1]到数组结束为未排序数组
 *      2. 外循环：遍历未排序数组，将当前num[i]记为cur_number，方便内循环比较
 *      3. 内循环：从nums[i-1]遍历已排序数组，nums[j] > cur_number,将已排序数组向后移一位。此时最后一位排序数组被覆盖
 *      4. 找到cur_number的位置，插入到数组中。
 * 算法是时间复杂度：
 *      O(n^2)
 * */
void insert_sort(int nums[], int size);

void insert_sort(int nums[], int size) {
    int i,j,cur_number;
    for (i = 1; i < size; ++i) {
        cur_number = nums[i];
        for ( j = i-1; j >= 0 && nums[j] > cur_number; --j) {
            nums[j+1] =nums[j];
        }
        nums[j+1] = cur_number;
    }
}

/*
 * 希尔排序 -不稳定的排序算法,相同值的可能分配在不同的组，导致顺序不一定
 * 思想：
 *      把记录按步长 gap 分组，对每组记录采用直接插入排序方法进行排序
 * 算法时间复杂度
 *      平均：O(n log n) 最坏：O(n^(3/2))
 * 直接插入排序和希尔排序的比较
 *      直接插入排序是稳定的；而希尔排序是不稳定的。
 *      直接插入排序更适合于原始记录基本有序的集合。
 *      希尔排序的比较次数和移动次数都要比直接插入排序少，当N越大时，效果越明显。
 *      在希尔排序中，增量序列gap的取法必须满足：最后一个步长必须是 1 。
 *      直接插入排序也适用于链式存储结构；希尔排序不适用于链式结构。
 * */
void shell_sort(int nums[], int size);

void shell_sort(int nums[], int size) {
    int i, j, gap, cur_number;
    for (gap = size/2; gap > 0 ; gap /= 2) {
        for ( i = gap; i < size; ++i) {
            cur_number = nums[i];
            for ( j = i-gap; j >=0 && nums[j] > cur_number; j -= gap) {
                nums[j+gap] =nums[j];
            }
            nums[j+gap] = cur_number;
        }
    }
}

/*冒泡排序 -稳定
 *
 * 思想：
 *      1. 外层循环，控制排序的个数，最大为数组长度-1 。
 *      2. 内层循环，两两比较 进行交换。比较的个数为：数组长度-1 - 已排数组大小。
 *      3. 设置flag位，flag=1 表示数组还未完全排序，flag = 0 表示数组已经是排序的数组，可以提前结束。
 * 算法时间复杂度
 *      平均O(n^2).
 *
 * */
void bubble_sort(int nums[], int size);

void bubble_sort(int nums[], int size){
    int i,j;
    int temp;
    int flag = 1;
    for (i = 0; i < size-1 && flag; ++i) {
        flag = 0;
        for (j = 0;  j < size-1-i ; ++j) {
            if (nums[j] > nums[j+1]) {
                temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
                flag = 1;
            }
        }
    }
}

/* 快速排序 -分治思想，不稳定。
 * 思想：快速对调左右区间，
 * 算法时间复杂度：
 *      平均 O(n log n) 最坏O(n^2) 分治思想决定的
 * */
void quick_sort(int nums[], int begin, int end);
int partition(int nums[], int begin, int end);

void quick_sort(int nums[], int begin, int end) {
    if (begin >= end)
        return;

    int pivot = partition(nums,begin,end);

    quick_sort(nums, begin, pivot-1);
    quick_sort(nums ,pivot+1, end);
}

int partition(int nums[], int begin, int end) {
    int pivot = end;
    int count = begin;
    int temp;
    for (int i = begin; i < end; ++i) {
        if (nums[i] < nums[pivot]) {
            temp = nums[count];
            nums[count] = nums[i];
            nums[i] = temp;

            count++;
        }
    }

    temp = nums[count];
    nums[count] = nums[pivot];
    nums[pivot] = temp;

    return count;
}

/*
 * 归并排序 - 稳定的排序
 *
 * 思想：
 *
 * 算法时间复杂度：
 *      平均O(n log n) 最好最坏都是这个。
 * */
void merge_sort(int nums[], int begin, int end);
void merge(int nums[], int begin, int mid, int end);

void merge_sort(int nums[], int begin, int end) {
    if (begin >= end)
        return;
    int mid = (begin + end) >> 1;
    merge_sort(nums,begin,mid);
    merge_sort(nums,mid+1,end);

    merge(nums, begin, mid, end);
}

void merge(int nums[], int begin, int mid, int end) {
    int temp_length = end - begin + 1;
    int temp[temp_length];
    int i = begin;
    int j = mid+1;
    int k=0;
    while (i <= mid && j <= end) {
        temp[k++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
    }

    while (i <= mid) temp[k++] =nums[i++];

    while (j <= end) temp[k++] = nums[j++];

    for ( k = 0;  k < temp_length; ++k) {
        nums[begin + k ] = temp[k];
    }
}

/*
 * 选择排序
 * 思想： 记录无需数组中的最小值的index，将其添加到有序数组中
 *
 * 算法时间复杂度：
 *      平均：O(n^2)
 * */
void select_sort(int nums[], int size);

void select_sort(int nums[], int size) {
    int i,j, mindex;
    for (i = 0; i < size; ++i) {
        mindex =i;
        for (j = i; j < size; ++j) {
            if (nums[j] < nums[mindex]) {
                mindex = j;
            }
        }
        int temp = nums[mindex];
        nums[mindex] = nums[i];
        nums[i] = temp;
    }
}

/*
 * 堆排序
 * */
void maxHeap (int nums[], int size, int index);
void swap(int *nums, int i, int j);
void build_heap (int nums[], int size);
void  heap_sort(int nums[], int size);

void maxHeap (int nums[], int size, int index) {
    if (index >= size)
        return;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int maxindex = index;

    if (left < size && nums[left] > nums[maxindex])
        maxindex = left;

    if (right < size && nums[right] > nums[maxindex])
        maxindex = right;

    if (maxindex != index) {
        swap(nums,maxindex,index);
        maxHeap(nums,size,maxindex);
    }
}

void swap(int nums[], int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

void build_heap (int nums[], int size)
{
    int last_node = size - 1;
    int parent = (last_node - 1) >> 1;
    for (int i = parent; i >= 0; --i) {
        maxHeap(nums,size,i);
    }
}

void  heap_sort(int nums[], int size) {
    build_heap(nums, size);

    for (int i = size-1; i >= 0 ; --i) {
        swap(nums,0,i);
        maxHeap(nums,i,0);

    }
}

/*
 * 基数排序
 * */
int getMaxNumber(int *nums, int size);
int getMaxDigit(int number);
int getKthNumber (int number,int k);
void radix_sort(int *nums,int size);

int getMaxNumber(int *nums, int size) {
    int max_number = nums[0];
    for (int i = 0; i < size; ++i)
    {
        if (max_number < nums[i])
            max_number = nums[i];
    }
    return max_number;
}

int getMaxDigit(int number) {
    int digit = 0 ;

    do{
        ++digit;
        number /= 10;
    }while(number);

    return digit;
}

int getKthNumber (int number,int k) {
    int kth_number = number % 10;
    while(k>=0) {
        kth_number = number % 10;
        number /= 10;
        --k;
    }
    return kth_number;
}

void radix_sort(int *nums,int size) {
    int max_number = getMaxNumber(nums,size);
    int digit = getMaxDigit(max_number);

    int i,j,k;

    int *temp[10];
    int count[10] = {0};

    for (int i = 0; i < 10; ++i)
    {
        temp[i] = (int *) malloc(size * sizeof(int));
        memset(temp[i] , 0 ,size *sizeof(int));
    }

    for (int i = 0; i < digit; ++i)
    {
        memset(count,0,10 * sizeof(int)) ;
        for ( j = 0; j < size; ++j)
        {
            int kth_number = getKthNumber(nums[j],i);
            temp[kth_number][count[kth_number]++] = nums[j];
        }

        int index  = 0;
        for ( j = 0; j < 10; ++j)
        {
            for (k = 0; k < count[j]; ++k)
            {
                nums[index++] = temp[j][k];
            }
        }
    }
}
#endif //SORT_SORT_H
