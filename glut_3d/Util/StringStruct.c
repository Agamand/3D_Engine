#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "StringStruct.h"

#define NUM_ASCII_BEGIN 48
#define NUM_ASCII_SIZE 10

StringC * newString(char * str)
{
	StringC * s_Str;
	char * newStr;
	unsigned int size;
	size = strlen(str)+1;
	s_Str = (StringC*)malloc(sizeof(StringC));
	newStr = (char*)malloc(sizeof(char)*size);
	strcpy(newStr,str);
	s_Str->str = newStr;
	s_Str->size = size;
	initStringStruc(s_Str);
	return s_Str;
}

StringC * newStringInt(int val)
{
	char buffer[32];
	itoa(val,buffer,32);
	return newString(buffer);
}

void deleteString(StringC *str)
{
	free(str->str);
	free(str);
}

void initStringStruc(StringC* str)
{
	str->Conca = conca;
	str->ConcaInt = concaInt;
	str->IndexOf = indexOf;
	str->SupprOf = supprOf;
	str->SupprAllOf = supprAllOf;
	str->Cut = cut;
	str->GetCount = getCount;
	str->GetCountOf = getCountOf;
	str->CompareTo = compareTo;
	str->GetChar = getChar;
	str->ToInt = toInt;
	str->GetWordList = getWordList;
}


void conca(StringC * str, char * chr)
{
	int newsize;
	char* newchr;
	newsize = strlen(str->str)+strlen(chr)+1;
	newchr = (char*)malloc(sizeof(char)*newsize);
	strcpy(newchr,str->str);
	strcat(newchr,chr);
	free(str->str);
	str->str = newchr;
}

void concaInt(StringC * str, int val)
{
	char buffer[32];
	itoa(val,buffer,32);
	str->Conca(str,buffer);
}

int indexOf(StringC * str, char *chr, int initpos)
{
	int size = 0;
	char * i;
    size = strlen(chr);
	for(i = str->str+initpos; i < (str->str+strlen(str->str)); i++)
		if(!(strncmp(i,chr, size)))
			return (int)(i-str->str);
	return -1;
}

void supprOf(StringC * str, char * chr, int atpos)
{
	char *itr;
	int i;

	if((i = str->IndexOf(str,chr,atpos)) < 0)
	    return;

	itr = str->str + i;
	strncpy(itr,itr+strlen(chr),strlen(chr));
}

void supprAllOf(StringC* str, char* chr)
{
	int i;
	while((i = str->IndexOf(str,chr,0)) >= 0)
	{
		str->SupprOf(str,chr,i);
	}
}

StringC * cut(StringC * str, int beg, int end)
{
	StringC * cutString = NULL;
	char * cutchr;
	int size = (end-beg)+1;

	if(end < beg)
		return cutString;

	cutchr = (char*)malloc(sizeof(char)*size);
	strncpy(cutchr,str->str+beg,size-1);
	cutchr[size-1] = '\0';
	cutString = newString(cutchr);
	return cutString;
}


int getCount(StringC *str)
{
	int i = 1, count = 0;
	while((i = str->IndexOf(str," ",i)) >= 0)
	{
		count++;
		i++;
	}
	return count+1;
}

int getCountOf(StringC *str, char * chr)
{
	int i = 0, count = 0, size = strlen(chr);
	while((i = str->IndexOf(str,chr,i)) >= 0)
	{
		if((i-1)< 0  || ((i-1)>=0 && str->str[i-1] == ' '))
			count++;
		
		i++;
	}
	return count;
}

int compareTo(StringC* str, char* chr)
{
	return !strcmp(str->str,chr) ? 1 : 0;
}

char * getChar(StringC * str)
{
	char * chr;
	chr = (char*)malloc(sizeof(char) * str->size);
	strcpy(chr,str->str);
	return chr;
}

int toInt(StringC* str)
{
	int strint = 0, i;
	for(i = 0; i < str->size; i++)
		if(((int)str->str) >= (NUM_ASCII_BEGIN + NUM_ASCII_SIZE) || (int)(str->str) < NUM_ASCII_BEGIN)
			continue;
		else
			strint += (int)pow((double)(((int)str->str[str->size-i-1]) - NUM_ASCII_BEGIN),i);
	return strint;
}


int hasInList(ListCh* ls, StringC* str)
{
	Pointer *itr;
	itr = ls->begin;
	while((itr = itr->nextpointer) != ls->end)
	{
		if(str->CompareTo(str,((StringC*)itr->pointer)->str))
			return 1;
		//itr = itr->nextpointer;
	}

	return 0;
}

ListCh* getWordList(StringC * str)
{
	ListCh * wordlist;
	StringC * str_c;
	int i, index = -1, lastindex;
	int wordNb = str->GetCount(str);
	wordlist = newListCh();
	for(i = 0; i < wordNb; i++)
	{
		lastindex = index;
		index = str->IndexOf(str," ",lastindex+1);
		str_c = str->Cut(str,lastindex+1,index < 0 ? str->size : index);
		if(!(hasInList(wordlist,str_c)))
			wordlist->Append(wordlist, str_c);
	}
	return wordlist;
}



