#include"head.h"
#include<stdio.h>
#include<errno.h>
#include<math.h>
#define MinPQSize 5
#define MinData 0

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	if (MaxElements < MinPQSize)
		perror("PriorityQueue is too small!");
	H = malloc(sizeof(struct HeapStruct));
	if (H == NULL)
		perror("Out of space!!!");
	H->Elements = malloc(sizeof(ElementType)*(MaxElements+1));
	if (H->Elements == NULL)
		perror("Out of space!!!");
	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[0] = MinData;
	return H;
}
void Destroy(PriorityQueue H)
{
	if (H != NULL)
	{
		H->Elements = NULL;
		free(H->Elements);
		free(H);
	}
}
void MakeEmpty(PriorityQueue H)
{
	if (H == NULL)
		printf("Please initialize priority queue first!");
	else
	{
		H->Size = 0;
	}
}
void Insert(ElementType x, PriorityQueue H)
{
	int i;
	if (IsFull(H))
	{
		perror("Priority queue is full!");
			return;
	}
	else
	{
		for (i = ++H->Size; H->Elements[i/2]>x;i/=2)
		{
			H->Elements[i] = H->Elements[i / 2];
		}
		H->Elements[i] = x;
	}
}
ElementType DeleteMin(PriorityQueue H)
{
	int i, Child;
	ElementType MinElement,LastElement;
	if (IsEmpty(H))
	{
		perror("Priority queue is empty!");
		return H->Elements[0];
	}
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];
	for (i = 1;i*2<=H->Size;i=Child)
	{
		Child = i * 2;
		if (Child!=H->Size && H->Elements[Child] > H->Elements[Child + 1])
			Child++;
		if (LastElement > H->Elements[Child])
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}
ElementType FindMin(PriorityQueue H)
{
	return H->Elements[1];
}
int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}
int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}
PriorityQueue BuildHeap(int a[],int N, PriorityQueue H)
{
	int i;
	if (H == NULL)
		H = Initialize(N);
	for (i = 1; i <= N; i++)
	{
		H->Elements[i] = a[i - 1];
		H->Size++;
	}
	for (i = N / 2; i > 0; i--)
		PercolateDown(i,H);
	return H;
}
void PercolateDown(int i,PriorityQueue H)
{
	int j,Child;
	ElementType NowElement;
	
	for (j = i; j * 2 <= H->Size; j = Child)
	{
		Child = j * 2;
		if (Child!=H->Size && H->Elements[Child] > H->Elements[Child + 1])
			Child++;
		if (H->Elements[j] > H->Elements[Child])
		{
			NowElement = H->Elements[j];
			H->Elements[j] = H->Elements[Child];
			H->Elements[Child] = NowElement;
		}
		else
			break;
	}
}
void printPQ(PriorityQueue H)
{
	int i = 0, j, k, z, z1,pos;
	if (H == NULL)
		perror("Priority queue is null");
	while (H->Size > pow(2, i) - 1)
	{
		i++;//13:4,树的节点达到了第几层
	}
	k = 1;//当前输出第K层
	for (j = 1; j <= H->Size;j=j)
	{
		z = pow(2, (i - k + 1)) - 1;//两个节点之间隔几个空
		z1 = pow(2, i - k) - 1;//这层开始空几个空
		for (pos = z1; pos >= 0; pos--)
		{
			printf("  ");
		}
		printf("%d", H->Elements[j++]);
		while (j <= pow(2, k) - 1)
		{
			for (pos = z; pos >= 0; pos--)
			{
				printf("  ");
			}
			printf("%d", H->Elements[j++]);
		}
		printf("\n");
		k++;
	}
}
int main()
{
	int a[15] = { 150,80,40,30,10,70,110,100,20,90,60,50,120,140,130 };
	PriorityQueue H = NULL;
	H = BuildHeap(a, 15, H);
	printf("该优先队列的最小值是：%d\n", FindMin(H));
	printPQ(H);
	DeleteMin(H);
	printf("该优先队列的最小值是：%d\n", FindMin(H));
	Insert(6, H);
	printf("该优先队列的最小值是：%d\n", FindMin(H));
	return 0;
}
