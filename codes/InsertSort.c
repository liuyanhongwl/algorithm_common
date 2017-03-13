#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void printfArray(int array[], int length);

void insertSort(int array[], int length);

void recursiveInsertSort(int array[], int length, int cur);

void selectionSort(int array[], int length);

void heapSort(int array[], int length);
void buildHeap(int array[], int length);
void heapAdjust(int array[], int length, int i);

void mergeSort(int array[], int tempArray[], int low, int high);

void bubbleSort(int array[], int length);
void bubbleSort1(int array[], int length);
void bubbleSort2(int array[], int length);

void quickSort(int array[], int low, int high);
void quickSort1(int array[], int low, int high);
void quickSort2(int array[], int low, int high);

int main(int argc, char const *argv[])
{
	//初始化一个随机数组
	srand(time(0));
	const int length = 10;
	int array[10];
	for (int i = 0; i < length; ++i)
	{
		array[i] = rand()%100;
	}

	printf("插入排序前:\n");
	printfArray(array, length);

	//插入排序
	// insertSort(array, length);

	//递归式插入排序
	// recursiveInsertSort(array, length, length - 1);

	//选择排序
	// selectionSort(array, length);

	//堆排序
	// heapSort(array, length);

	//归并排序
	// int tempArray[length];
	// mergeSort(array, tempArray, 0, length - 1);

	//冒泡排序
	// bubbleSort(array, length);
	// bubbleSort1(array, length);
	// bubbleSort2(array, length);

	//快速排序
	// quickSort(array, 0, length-1);
	// quickSort1(array, 0, length-1);
	quickSort2(array, 0, length-1);

	printf("排序后：\n");	
	printfArray(array, length);	

	return 0;
}

void printfArray(int array[], int length)
{
	for (int i = 0; i < length; ++i)
	{
		printf("%d,", array[i]);
	}
	printf("\n");
}

//插入排序
void insertSort(int array[],int length)
{
    for (int i = 1; i < length; i++) {
        int temp = array[i];
        int j = i;
        for (; j > 0; j--) {
            if (array[j-1] > temp) {
                array[j] = array[j-1];
            }else{
                break;
            }
        }
        array[j] = temp;
    }
}

//递归式插入排序
void recursiveInsertSort(int array[], int length, int cur)
{
	if (cur < 1)
	{
		return;
	}

	//递归前一个数组
	recursiveInsertSort(array, length, cur-1);

	int value = array[cur];
	int j = cur;
	for (; j > 0; j--)
	{
		if (array[j-1] > value){
			array[j] = array[j-1];
		}else{
			break;
		}
	}
	array[j] = value;
}

//选择排序
void selectionSort(int array[], int length)
{
	for (int i = 0; i < length-1; ++i)
	{
		int min = i;
		for (int j = i+1; j < length; ++j)
		{
			if (array[min] > array[j]){
				min = j;
			}
		}

		if (min != i){
			int temp = array[i];
			array[i] = array[min];
			array[min] = temp;
		}
	}
}

//堆排序 start
//注意：这里的i=（1,2,3...n）
void heapSort(int array[], int length)
{
	buildHeap(array, length);
	for (int i = length; i >= 1; i--)
	{
		//交换第一个元素和最后一个元素，即每次将堆顶元素排到未排好序列的最后
		int temp = array[0];	
		array[0] = array[i-1];
		array[i-1] = temp;
		//重新调整为堆
		heapAdjust(array, i-1, 1); 
	}
}

///调整以i结点为根的树为堆
void heapAdjust(int array[], int length, int i)
{
	int lChild = i*2;
	int rChild = i*2 + 1;
	int maxIndex = i;
	//处理非叶子节点
	if (i <= length/2) 
	{
		if (lChild <= length && array[lChild-1] > array[maxIndex-1])
		{
			maxIndex = lChild;
		}
		if (rChild <= length && array[rChild-1] > array[maxIndex-1])
		{
			maxIndex = rChild;
		}
		if (maxIndex != i)
		{
			int temp = array[maxIndex-1];
			array[maxIndex-1] = array[i-1];
			array[i-1] = temp;
			heapAdjust(array, length, maxIndex);
		}
	}
}

///创建堆
void buildHeap(int array[], int length)
{
	//从最后一个非叶子结点开始，调整为堆
	for (int i = length/2; i >= 1; i--)
	{
		heapAdjust(array, length, i);
	}
}
//堆排序 end

//归并排序
void mergeSort(int array[], int tempArray[], int low, int high)
{
	if (low >= high){
		return;
	}

	//递归前半段、后半段
	int mid = (low + high) / 2;
	mergeSort(array, tempArray, low, mid);
	mergeSort(array, tempArray, mid + 1, high);

	int i = low;
	int j = mid + 1;
	int cur = 0;
	while(i <= mid && j <= high)
	{
		if (array[i] < array[j]){
			tempArray[cur] = array[i++];
		}else{
			tempArray[cur] = array[j++];
		}
		cur++;
	}

	while(i <= mid)
	{
		tempArray[cur++] = array[i++];
	}

	while(j <= high)
	{
		tempArray[cur++] = array[j++];
	}

	for (int i = 0; i < cur; ++i)
	{
		array[i+low] = tempArray[i];
	}
}

//冒泡排序
void bubbleSort(int array[], int length)
{
	for (int i = 0; i < length-1; ++i)
	{
		for (int j = 0; j < length-1-i; ++j)
		{
			if (array[j] > array[j+1])
			{
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

//冒泡排序 改进 加标志位
void bubbleSort1(int array[], int length)
{
	for (int i = length - 1; i > 0;)
	{
		int pos = 0;
		for (int j = 0; j < i; ++j)
		{
			if (array[j] > array[j+1])
			{
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
				pos = j;
			}
		}
		i = pos;
	}
}

//冒泡排序 改进 双向冒泡
void bubbleSort2(int array[], int length)
{
	int low = 0;
	int high = length - 1;
	while(low < high){
		for (int j = low; j < high; j++)
		{
			//正向冒泡
			if (array[j] > array[j+1])
			{
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
		high--;
		for (int j = high; j > low; j--)
		{
			//反向冒泡
			if (array[j-1] > array[j])
			{
				int temp = array[j];
				array[j] = array[j-1];
				array[j-1] = temp;
			}
		}
		low++;
	}
}

//快速排序
void quickSort(int array[], int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int i = low;
	int j = high;
	int cur = array[i];
	int curIndex = i;
	while(i < j){
		cur = array[i];
		curIndex = i;
		while(curIndex < j && array[j] >= cur) j--;
		array[curIndex] = array[j];
		array[j] = cur;
		curIndex = j;
		while(i < curIndex && array[i] <= cur) i++;
		array[curIndex] = array[i];
		array[i] = cur;
		curIndex = i;
	}
	quickSort(array, low, curIndex-1);
	quickSort(array, curIndex+1, high);
}

//快速排序 改进 前后中三点取中
void quickSort1(int array[], int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int i = low;
	int j = high;
	int cur = array[i];
	int curIndex = i;
	while(i < j){
		//前后中三点取中 start
		cur = array[i];
		curIndex = i;
		int max = array[i];
		int maxIndex = i;
		int min = array[i];
		int minIndex = i;
		if (array[i] > array[j])
		{
			min = array[j];
			minIndex = j;
		}else{
			max = array[j];
			maxIndex = j;
		}

		if (min > array[(i+j)/2])
		{
			cur = min;
			curIndex = minIndex;
		}else if (max < array[(i+j)/2])
		{
			cur = max;
			curIndex = maxIndex;
		}else{
			cur = array[(i+j)/2];
			curIndex = (i+j)/2;
		}
		//前后中三点取中 end

		while(curIndex < j && array[j] >= cur) j--;
		array[curIndex] = array[j];
		array[j] = cur;
		curIndex = j;
		while(i < curIndex && array[i] <= cur) i++;
		array[curIndex] = array[i];
		array[i] = cur;
		curIndex = i;
	}
	quickSort1(array, low, curIndex-1);
	quickSort1(array, curIndex+1, high);
}

//快速排序 改进 对长度大于k的序列快速排序，小于k的序列插入排序
void quickSort2(int array[], int low, int high)
{
	if (low >= high)
	{
		return;
	}

	int k = 8;
	int i = low;
	int j = high;
	if (j - i < k)
	{
		//序列小于k，使用插入排序
		for (int x = i+1; x <= j; x++)
		{
			int value = array[x];
			int y = x;
			for (; y > i; y--)
			{
				if (array[y-1] > value)
				{
					array[y] = array[y-1];
				}else{
					break;
				}
			}
			array[y] = value;
 		}
	}else{
		//序列大于k，使用快速排序
		int cur = array[i];
		int curIndex = i;
		while(i < j){
			cur = array[i];
			curIndex = i;
			while(curIndex < j && array[j] >= cur) j--;
			array[curIndex] = array[j];
			array[j] = cur;
			curIndex = j;
			while(i < curIndex && array[i] <= cur) i++;
			array[curIndex] = array[i];
			array[i] = cur;
			curIndex = i;
		}
		quickSort2(array, low, curIndex-1);
		quickSort2(array, curIndex+1, high);
	}
}
