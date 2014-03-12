#pragma once


namespace Tungsten
{

//Vector class implementation, default type float
template<unsigned int dimensions,typename T=float> class Vector
{
private:
	T data[dimensions];
public:
	T& operator[](int index)
		{
			return ((T*)(this))[index];
		};
	template<typename T2>
	Vector<dimensions,T2>	operator=(Vector<dimensions,T2> arg)
	{
		for(int i=0;i<dimensions;i++)
		{
			this->data[i]=(T)arg[i];
		}
		return this;
	};
	Vector<dimensions,T>	operator+(Vector<dimensions,T> arg)
	{
		
		Vector<dimensions,T> ret;
		for(int i=0;i<dimensions;i++)
		{
			ret[i]=this->operator[](i)+(T)arg[i];
		}
		return ret;
	}
};


template<typename T> class Vector<2,T>
{
public:
	T x;
	T y;
	T& operator[](int index)
		{
			return ((T*)(this))[index];
		};
	
	Vector()=default;
	Vector(T x,T y)
		:x(x), y(y)
	{
		
	}
	template<typename T2>
	Vector<2,T>& operator=(Vector<2,T2>& arg)
	{
	
		for(int i=0;i<2;i++)
		{
			this->operator[](i)=(T)arg[i];
		}
		return *this;
	};
	template<typename T2>
	operator Vector<2, T2>()
	{
		Vector<2, T2> ret;
		for (int i = 0; i < 2; i++)
		{
			ret[i] = (T2)this->operator[](i);
		}
		return ret;
	}
	template<typename T2>
	Vector<2,T>	operator+(Vector<2,T2>& arg)
	{
		Vector<2,T> ret;
		for(int i=0;i<2;i++)
		{
			ret[i]=this->operator[](i)+(T)arg[i];
		}
		return ret;
	}
};

	typedef Vector<2> Point;

template<typename T> class Vector<3,T>
{
public:

	T x;
	T y;
	T z;
	T& operator[](int index)
		{
			return ((T*)(this))[index];
		};
	Vector()=default;
	Vector(T x, T y,T z)
	{
		this->x=x;
		this->y=y;
		this->z=z;
	}
	template<typename T2>
	Vector<3,T2> operator=(Vector<3,T2>& arg)
	{
		for(int i=0;i<2;i++)
		{
			this->operator[](i)=(T)arg[i];
		}
		return this;
	};
	Vector<3,T>	operator+(Vector<3,T> arg)
	{
		Vector<3,T> ret;
		for(int i=0;i<3;i++)
		{
			ret[i]=this->operator[](i)+(T)arg[i];
		}
		return ret;
	}
};

template<typename T> class Vector<4,T>
{
public:
	union
	{
		struct
		{
			T x;
			T y;
		};
		Vector<2, T> upperLeft;
	};
	union
	{
		struct
		{
			T z;
			T w;
		};
		Vector<2, T> lowerRight;
	};

	
	
	T& operator[](int index)
		{
			return ((T*)(this))[index];
		};
	Vector() = default;
	Vector(T x, T y,T z,T w)
		:x(x), y(y), z(z), w(w)
		
	{
		
	}
	Vector(Vector<2,T> xy, Vector<2,T> zw)
		:x(xy.x), y(xy.y), z(zw.x), w(zw.y)
		
	{
		
	}
	template<typename T2>
	const Vector<4,T>& operator=(Vector<4,T2>& arg)
	{
		for(int i=0;i<4;i++)
		{
			(this->operator[](i))=(T)(arg[i]);
		}
		return *this;
	};
	Vector<4,T>	operator+(Vector<4,T>& arg)
	{
		Vector<4,T> ret;
		for(int i=0;i<4;i++)
		{
			ret[i]=this->operator[](i)+(T)arg[i];
		}
		return ret;
	}
	
	
	

	//Check if the point is inside the rectangle
	bool Contains(Point p)
	{
		if (p.x<x || p.x>z) return false;
		if (p.y<y || p.y>w) return false;
		return true;
	}
};
	typedef Vector<4> Rectangle;
	typedef Vector<2> float2;
	typedef Vector<3> float3;
	typedef Vector<4> float4;


	//Norm2 of vector (sum of squares)
	template<unsigned int dimensions,typename T>
	T norm2(Vector<dimensions, T>& arg)
	{
		T accumulator=0;
		for (int i = 0; i < dimensions;i++)
		{
			accumulator += arg[i]*arg[i];
		}
		return sqrt(accumulator);
	}

	
	template<unsigned int dimensions, typename T>
	void normalize(Vector<dimensions, T>& arg)
	{
		T length = norm2(arg);
		for (int i = 0; i < dimensions; i++)
		{
			arg[i] /= length;
		}
	}
	
}