#include"head.h"
#include<stdio.h>
#include<errno.h>
#include<stdbool.h>//不然不能识别Bool类型
#include<math.h>
#define MinTableSize 5

bool isPrime(int num)
{
	int i, k;
	k = (int)sqrt(num);
	for (i = 2; i <= k; i++)
		if (num%i == 0)  return 0;
	return 1;	   //注意 写成 else	return 1;是错的！！ERROR!!
}
int NextPrime(int n)
{
	bool state = isPrime(n);
	while (!state)
	{
		state = isPrime(++n);
	}
	return n;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;
	if(TableSize<MinTableSize)
	{
		perror("Table size too small");
		return NULL;
	}
	H = malloc(sizeof(struct HashTbl));
	if (H == NULL)
		perror("Out of space!!!");
	H->TableSize = NextPrime(TableSize);
	H->TheLists = malloc(sizeof(List)*H->TableSize);
	if (H->TheLists == NULL)
		perror("Out of space!!!");
	for (i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = malloc(sizeof(struct ListNode));
		if (H->TheLists[i] == NULL)
			perror("Out of space!!!");
		else
			H->TheLists[i]->Next = NULL;
	}
	return H;
}
int Hash(ElementType Key, int N)
{
	return Key % N;
}
void DestroyTable(HashTable H)
{
	List Los;
	Position Pos, Tmp;
	int i;
	for (i = 0; i < H->TableSize; i++)
	{
		Los = H->TheLists[i];
		Pos = Los->Next;
		Los->Next = NULL;
		while (Pos != NULL)
		{
			Tmp = Pos->Next;
			free(Pos);
			Pos = Tmp;
		}
		free(Los);
	}
}
Position Find(ElementType Key, HashTable H)
{
	Position P;
	List L;
	L = H->TheLists[Hash(Key, H->TableSize)];
	P = L->Next;
	while (P != NULL && P->Element != Key)
	{
		P = P->Next;
	}
	return P;
}
void Insert(ElementType Key, HashTable H)
{
	Position Pos, NewCell;
	List L;
	Pos = Find(Key, H);
	if (Pos == NULL)
	{
		NewCell = malloc(sizeof(struct ListNode));
		if (NewCell == NULL)
			perror("Out of space!!!");
		else
		{
			L = H->TheLists[Hash(Key, H->TableSize)];
			NewCell->Element = Key;
			NewCell->Next = L->Next;
			L->Next = NewCell;//头插法
		}

	}
}
ElementType Retrieve(Position P)
{
	if (P == NULL)
	{
		perror("没有找到该元素！");
	}
	else
		return P->Element;
}
int main()
{
	printf("开始构建散列表···\n");
	HashTable H = NULL;
	H = InitializeTable(10);
	int a[10] = { 0,1,4,9,16,25,36,49,64,81 };
	int i;
	for (i = 0; i < 10; i++)
	{
		Insert(a[i], H);
	}
	printf("%d\n", Retrieve(Find(16, H)));
	printf("%d\n", Retrieve(Find(4, H)));
	printf("%d\n", Retrieve(Find(2, H)));
	DestroyTable(H);
	return 0;
}
