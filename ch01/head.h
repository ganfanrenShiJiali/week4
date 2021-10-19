#include<stdbool.h>
#ifndef _HashSep_H
#define _HashSep_H

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
typedef int ElementType;

bool isPrime(int num);
int NextPrime(int n);
HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);
int Hash(ElementType Key, int N);

#endif
struct ListNode
{
	ElementType Element;
	Position Next;
};
typedef Position List;
struct HashTbl
{
	int TableSize;
	List *TheLists;
};
