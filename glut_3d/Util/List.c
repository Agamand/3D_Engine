#include <stdio.h>
#include <stdlib.h>
#include "List.h"



ListCh * newListCh()
{
	ListCh * ls;
	ls = (ListCh*)malloc(sizeof(ListCh));
	ls->begin = newPointer(NULL);
	ls->end = newPointer(NULL);
	ls->begin->nextpointer = ls->end;
	ls->size = 0;
	initListCh(ls);
	return ls;
}

void initListCh(ListCh *ls)
{
	ls->Append = appendListCh;
	ls->Erase = eraseListCh;
	//ls->IsEmpty = isEmpty;
}

void deleteListCh(ListCh* ls)
{
	Pointer * pt,*ptdel = NULL;
	pt = ls->begin;
	while(pt != NULL)
	{
		ptdel = pt;
		pt = pt->nextpointer;
		if(ptdel != NULL)
			free(ptdel);
	}
	free(ls);
}

List * newList()
{
	List * ls;
	ls = (List*)malloc(sizeof(List));
	ls->list = NULL;
	ls->size = 0;
	initList(ls);
	return ls;
}

void initList(List * ls)
{
	ls->Append = appendList;
	ls->Erase = eraseList;
}

void deleteList(List* ls)
{
	free(ls->list);
	free(ls);
}

void appendList(List* ls, void* p)
{
	int i;
	Tab * newtab;
	newtab = (Tab*)malloc(sizeof(Tab*)*(ls->size+1));
	for(i = 0; i < ls->size; i++)
		newtab[i] = ls->list[i];
	newtab[ls->size].pointer = p;
	free(ls->list);
	ls->list = newtab;
	ls->size++;
}

void eraseList(List* ls, void* p)
{
	int	i, n = 0;
	Tab * newtab;
	newtab = (Tab*)malloc(sizeof(Tab*)*(ls->size-1));
	for(i = 0; i < ls->size; i++)
		if(ls->list[i].pointer == p)
			continue;
		else newtab[n++] = ls->list[i];

	free(ls->list);
	ls->list = newtab;
	ls->size--;
}

Pointer* newPointer(void * pt)
{
	Pointer* p;
	p = (Pointer*)malloc(sizeof(Pointer));
	p->pointer = pt;
	p->nextpointer = NULL; 
	return p;
}


void appendListCh(ListCh* ls, void* p)
{
	Pointer * pt;
	if(p == NULL)
		return;
	ls->end->pointer = p;
	pt = newPointer(NULL);
	ls->end->nextpointer = pt;
	ls->end = pt;
	ls->size++;
}

void eraseListCh(ListCh* ls, void* p)
{
	Pointer * pt, *ptdel;
	pt = ls->begin;
	while(pt->nextpointer != NULL)
	{
		if(pt->nextpointer->pointer == p)
		{
			ptdel = pt->nextpointer;
			pt->nextpointer = ptdel->nextpointer;
			free(ptdel);
			ls->size--;
			return;
		}else pt = pt->nextpointer;
	}
}

