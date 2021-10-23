#ifndef _BinHeap_H
#define _BinHeap_H

struct  HeapStruct;
typedef struct HeapStruct *PriorityQueue;
typedef int ElementType;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(ElementType x, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
PriorityQueue BuildHeap(int a[],int N,PriorityQueue H);
void PercolateDown(int i,PriorityQueue H);
void printPQ(PriorityQueue H);

#endif

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};
