#include "header.c"
#include "Node.c"

void printfArray(int array[], int length);
void sortByOddEvenNumber(int a[],int length);
int searchSubString(char *string, char *subString);
Node * reverseNodeList(Node *nodes);

int main()
{
	//初始化一个随机数组
	srand(time(0));
	const int length = 10;
	int array[10];
	for (int i = 0; i < length; ++i)
	{
		array[i] = rand()%100;
	}

	printf("原数组:\n");
	printfArray(array, length);

	sortByOddEvenNumber(array, length);
	printf("奇数在前，偶数在后:\n");
	printfArray(array, length);

	char string[] = "hello alignment";
	char subString[] = "alignment";
	int index = searchSubString(string, subString);
	printf("查找子串:\n");
	printf("string=%s, subString=%s, search index=%d\n", string, subString, index);

	//生成一个链表
	struct Node node = {1, NULL};
	struct Node *h = &node;
	struct Node *p = h;
	struct Node ns[10];
	for (int i = 2; i < 10; ++i)
	{
		ns[i].data = i, ns[i].next = NULL;
		p->next = &ns[i];
		p = &ns[i];
	}
	printf("原链表:\n");
	printfNodeList(h);

	struct Node *reverseH = reverseNodeList(h);
	printf("倒序链表:\n");
	printfNodeList(reverseH);

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

///把一个数组里的数，奇数全在前面，偶数全在后面，要求空间复杂度为O(1)。
void sortByOddEvenNumber(int a[], int length)
{
	int i = 0, j = length-1;

	while(i < j){
		while(i < j && a[i] % 2 == 1) i++;
		while(i < j && a[j] % 2 == 0) j--;
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}

///查找子串。
int searchSubString(char *string, char *subString)
{
	int length = strlen(string);
	int subLength = strlen(subString);
	int index = -1;

	for (int i = 0; i < length-subLength+1; ++i)
	{
		int j = 0;
		for (; j < subLength; ++j)
		{
			if (string[i+j] != subString[j])
			{
				break;
			}
		}
		if (j == subLength)
		{
			index = i;
		}
	}

	return index;
}

///倒序链表
Node * reverseNodeList(Node *nodes)
{
	Node *p = nodes->next;
    Node *newP = nodes;
    newP->next = NULL;
    while(p != NULL)
    {
        Node *curP = p;
        p = p->next;
        
        curP->next = newP;
        newP = curP;
    }
    return newP;
}






