#pragma once
#define _SCL_SECURE_NO_WARNINGS
#include <memory>
template<class Ty>
class MemoryCache
{
private:
	//Pointer to the allocated area of memory
	Ty* ptr;
	int minSize;
	int elemCapacity;
	float scaleFactor;
	float attenuationFactor;
	float initialScaleFactor;
public:
	//---------------------------------------------------------------------------
	// Whenever the capacity is reached the array expands by the scaleFactor.
	//The scaleFactor is then attenuated (sFactor=sFact/attenuation).
	//Expanding for all integers from 1 to 10,000 the default values have the 
	//following performance: 
	//	6 reallocations
	//	11092 final capacity
	//	11087 total wasted capacity (sum of ( capacity - required ) for each expansion)
	//---------------------------------------------------------------------------



	MemoryCache(int minSize=0,float scaleFactor=10.0f,float attenuationFactor=1.35f)
	{
		ptr=NULL;
		this->minSize = minSize;
		this->elemCapacity=minSize;
		this->scaleFactor=scaleFactor;
		this->attenuationFactor = attenuationFactor;
		this->initialScaleFactor = scaleFactor;
		ptr=new Ty[elemCapacity];
		
	};
	//Sets the capacity to at least the elementCount argument, while clearing all the data
	void ResetCapacity(int elementCount=0)
	{
		if(elementCount<minSize) elementCount=minSize;
		scaleFactor = initialScaleFactor;
		if(elementCount>elemCapacity)
		{
			if(elemCapacity==elemCapacity*scaleFactor) elemCapacity=elementCount;
			while(elemCapacity<elementCount)
			{
				elemCapacity=(int)(elemCapacity*scaleFactor);
				scaleFactor = scaleFactor / attenuationFactor;
			}
			delete[] ptr;
			ptr=new Ty[elemCapacity];
		}
		if(elementCount<elemCapacity)
		{
			elemCapacity=elementCount;
			
			delete[] ptr;
			ptr=new Ty[elemCapacity];
		}
	}
	//Expands the capacity, keeping the content intact
	void Expand(int elementCount)
	{
		
		if(elementCount>elemCapacity)
		{
			int copySize=elemCapacity;
			if(copySize==(int)(elemCapacity*scaleFactor) ) elemCapacity=elementCount;
			while(elemCapacity<elementCount)
			{
				elemCapacity=(int)(elemCapacity*scaleFactor);
				scaleFactor = scaleFactor / attenuationFactor;
			}
			Ty* aux=new Ty[elemCapacity];

			for(int i=0;i<copySize;i++)
			{
				aux[i]=ptr[i];
			}
			 
			delete[] ptr;
			ptr=aux;
		}

	}
	Ty* GetPtr()
	{
		return ptr;
	}
	~MemoryCache(void)
	{
		delete[] ptr;
	}
	
};


