#ifndef LIST_H
#define LIST_H
#include <cstdio>
#include <cstring>

template <typename T>
class List
{
public:
	List();
	~List();

	bool empty() { return _size == 0;}
	size_t size() { return _size;}
	size_t begin() { return 0;}

	void push_back(T);
	void erase(size_t);
	void clear();
	bool hasIn(T);
	T operator[] (size_t i);
private:
	T* container;
	size_t _size;
};

template <typename T>
List<T>::List()
{
	container = NULL;
	_size = 0;
}

template <typename T>
List<T>::~List()
{
	if(container != NULL)
		clear();
}

template <typename T>
void List<T>::push_back(T v)
{
	T* temp = new T[_size+1];
	memcpy(temp,container,_size*sizeof(T));
	temp[_size] = v;
	delete container;
	container = temp;
	_size++;
}

template <typename T>
void List<T>::erase(size_t i)
{

	T* temp = new T[_size-1];
	memcpy(temp,container,i*sizeof(T));
	memcpy(temp+i+1,container,(_size-(i+1))*sizeof(T));
	delete container;
	container = temp;
	_size--;
}

template <typename T>
void List<T>::clear()
{
	if(container != NULL)
		delete container;
}

template <typename T>
bool List<T>::hasIn(T value)
{
	for(size_t i = 0; i < _size; i++)
	{
		if(value == container[i])
			return true;
		else continue;
	}
	return false;
}

template <typename T>
inline T List<T>::operator[] (size_t i)
{
	if(i >= _size)
		return NULL;

	return container[i];
}
#endif

