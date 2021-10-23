#include"head.h"
#include<stdio.h>

PriorityQueue Initialize(void)//?
{
	PriorityQueue H;
	H = malloc(sizeof(struct TreeNode));
	if (H == NULL)
		perror("Out of space!!!");
	else
	{
		H->Left = H->Right = NULL;
		H->Npl = -1;
	}
	return H;
}
ElementType FindMin(PriorityQueue H)
{
	return H->Element;
}
int IsEmpty(PriorityQueue H)
{
	return H->Left = H->Right = NULL;
}
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
	if (H1 == NULL)
		return H2;
	if (H2 == NULL)
		return H1;
	if (H1->Element < H2->Element)
		return Merge1(H1, H2);
	else
		return Merge1(H2, H1);
}
static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
	if (H1->Left == NULL)
		H1->Left = H2;
	else
	{
		H1->Right = Merge(H1->Right, H2);
		if (H1->Left->Npl < H1->Right->Npl)
			SwapChildren(H1);
		H1->Npl = H1->Right->Npl + 1;
	}
	return H1;
}
PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
	PriorityQueue SingleNode;
	SingleNode = malloc(sizeof(struct TreeNode));
	if (SingleNode == NULL)
		perror("Out of space!!!");
	else
	{
		SingleNode->Element = X;
		SingleNode->Left = SingleNode->Right = NULL;
		SingleNode->Npl = 0;
		H = Merge(SingleNode, H);
	}
	return H;
}
PriorityQueue DeleteMin1(PriorityQueue H)
{
	PriorityQueue LeftHeap, RightHeap;
	if (IsEmpty(H))
	{
		perror("Priority queue is empty!");
		return H;
	}
	LeftHeap = H->Left;
	RightHeap = H->Right;
	free(H);
	return Merge(LeftHeap, RightHeap);
}
