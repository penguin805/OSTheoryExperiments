#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef unsigned long DWORD;
typedef unsigned char RESULT;
#define SUCCESS	(RESULT)~0
#define ERROR	(RESULT)0
#define TOTAL_MEM_SIZE 1024

enum BlockState
{
	BLOCK_FREE = 0,
	BLOCK_BUSY = 1
};

struct FreeMemBlock
{
	DWORD BlockAddress;
	DWORD BlockSize;
	BlockState State;
};
typedef struct FreeMemBlock FREEBLOCK;

struct FreeBlockTableNode
{
	FREEBLOCK MemBlock;
	struct FreeBlockTableNode *Prev;
	struct FreeBlockTableNode *Next;
};
typedef struct FreeBlockTableNode FREEBLOCKTABLE_NODE;

struct FreeBlkDuLinkedList
{
	FREEBLOCKTABLE_NODE *Head, *Tail;
	RESULT(*BlockAllocFunc)(unsigned Size);
};
typedef struct FreeBlkDuLinkedList FREEBLOCK_TABLE;

FREEBLOCK_TABLE BlockTable;

RESULT NextFitAlloc(unsigned Size)
{
	return SUCCESS;
}

RESULT BestFitAlloc(unsigned Size)
{
	return SUCCESS;
}

RESULT WorstFitAlloc(unsigned Size)
{
	return SUCCESS;
}

RESULT LAlloc(unsigned Size)
{
	if (Size > TOTAL_MEM_SIZE)
		return ERROR;
	else
		return BlockTable.BlockAllocFunc(Size);
}

void LFree(unsigned Addr)
{

}

void PrintTable()
{
	int Num = 0;
	FREEBLOCKTABLE_NODE *pNode = BlockTable.Head->Next;
	const char *szStateStr[] = { "空闲","已分配" };
	puts("\n------------分配情况------------");
	puts("分区号\t始地址\t区大小\t状态\n");
	while (pNode)
	{
		printf("%-4d\t%-4d\t%-4dKB\t%s\n", Num, pNode->MemBlock.BlockAddress,
			pNode->MemBlock.BlockSize, szStateStr[pNode->MemBlock.State]);
		Num++;
		pNode = pNode->Next;
	}
	puts("--------------------------------");
}

RESULT InitFreeBlkDuLinkedList(int Algorithm)
{
	RESULT(*AllocFunc[3])(unsigned Size) = {
		NextFitAlloc, BestFitAlloc, WorstFitAlloc
	};
	memset(&BlockTable, 0, sizeof(FREEBLOCK_TABLE));
	
	if (Algorithm >= 0 && Algorithm <= 2)
	{
		BlockTable.BlockAllocFunc = AllocFunc[Algorithm];
	}
	else
		return ERROR;

	BlockTable.Head = (FREEBLOCKTABLE_NODE *)malloc(sizeof(FREEBLOCKTABLE_NODE));
	BlockTable.Tail = (FREEBLOCKTABLE_NODE *)malloc(sizeof(FREEBLOCKTABLE_NODE));
	BlockTable.Head->Prev = NULL;
	BlockTable.Head->Next = BlockTable.Tail;
	BlockTable.Tail->Prev = BlockTable.Head;
	BlockTable.Tail->Next = NULL;
	BlockTable.Tail->MemBlock.BlockAddress = 0;
	BlockTable.Tail->MemBlock.BlockSize = TOTAL_MEM_SIZE;
	BlockTable.Tail->MemBlock.State = BLOCK_FREE;
	return SUCCESS;
}

int main()
{
	int Algorithm, Action;
	puts("0. 循环首次适应算法 (Next Fit)");
	puts("1. 最佳适应算法 (Best Fit)");
	puts("2. 最坏适应算法 (Worst Fit)");
	printf("选择: ");
	scanf("%d", &Algorithm);
	if (InitFreeBlkDuLinkedList(Algorithm) != SUCCESS)
		return -1;
	
	while (1)
	{
		PrintTable();
		puts("内存操作：");
		puts("1: 分配\n2: 回收\n0: 退出");
		scanf("%d", &Action);
		switch (Action)
		{
		case 1:
			{
				
			}
			break;
		case 2:
			break;
		case 0:
			return 0;
		default:
			break;
		}
	}
	return 0;
}