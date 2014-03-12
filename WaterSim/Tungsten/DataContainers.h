#pragma once
#include <string>

#include "MemoryCache.h"
#include "Vector.h"
#include "Handle.h"
#include <stdexcpt.h>

namespace Tungsten 
{



struct MemoryBlock
{

	void* ptr;
	unsigned int width;
	MemoryBlock()
	{
		ptr=0;
		width=0;
	}
	template<typename T>
	MemoryBlock(T* ptr)
	{
		this->ptr = ptr;
		width = sizeof(T);
	}
	MemoryBlock(void* ptr,unsigned int width)
	{
		this->ptr=ptr;
		this->width=width;
	}
	//Allocates a block of memory of the requested size
	MemoryBlock(int size)
	{
		ptr=new byte[size];
		width=size;
	}
	void Release()
	{
		delete[] ptr;
		ptr=NULL;
	}
	
};


template <typename _val,typename _tag> struct Pair
{
	
	_val val;
	_tag tag;
	_val& elem1 ;
	_tag& elem2 ;
	Pair(_val val,_tag tag)
		:tag(tag), val(val), elem1(val), elem2(tag)
	{

	}


	Pair<_val,_tag>& operator=(Pair& ref)
	{
		tag=ref.tag;
		val=ref.val;
		return *this;
	}
	Pair(Pair& ref)
		:elem1(val), elem2(tag)
	{
		tag=ref.tag;
		val=ref.val;
	}
	Pair()
		:elem1(val), elem2(tag)
	{

	}
};

class OutOfRange : public std::exception
{

};

template<typename T> class DynamicArray
{
private:
	int lastPos;
	MemoryCache<T> memory;

public:
	DynamicArray()
	{
		lastPos=0;
	}


	T& operator[](int index)
	{
		if (index >= lastPos) throw OutOfRange();
		return *(memory.GetPtr()+index);
	};
	void PushBack(T element)
	{
		memory.Expand(++lastPos);
		//The n-th element has the (n-1)th index
		this->operator[](lastPos-1)=element;
	}
	//Returns number of items in the container
	unsigned int GetSize()
	{
		return lastPos;
	}
	unsigned int GetByteWidth()
	{
		return lastPos*sizeof(T);
	}
	//Rests the array
	void Clear()
	{
		lastPos=0;
		memory.ResetCapacity();
	}
	T* GetPtr()
	{
		return memory.GetPtr();
	}

	DynamicArray(DynamicArray<T>& ref)
	{
		lastPos = ref.lastPos;
		memory.Expand(lastPos);
		for (int i = 0; i < lastPos; i++)
		{
			memory.GetPtr()[i] = ref.memory.GetPtr()[i];
		}
	}
	DynamicArray<T>& operator=(DynamicArray<T>& ref)
	{
		memory.ResetCapacity();
		memory.Expand(ref.lastPos);
		lastPos = ref.lastPos;
		for (int i = 0; i < lastPos; i++)
		{
			memory.GetPtr()[i] = ref.memory.GetPtr()[i];
		}
		return *this;
	}
	

};


template <typename _val,typename _tag=std::wstring> class Dictionary;


template <typename _val,typename _tag> class Dictionary
	: public DynamicArray<Pair<_val,_tag>>
{
	
private:
	typedef Pair<_val,_tag> _pair;	
public:
	Dictionary()
		:DynamicArray<_pair>()
	{

	}
	void Register(_pair pair)
	{
		this->PushBack(pair);

	}
	void Register(_val val, _tag tag)
	{
		
		this->PushBack(_pair(val,tag));
	}
	
	
	
	//Method will seek through the dictionary, returning NULL on failure
	_val* Seek    (_tag tag)
	{
		for(unsigned int i=0;i<GetSize() ;i++)
		{
			if(this->operator[](i).tag == tag) return &(this->operator[](i).val);
		}
		return NULL;
	}
	

};

typedef unsigned int Pixel;

struct Color
{
	float r;
	float g;
	float b;
	float a;
	Color() = default;
	Color(float r, float g, float b, float a)
		:r(r), g(g), b(b), a(a)
	{}
	operator Vector<4>()
	{
		return *((Vector<4>*)this);
	}
};

}
