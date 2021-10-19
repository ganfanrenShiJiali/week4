#include"head.h"
#include<stdio.h>
#include<math.h>
#define MinTableSize 5
bool IsPrime(int num)
{
	int i, k;
	k = sqrt(num);
	for (i = 2; i <= k; i++)
		if (num%i == 0) return 0;
	return 1;
}
int NextPrime(int n)
{
	bool state = IsPrime(n);
	while (!state)
	{
		state = IsPrime(++n);
	}
	return n;
}
int Hash(ElementType Key, int TableSize)
{
	return Key % TableSize;
}
HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;
	if (TableSize < MinTableSize)
	{
		perror("Table size too small");
		return NULL;
	}
	H = malloc(sizeof(struct HashTbl));
	if (H == NULL)
		perror("Out of space!!!");
	H->TableSize = NextPrime(TableSize);
	H->TheCells = malloc(sizeof(Cell)*H->TableSize);
	if (H->TheCells == NULL)
		perror("Out of space!!!");
	for (i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;
	return H;
}
void DestroyTable(HashTable H)
{
	free(H->TheCells);
	free(H);
}
Position Find(ElementType Key, HashTable H)
{
	Position CurrentPos;
	int CollisionNum;

	CollisionNum = 0;
	CurrentPos = Hash(Key, H->TableSize);
	while (H->TheCells[CurrentPos].Info != Empty && H->TheCells[CurrentPos].Element != Key)
	{//如果非空并且不是该元素
		CurrentPos += 2 * ++CollisionNum - 1;
		if (CurrentPos >= H->TableSize)
			CurrentPos -= H->TableSize;
	}
	return CurrentPos;//如果没有找到，则这个位置正好是应该插入的位置
}
void Insert(ElementType Key, HashTable H)
{
	Position Pos;
	Pos = Find(Key, H);
	if (H->TheCells[Pos].Info != Legitimate)
	{
		H->TheCells[Pos].Element = Key;
		H->TheCells[Pos].Info = Legitimate;
	}
}
ElementType Retrieve(Position P, HashTable H)
{
	return H->TheCells[P].Element;
}
HashTable Rehash(HashTable H)
{
	int i, OldSize;
	Cell *OldCells;
	OldCells = H->TheCells;
	OldSize = H->TableSize;
	H = InitializeTable(2 * OldSize);
	for (i = 0; i < OldSize; i++)
		if (OldCells[i].Info == Legitimate)
			Insert(OldCells[i].Element, H);
	free(OldCells);
	return H;
}
int main()
{
	printf("开始构建散列表···\n");
	HashTable H = NULL;
	H = InitializeTable(10);
	int a[5] = { 89,18,49,58,69 };
	int i;
	for (i = 0; i < 5; i++)
	{
		Insert(a[i], H);
	}
	printf("%d\n", Find(49, H));
	printf("%d\n", Find(58, H));
	printf("%d\n", Find(69, H));
	//printf("%d\n",Retrieve(2, H));
	printf("%d\n", Retrieve(3, H));
	H = Rehash(H);
	DestroyTable(H);
	printf("散列表已销毁\n");
	return 0;
}
