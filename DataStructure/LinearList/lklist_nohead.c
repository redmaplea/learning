#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 定义单链表的结点类型
 */
struct LNode {
	int data;				// 数据域
	struct LNode *next;		// 指针域，指向下一个结点
};

typedef struct LNode LNode;
typedef struct LNode *LinkList;

// 按位查找
LNode *GetElem(LinkList L, int i)
{
	if (i < 0)
		return NULL;
	
	int j = 1;
	LNode *p = L;				//指向第一个结点
	while (p != NULL && j < i) {
		p = p->next;
		j++;
	}
	
	return p;
}

// 按值查找
LNode *LocateElem(LinkList L, int e)
{
	LNode *p = L;
	while (p != NULL && p->data != e)
		p = p->next;
	
	return p;
}

//在某个结点后插入新结点
int InsertNextNode(LNode *p, int e)
{
	if (p == NULL)
		return -1;
	
	LNode *s = (LNode *)malloc(sizeof(LNode));
	if (s == NULL)
		return -1;
	
	s->data = e;			//新结点数据域赋值 e
	s->next = p->next;		//新结点的后继指向原结点后继
	p->next = s;			//原结点的后继指向新结点
	
	return 0;
}

//在某个结点前插入新结点
int InsertPreNode(LNode *p, int e)
{
	if (p == NULL)
		return -1;
	
	LNode *s = (LNode *)malloc(sizeof(LNode));
	if (s == NULL)
		return -1;
	
	s->next = p->next;
	p->next = s;
	s->data = p->data;		//数据交换位置
	p->data = e;
	
	return 0;
}

int ListInsert(LinkList *L, int i, int e)
{
	int ret;
	
	if (i < 1)
		return -1;
	
	// 当插入位置为第一个结点时
	if (i == 1) {
		LNode *s = (LNode *)malloc(sizeof(LNode));
		if (s == NULL)
			return -1;
		
		s->data = e;
		
		// 当 L 为空表时
		if (*L == NULL) {
			s->next = NULL;
			*L = s;
		} else {
			s->next = *L;			//新节点的后继指向原第一个结点
			*L = s;					//新节点作为第一个节点
		}
	} else {
		// 先找到需要插入的位置的前驱结点
		LNode *p = GetElem(*L, i - 1);
		ret = InsertNextNode(p, e);
	}

	return ret;
}

//删除某个结点的后继结点
int DeleteNextNode(LNode *p, int *e)
{
	if (p == NULL)
		return -1;
	
	LNode *s = p->next;			//保存原结点的后继结点
	if (s == NULL)
		return -1;
	
	p->next = s->next;			//原结点的后继指向后继的后继
	*e = s->data;
	
	free(s);
	
	return 0;
}

//删除某个结点
int DeleteNode(LNode *p, int *e)
{
	if (p == NULL)
		return -1;
	
	LNode *s = p->next;			//保存原结点的后继结点
	if (s == NULL)
		return -1;
	
	p->next = s->next;			
	p->data = s->data;			//原后继的值覆盖
	
	free(s);
	
	return 0;
}

int ListDelete(LinkList *L, int i, int *e)
{
	int ret;
	if (i < 1)
		return -1;
	
	// 第一个结点特殊处理
	if (i == 1) {
		LNode *p = *L;
		if (p == NULL)
			return -1;
		
		*L = (*L)->next;
		*e = p->data;
		
		free(p);
	} else {
		// 先找到需要删除结点的前驱结点
		LNode *p = GetElem(*L, i - 1);
		
		// 再删除位置为 i 的结点
		ret = DeleteNextNode(p, e);
	}
	
	return ret;
}

// 求表长
int ListLength(LinkList L)
{
	int len;
	LNode *p = L;
	
	len = 0;
	while (p != NULL) {
		p = p->next;
		len++;
	}
	
	return len;
}

// 打印表元素
void ListPrint(LinkList L)
{
	LNode *p = L;
	
	while (p != NULL){
		printf("[%d]->", p->data);
		p = p->next;
	}
	
	printf("NULL\n");
}

int main()
{
	int e, len;
	
	// 不带头结点
	LinkList L = NULL;

	// 头插法：整个表逆序时可以使用该方法
	/*for (int i = 1; i <= 10; i++)
		if (InsertNextNode(head, i))
			printf("Insert error: %d\n", i);
	
	ListPrint(L);*/
	
	// 尾插法
	for (int i = 1; i <= 10; i++)
		if (ListInsert(&L, i, i))
			printf("Insert error: %d\n", i);
	
	ListPrint(L);
	
	// 在第1位插入元素 1000
	if (ListInsert(&L, 1, 1000))
		printf("Insert error.\n");
	
	ListPrint(L);
	
	// 在第100位插入元素 100
	if (ListInsert(&L, 100, 100))
		printf("Insert error.\n");
	
	ListPrint(L);
	
	// 在第5位插入元素 50
	if (ListInsert(&L, 5, 50))
		printf("Insert error.\n");
	
	ListPrint(L);
	
	// 删除第100个节点
	if (ListDelete(&L, 100, &e))
		printf("Delete error.\n");
	else
		printf("Delete: %d\n", e);
	
	ListPrint(L);
	
	// 删除第8个节点
	if (ListDelete(&L, 8, &e))
		printf("Delete error.\n");
	else
		printf("Delete: %d\n", e);
	
	ListPrint(L);
	
	// 删除第1个节点
	if (ListDelete(&L, 1, &e))
		printf("Delete error.\n");
	else
		printf("Delete: %d\n", e);
	
	ListPrint(L);
	
	// 求表长
	len = ListLength(L);
	printf("Length: %d\n", len);
	
	for (int i = len; i > 0; i--)
		if (ListDelete(&L, i, &e))
			printf("Delete error.\n");
		else
			printf("Delete: %d\n", e);
	
	len = ListLength(L);
	printf("Length: %d\n", len);
	ListPrint(L);
	
	return 0;
}