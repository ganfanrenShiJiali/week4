#ifndef _BinQueue_H
#define _BinQueue_H
typedef struct BinNode *Position;
typedef struct BinNode *BinTree;
typedef struct Collection *BinQueue;
typedef int ElementType;
#define MaxTrees 50


BinTree CombineTrees(BinTree T1, BinTree T2);
BinQueue Merge(BinQueue H1, BinQueue H2);
ElementType DeleteMin(BinQueue H);

#endif
struct BinNode
{
	ElementType Element;
	Position LeftChildren;
	Position NextSibling;
};
struct Collection
{
	int CurrentSize;
	BinTree TheTrees[MaxTrees];
};
