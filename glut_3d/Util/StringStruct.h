//#include <string.h>
#include "List.h"

typedef struct StringStruc StringC;
struct StringStruc
{
	// Variables

	char * str;
	int size;

	//Fonctions

	void(*Conca) (StringC*, char *);
	void(*ConcaInt)(StringC*, int);
	int(*IndexOf)(StringC*, char*, int);
    void(*SupprOf)(StringC*, char*, int);
	void(*SupprAllOf)(StringC*, char*);
	StringC*(*Cut)(StringC *, int, int);
	int(*GetCount)(StringC*);
	int(*GetCountOf)(StringC*, char*);
	int(*CompareTo)(StringC*, char*);
	char*(*GetChar)(StringC*);
	int(*ToInt)(StringC*);
	ListCh*(*GetWordList)(StringC*);
};


StringC* newString(char *);
StringC* newStringInt(int);
void deleteString(StringC *);
void initStringStruc();
void conca(StringC*, char *);
void concaInt(StringC*, int);
int indexOf(StringC*, char*, int);
void supprOf(StringC*, char*, int);
void supprAllOf(StringC*, char*);
StringC * cut(StringC *, int, int);
int getCount(StringC*);
int getCountOf(StringC*, char*);
int compareTo(StringC*,char*);
char* getChar(StringC*);
int toInt(StringC*);
ListCh * getWordList(StringC*);


