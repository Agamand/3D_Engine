

#ifndef LIST_H
#define LIST_H
typedef struct StructPointer Pointer;
typedef struct StructListCh ListCh;
typedef struct StructList List;
typedef struct StructTab Tab;

struct StructPointer
{
	void * pointer;
	Pointer * nextpointer;
};

struct StructTab
{
	void * pointer;
};



struct StructListCh // Liste CH
{
	Pointer* begin;
	Pointer* end;
	int size;

	void(*Append)(ListCh*,void*);
	void(*Erase)(ListCh*,void*);
	//int(*IsEmpty)(ListCh*);
};

struct StructList
{
	Tab* list;
	int size;

	void(*Append)(List*,Tab*);
	void(*Erase)(List*,Tab*);
	//int(*IsEmpty)(List*);
};

ListCh * newListCh();
void deleteListCh(ListCh*);
void initListCh(ListCh*);
List * newList();
void deleteList(List*);
void initList(List*);
Pointer * newPointer();


void appendListCh(ListCh*,void*);
void eraseListCh(ListCh*,void*);
//int isEmpty(ListCh* ls) { return ls->begin->nextpointer == ls->end;}

void appendList(List*,Tab*);
void eraseList(List*,Tab*);

#endif