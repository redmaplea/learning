#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE	10

typedef int ElemType;
typedef struct {
	ElemType *data;
	int max_length, cur_length;
}Sqlist;

/*
 * 初始化顺序表
 */
static int initSqlist(Sqlist *L)
{
	L->data = (ElemType *)malloc(INIT_SIZE * sizeof(ElemType));
	if (!L->data)
		return -1;	
	
	L->cur_length = 0;
	L->max_length = INIT_SIZE;

	return 0;
}

/*
 * 清空顺序表
 */
static int clearSqlist(Sqlist *L)
{
	if (!L->data)
		return -1;
	
	free(L->data);
	L->cur_length = 0;
	L->max_length = 0;

	return 0;
}

/*
 * 顺序表判空操作
 */
static int sqlistEmpty(Sqlist L)
{
	return (L.cur_length == 0);
}

/*
 * 求顺序表当前表长
 */
static int sqlistLength(Sqlist L)
{
	return L.cur_length;
}

/*
 * 获取顺序表中位序为 index 的元素，并返回给 e
 */
static int getElem(Sqlist L, int index, int *e)
{
	if (L.cur_length == 0)
		return -1;

	if (index < 1 || index > L.cur_length)
		return -1;

	*e = L.data[index - 1];

	return 0;
}

/*
 * 定位顺序表中值为 e 的元素
 */
static int locateElem(Sqlist L, int e)
{
	int i;

	if (L.cur_length == 0)
		return -1;

	for (i = 0; i < L.cur_length; i++)
		if (L.data[i] == e)
			return i + 1;

	return -1;
}

/*
 * 在顺序表位序为 index 的位置插入值为 e 的元素
 * 注意：数组下标从 0 开始，而位序从 1 开始
 */
static int sqlistInsert(Sqlist *L, int index, int e)
{
	int i;
	
	if (index < 1 || index > L->cur_length + 1)
		return -1;
	
	if (L->cur_length == L->max_length)
		return -1;
	
	for (i = L->cur_length; i >= index; i--)
		L->data[i] = L->data[i - 1];
	
	L->data[index - 1] = e;
	
	L->cur_length++;	//顺序表当前长度加 1
	
	return 0;
}

/*
 * 删除顺序表位序为 index 的元素，并返回给 e
 * 注意：数组下标从 0 开始，而位序从 1 开始
 */
static int sqlistDelete(Sqlist *L, int index, int *e)
{
	int i;
	
	if (index < 1 || index > L->cur_length)
		return -1;
	
	*e = L->data[index -1];
	
	for (i = index; i < L->cur_length; i++)
		L->data[i - 1] = L->data[i];

	L->cur_length--;	//顺序表当前长度减 1
	
	return 0;
}

/*
 * 打印顺序表的所有元素
 */
static int sqlistPrint(Sqlist L)
{
	if (L.cur_length <1 || L.cur_length > L.max_length)
		return -1;
	
	for (int i = 0; i < L.cur_length - 1; i++)
		printf("[%d]->", L.data[i]);
	
	printf("[%d]\n", L.data[L.cur_length - 1]);
	
	return 0;
}

int main()
{
	int index, e;
	Sqlist L;
	
	initSqlist(&L);
	
	if (sqlistEmpty(L))
		printf("List is empty.\n");
	
	for (int i = 1; i < 6; i++)
		sqlistInsert(&L, i, i);
	
	sqlistPrint(L);
	
	index = 3;
	getElem(L, index, &e);
	printf("List %dth element is %d\n", index, e);
	
	sqlistDelete(&L, index, &e);
	printf("List delete %dth element value %d\n", index, e);
	
	e = 8;
	sqlistInsert(&L, index, e);
	
	e = 8;
	printf("List %dth element value is %d\n", locateElem(L, e), e);
	
	sqlistPrint(L);
	
	clearSqlist(&L);
	
	return 0;
}
