#pragma once
namespace Tungsten
{

template<typename T>
class Handle
{
protected:
	T* data;
	unsigned int* counter;
	
public:
	Handle(T* initData=NULL)
	{
		data=initData;
		counter=new unsigned int;
		*counter=1;
	}
	
	Handle(Handle& ref)
	{
		
		counter=ref.counter;
		(*counter)++;
		data=ref.data;
	}
	Handle& operator=(Handle& ref)
	{
		(*counter)--;
		if(*counter<=0)
			delete data;
		counter=ref.counter;
		(*counter)++;
		data=ref.data;
		return *this;
	}

	bool operator==(Handle& ref)
	{
		return data==ref.data;
	}
	T& operator*()
	{
		return *data;
	}
	T* operator->()
	{
		return data;
	}

	~Handle()
	{
		(*counter)--;
		if(*counter<=0) 
		{
			delete data;
			delete counter;
			
		}
	}
	bool IsLast()
	{
		return counter==1;
	}
	bool IsNull()
	{
		return !data;
	}
};

template<typename T>
class WeakHandle: public Handle<T>
{
public:
	WeakHandle()
	{
		data=NULL;
		counter=new unsigned int;
		*counter=0;
	}
	WeakHandle(Handle& ref)
	{
		counter=ref.counter;
		data=ref.data;
	}
	WeakHandle& operator=(Handle& ref)
	{
		counter=ref.counter;
		data=ref.data;
	}
	~WeakHandle()
	{
		
	}


};

}